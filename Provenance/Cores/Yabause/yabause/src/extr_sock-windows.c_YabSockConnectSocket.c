#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct addrinfo {scalar_t__ ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  hints ;
typedef  int YabSock ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int connect (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int YabSockConnectSocket(const char *ip, int port, YabSock *sock)
{
   struct addrinfo *result = NULL, hints;
   char port_str[256];

   memset(&hints, 0, sizeof(hints));

   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_protocol = IPPROTO_TCP;

   sprintf(port_str, "%d", port);
   if (getaddrinfo(ip, port_str, &hints, &result) != 0)
   {
      perror("getaddrinfo");
      return -1;
   }

   // Create a Socket
   if ((sock[0] = socket(result->ai_family, result->ai_socktype,
      result->ai_protocol)) == -1)
   {
      freeaddrinfo(result);
      perror("socket");
      return -1;
   }

   // Connect to the socket
   if (connect(sock[0], result->ai_addr, (int)result->ai_addrlen) == -1)
   {
      perror("connect");
      freeaddrinfo(result);
      closesocket(sock[0]);
      return -1;
   }

   freeaddrinfo(result);
   return 0;
}