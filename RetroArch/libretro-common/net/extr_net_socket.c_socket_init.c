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
typedef  scalar_t__ uint16_t ;
struct addrinfo {int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  port_buf ;
typedef  enum socket_type { ____Placeholder_socket_type } socket_type ;

/* Variables and functions */
 int /*<<< orphan*/  AI_PASSIVE ; 
#define  SOCKET_TYPE_DATAGRAM 130 
#define  SOCKET_TYPE_SEQPACKET 129 
#define  SOCKET_TYPE_STREAM 128 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ getaddrinfo_retro (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  network_init () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned short) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int socket_init(void **address, uint16_t port, const char *server, enum socket_type type)
{
   char port_buf[16];
   struct addrinfo hints = {0};
   struct addrinfo **addrinfo = (struct addrinfo**)address;
   struct addrinfo *addr = NULL;

   if (!network_init())
      goto error;

   switch (type)
   {
      case SOCKET_TYPE_DATAGRAM:
         hints.ai_socktype = SOCK_DGRAM;
         break;
      case SOCKET_TYPE_STREAM:
         hints.ai_socktype = SOCK_STREAM;
         break;
      case SOCKET_TYPE_SEQPACKET:
         /* TODO/FIXME - implement? */
         break;
   }

   if (!server)
      hints.ai_flags = AI_PASSIVE;

   port_buf[0] = '\0';

   snprintf(port_buf, sizeof(port_buf), "%hu", (unsigned short)port);

   if (getaddrinfo_retro(server, port_buf, &hints, addrinfo) != 0)
      goto error;

   addr = (struct addrinfo*)*addrinfo;

   if (!addr)
      goto error;

   return socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

error:
   return -1;
}