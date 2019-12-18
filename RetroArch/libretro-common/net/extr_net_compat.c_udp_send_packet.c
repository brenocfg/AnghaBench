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
struct addrinfo {struct addrinfo* ai_next; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  port_buf ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  freeaddrinfo_retro (struct addrinfo*) ; 
 scalar_t__ getaddrinfo_retro (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ sendto (int,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned short) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_close (int) ; 
 scalar_t__ strlen (char const*) ; 

bool udp_send_packet(const char *host,
      uint16_t port, const char *msg)
{
   char port_buf[16]           = {0};
   struct addrinfo hints       = {0};
   struct addrinfo *res        = NULL;
   const struct addrinfo *tmp  = NULL;
   int fd                      = -1;
   bool ret                    = true;

   hints.ai_socktype           = SOCK_DGRAM;

   snprintf(port_buf, sizeof(port_buf), "%hu", (unsigned short)port);

   if (getaddrinfo_retro(host, port_buf, &hints, &res) != 0)
      return false;

   /* Send to all possible targets.
    * "localhost" might resolve to several different IPs. */
   tmp = (const struct addrinfo*)res;
   while (tmp)
   {
      ssize_t len, ret_len;

      fd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
      if (fd < 0)
      {
         ret = false;
         goto end;
      }

      len     = strlen(msg);
      ret_len = sendto(fd, msg, len, 0, tmp->ai_addr, tmp->ai_addrlen);

      if (ret_len < len)
      {
         ret = false;
         goto end;
      }

      socket_close(fd);
      fd = -1;
      tmp = tmp->ai_next;
   }

end:
   freeaddrinfo_retro(res);
   if (fd >= 0)
      socket_close(fd);
   return ret;
}