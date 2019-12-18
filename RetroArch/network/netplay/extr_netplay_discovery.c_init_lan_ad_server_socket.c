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
typedef  int /*<<< orphan*/  uint16_t ;
struct addrinfo {int dummy; } ;
typedef  int /*<<< orphan*/  netplay_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  SOCKET_TYPE_DATAGRAM ; 
 int /*<<< orphan*/  freeaddrinfo_retro (struct addrinfo*) ; 
 int lan_ad_server_fd ; 
 int /*<<< orphan*/  socket_bind (int,void*) ; 
 int /*<<< orphan*/  socket_close (int) ; 
 int socket_init (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool init_lan_ad_server_socket(netplay_t *netplay, uint16_t port)
{
   struct addrinfo *addr = NULL;
   int fd = socket_init((void **) &addr, port, NULL, SOCKET_TYPE_DATAGRAM);

   if (fd < 0)
      goto error;

   if (!socket_bind(fd, (void*)addr))
   {
      socket_close(fd);
      goto error;
   }

   lan_ad_server_fd = fd;
   freeaddrinfo_retro(addr);

   return true;

error:
   if (addr)
      freeaddrinfo_retro(addr);
   RARCH_ERR("[discovery] Failed to initialize netplay advertisement socket\n");
   return false;
}