#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct natt_status {int have_inet4; int have_inet6; struct sockaddr_in6 ext_inet6_addr; struct sockaddr_in ext_inet4_addr; } ;
struct addrinfo {scalar_t__ ai_family; int ai_addrlen; scalar_t__ ai_addr; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  enum socket_protocol { ____Placeholder_socket_protocol } socket_protocol ;
struct TYPE_4__ {int /*<<< orphan*/  servicetype; } ;
struct TYPE_6__ {TYPE_1__ first; } ;
struct TYPE_5__ {int /*<<< orphan*/ * controlURL; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int PATH_MAX_LENGTH ; 
 int SOCKET_PROTOCOL_UDP ; 
 int UPNP_AddAnyPortMapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char*,char*,char const*,int /*<<< orphan*/ *,char*,char*) ; 
 int UPNP_AddPortMapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char*,char*,char const*,int /*<<< orphan*/ *,char*) ; 
 int UPNP_GetExternalIPAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__ data ; 
 int /*<<< orphan*/  freeaddrinfo_retro (struct addrinfo*) ; 
 scalar_t__ getaddrinfo_retro (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 TYPE_2__ urls ; 

__attribute__((used)) static bool natt_open_port(struct natt_status *status,
      struct sockaddr *addr, socklen_t addrlen, enum socket_protocol proto)
{
#ifndef HAVE_SOCKET_LEGACY
#if HAVE_MINIUPNPC
   int r;
   char host[PATH_MAX_LENGTH], ext_host[PATH_MAX_LENGTH],
        port_str[6], ext_port_str[6];
   struct addrinfo hints         = {0};
   const char *proto_str         = NULL;
   struct addrinfo *ext_addrinfo = NULL;

   /* if NAT traversal is uninitialized or unavailable, oh well */
   if (!urls.controlURL || !urls.controlURL[0])
      return false;

   /* figure out the internal info */
   if (getnameinfo(addr, addrlen, host, PATH_MAX_LENGTH,
            port_str, 6, NI_NUMERICHOST|NI_NUMERICSERV) != 0)
      return false;

   proto_str = (proto == SOCKET_PROTOCOL_UDP) ? "UDP" : "TCP";

   /* add the port mapping */
   r = UPNP_AddAnyPortMapping(urls.controlURL,
         data.first.servicetype, port_str,
         port_str, host, "retroarch",
         proto_str, NULL, "3600", ext_port_str);

   if (r != 0)
   {
      /* try the older AddPortMapping */
      memcpy(ext_port_str, port_str, 6);
      r = UPNP_AddPortMapping(urls.controlURL,
            data.first.servicetype, port_str,
            port_str, host, "retroarch",
            proto_str, NULL, "3600");
   }
   if (r != 0)
      return false;

   /* get the external IP */
   r = UPNP_GetExternalIPAddress(urls.controlURL,
         data.first.servicetype, ext_host);
   if (r != 0)
      return false;

   /* update the status */
   if (getaddrinfo_retro(ext_host,
            ext_port_str, &hints, &ext_addrinfo) != 0)
      return false;

   if (ext_addrinfo->ai_family == AF_INET &&
       ext_addrinfo->ai_addrlen >= sizeof(struct sockaddr_in))
   {
      status->have_inet4     = true;
      status->ext_inet4_addr = *((struct sockaddr_in *)
            ext_addrinfo->ai_addr);
   }
#if defined(AF_INET6) && !defined(HAVE_SOCKET_LEGACY)
   else if (ext_addrinfo->ai_family == AF_INET6 &&
            ext_addrinfo->ai_addrlen >= sizeof(struct sockaddr_in6))
   {
      status->have_inet6     = true;
      status->ext_inet6_addr = *((struct sockaddr_in6 *)
            ext_addrinfo->ai_addr);
   }
#endif
   else
   {
      freeaddrinfo_retro(ext_addrinfo);
      return false;
   }

   freeaddrinfo_retro(ext_addrinfo);
   return true;

#else
   return false;
#endif
#else
   return false;
#endif
}