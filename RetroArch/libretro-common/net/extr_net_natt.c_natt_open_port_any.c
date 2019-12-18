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
struct net_ifinfo_entry {int /*<<< orphan*/  host; } ;
struct net_ifinfo {size_t size; struct net_ifinfo_entry* entries; } ;
struct natt_status {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  port_str ;
typedef  enum socket_protocol { ____Placeholder_socket_protocol } socket_protocol ;

/* Variables and functions */
 int /*<<< orphan*/  freeaddrinfo_retro (struct addrinfo*) ; 
 scalar_t__ getaddrinfo_retro (int /*<<< orphan*/ ,char*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ natt_open_port (struct natt_status*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_ifinfo_free (struct net_ifinfo*) ; 
 int /*<<< orphan*/  net_ifinfo_new (struct net_ifinfo*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 

bool natt_open_port_any(struct natt_status *status,
      uint16_t port, enum socket_protocol proto)
{
#if !defined(HAVE_SOCKET_LEGACY) && (!defined(SWITCH) || defined(SWITCH) && defined(HAVE_LIBNX))
   size_t i;
   char port_str[6];
   struct net_ifinfo list;
   struct addrinfo hints = {0}, *addr;
   bool ret              = false;

   snprintf(port_str, sizeof(port_str), "%hu", port);

   /* get our interfaces */
   if (!net_ifinfo_new(&list))
      return false;

   /* loop through them */
   for (i = 0; i < list.size; i++)
   {
      struct net_ifinfo_entry *entry = list.entries + i;

      /* ignore localhost */
      if (  string_is_equal(entry->host, "127.0.0.1") ||
            string_is_equal(entry->host, "::1"))
         continue;

      /* make a request for this host */
      if (getaddrinfo_retro(entry->host, port_str, &hints, &addr) == 0)
      {
         ret = natt_open_port(status, addr->ai_addr,
               addr->ai_addrlen, proto) || ret;
         freeaddrinfo_retro(addr);
      }
   }

   net_ifinfo_free(&list);

   return ret;

#else
   return false;
#endif
}