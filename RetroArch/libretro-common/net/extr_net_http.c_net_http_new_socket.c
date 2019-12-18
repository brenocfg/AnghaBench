#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fd; int /*<<< orphan*/  ssl_ctx; scalar_t__ ssl; } ;
struct http_connection_t {TYPE_1__ sock_state; int /*<<< orphan*/  domain; int /*<<< orphan*/  port; } ;
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_TYPE_STREAM ; 
 int /*<<< orphan*/  freeaddrinfo_retro (struct addrinfo*) ; 
 int /*<<< orphan*/  socket_close (int) ; 
 int socket_connect (int,void*,int) ; 
 int socket_init (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket_next (void**) ; 
 scalar_t__ socket_nonblock (int) ; 
 int /*<<< orphan*/  ssl_socket_close (int /*<<< orphan*/ ) ; 
 int ssl_socket_connect (int /*<<< orphan*/ ,void*,int,int) ; 
 int /*<<< orphan*/  ssl_socket_init (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_http_new_socket(struct http_connection_t *conn)
{
   int ret;
   struct addrinfo *addr = NULL, *next_addr = NULL;
   int fd                = socket_init(
         (void**)&addr, conn->port, conn->domain, SOCKET_TYPE_STREAM);
#ifdef HAVE_SSL
   if (conn->sock_state.ssl)
   {
      if (!(conn->sock_state.ssl_ctx = ssl_socket_init(fd, conn->domain)))
         return -1;
   }
#endif

   next_addr = addr;

   while (fd >= 0)
   {
#ifdef HAVE_SSL
      if (conn->sock_state.ssl)
      {
         ret = ssl_socket_connect(conn->sock_state.ssl_ctx,
               (void*)next_addr, true, true);

         if (ret >= 0)
            break;

         ssl_socket_close(conn->sock_state.ssl_ctx);
      }
      else
#endif
      {
         ret = socket_connect(fd, (void*)next_addr, true);

         if (ret >= 0 && socket_nonblock(fd))
            break;

         socket_close(fd);
      }

      fd = socket_next((void**)&next_addr);
   }

   if (addr)
      freeaddrinfo_retro(addr);

   conn->sock_state.fd = fd;

   return fd;
}