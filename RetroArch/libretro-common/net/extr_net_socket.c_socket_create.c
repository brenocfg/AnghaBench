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
typedef  enum socket_type { ____Placeholder_socket_type } socket_type ;
typedef  enum socket_protocol { ____Placeholder_socket_protocol } socket_protocol ;
typedef  enum socket_domain { ____Placeholder_socket_domain } socket_domain ;

/* Variables and functions */
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int SCE_NET_IPPROTO_TCP ; 
 int SCE_NET_IPPROTO_UDP ; 
 int SCE_NET_SOCK_DGRAM ; 
 int SCE_NET_SOCK_STREAM ; 
#define  SOCKET_PROTOCOL_NONE 133 
#define  SOCKET_PROTOCOL_TCP 132 
#define  SOCKET_PROTOCOL_UDP 131 
#define  SOCKET_TYPE_DATAGRAM 130 
#define  SOCKET_TYPE_SEQPACKET 129 
#define  SOCKET_TYPE_STREAM 128 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 int domain_get (int) ; 
 int sceNetSocket (char const*,int,int,int) ; 
 int socket (int,int,int) ; 

int socket_create(
      const char *name,
      enum socket_domain   domain_type,
      enum socket_type     socket_type,
      enum socket_protocol protocol_type)
{
   int type     = 0;
   int protocol = 0;
   int domain   = domain_get(domain_type);
#ifdef VITA

   switch (socket_type)
   {
      case SOCKET_TYPE_DATAGRAM:
         type = SCE_NET_SOCK_DGRAM;
         break;
      case SOCKET_TYPE_STREAM:
         type = SCE_NET_SOCK_STREAM;
         break;
      case SOCKET_TYPE_SEQPACKET:
         /* TODO/FIXME - implement */
         break;
   }

   switch (protocol_type)
   {
      case SOCKET_PROTOCOL_NONE:
         protocol = 0;
         break;
      case SOCKET_PROTOCOL_TCP:
         protocol = SCE_NET_IPPROTO_TCP;
         break;
      case SOCKET_PROTOCOL_UDP:
         protocol = SCE_NET_IPPROTO_UDP;
         break;
   }

   return sceNetSocket(name, domain, type, protocol);
#else
   switch (socket_type)
   {
      case SOCKET_TYPE_DATAGRAM:
         type = SOCK_DGRAM;
         break;
      case SOCKET_TYPE_STREAM:
         type = SOCK_STREAM;
         break;
      case SOCKET_TYPE_SEQPACKET:
         /* TODO/FIXME - implement */
         break;
   }

   switch (protocol_type)
   {
      case SOCKET_PROTOCOL_NONE:
         protocol = 0;
         break;
      case SOCKET_PROTOCOL_TCP:
         protocol = IPPROTO_TCP;
         break;
      case SOCKET_PROTOCOL_UDP:
         protocol = IPPROTO_UDP;
         break;
   }

   return socket(domain, type, protocol);
#endif
}