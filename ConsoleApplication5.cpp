

#include <iostream>
#include <thread>
#include <vector>
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

std::vector<SOCKET> clientList;

void Run(SOCKET);

int main()
{
    SOCKET serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cout << "socket error" << std::endl;
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.S_un.S_addr = htonl(INADDR_LOOPBACK);

    int result = bind(serverSocket,
        (const sockaddr*)(&serverAddress), 
        sizeof(serverAddress));
    if (result < 0)
    {
        std::cout << "bind socket error" << std::endl;
        return 1;
    }

    result = listen(serverSocket, 100);
    if (result < 0)
    {
        std::cout << "listen socket error" << std::endl;
        return 1;
    }

    while (true)
    {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

        new std::thread(Run, clientSocket);
        ClientList.push_back(clientSocket);
    }
    return 0; 
}

void Run(SOCKET s) {
    char message[512];
    while (true)
    {
        int n = recv(s, message, 512, 0);
        if (n < 0)
        {
            break;
        }
        std::cout << message << std::endl;
        send(s, "ok", 3, 0);
    }
}
