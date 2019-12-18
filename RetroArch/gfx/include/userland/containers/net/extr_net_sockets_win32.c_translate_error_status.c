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
typedef  int /*<<< orphan*/  vc_container_net_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_CONNECTION_LOST ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_CONNECTION_REFUSED ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_GENERAL ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_HOST_NOT_FOUND ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_INVALID_SOCKET ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_IN_PROGRESS ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_IN_USE ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NETWORK ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NOT_CONNECTED ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_TIMED_OUT ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_TOO_BIG ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_TRY_AGAIN ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_WOULD_BLOCK ; 
#define  WSAEACCES 162 
#define  WSAEADDRINUSE 161 
#define  WSAEADDRNOTAVAIL 160 
#define  WSAEALREADY 159 
#define  WSAECONNABORTED 158 
#define  WSAECONNREFUSED 157 
#define  WSAECONNRESET 156 
#define  WSAEDISCON 155 
#define  WSAEDQUOT 154 
#define  WSAEFAULT 153 
#define  WSAEHOSTDOWN 152 
#define  WSAEHOSTUNREACH 151 
#define  WSAEINPROGRESS 150 
#define  WSAEINVAL 149 
#define  WSAELOOP 148 
#define  WSAEMFILE 147 
#define  WSAENAMETOOLONG 146 
#define  WSAENETDOWN 145 
#define  WSAENETRESET 144 
#define  WSAENETUNREACH 143 
#define  WSAENOBUFS 142 
#define  WSAENOTCONN 141 
#define  WSAEPROCLIM 140 
#define  WSAESHUTDOWN 139 
#define  WSAESTALE 138 
#define  WSAETIMEDOUT 137 
#define  WSAEUSERS 136 
#define  WSAEWOULDBLOCK 135 
#define  WSAHOST_NOT_FOUND 134 
#define  WSANO_DATA 133 
#define  WSANO_RECOVERY 132 
#define  WSATRY_AGAIN 131 
#define  WSA_INVALID_HANDLE 130 
#define  WSA_INVALID_PARAMETER 129 
#define  WSA_NOT_ENOUGH_MEMORY 128 

__attribute__((used)) static vc_container_net_status_t translate_error_status( int error )
{
   switch (error)
   {
   case WSA_INVALID_HANDLE:      return VC_CONTAINER_NET_ERROR_INVALID_SOCKET;
   case WSA_NOT_ENOUGH_MEMORY:   return VC_CONTAINER_NET_ERROR_NO_MEMORY;
   case WSA_INVALID_PARAMETER:   return VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   case WSAEACCES:               return VC_CONTAINER_NET_ERROR_ACCESS_DENIED;
   case WSAEFAULT:               return VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   case WSAEINVAL:               return VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   case WSAEMFILE:               return VC_CONTAINER_NET_ERROR_TOO_BIG;
   case WSAEWOULDBLOCK:          return VC_CONTAINER_NET_ERROR_WOULD_BLOCK;
   case WSAEINPROGRESS:          return VC_CONTAINER_NET_ERROR_IN_PROGRESS;
   case WSAEALREADY:             return VC_CONTAINER_NET_ERROR_IN_PROGRESS;
   case WSAEADDRINUSE:           return VC_CONTAINER_NET_ERROR_IN_USE;
   case WSAEADDRNOTAVAIL:        return VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   case WSAENETDOWN:             return VC_CONTAINER_NET_ERROR_NETWORK;
   case WSAENETUNREACH:          return VC_CONTAINER_NET_ERROR_NETWORK;
   case WSAENETRESET:            return VC_CONTAINER_NET_ERROR_CONNECTION_LOST;
   case WSAECONNABORTED:         return VC_CONTAINER_NET_ERROR_CONNECTION_LOST;
   case WSAECONNRESET:           return VC_CONTAINER_NET_ERROR_CONNECTION_LOST;
   case WSAENOBUFS:              return VC_CONTAINER_NET_ERROR_NO_MEMORY;
   case WSAENOTCONN:             return VC_CONTAINER_NET_ERROR_NOT_CONNECTED;
   case WSAESHUTDOWN:            return VC_CONTAINER_NET_ERROR_CONNECTION_LOST;
   case WSAETIMEDOUT:            return VC_CONTAINER_NET_ERROR_TIMED_OUT;
   case WSAECONNREFUSED:         return VC_CONTAINER_NET_ERROR_CONNECTION_REFUSED;
   case WSAELOOP:                return VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   case WSAENAMETOOLONG:         return VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   case WSAEHOSTDOWN:            return VC_CONTAINER_NET_ERROR_NETWORK;
   case WSAEHOSTUNREACH:         return VC_CONTAINER_NET_ERROR_NETWORK;
   case WSAEPROCLIM:             return VC_CONTAINER_NET_ERROR_NO_MEMORY;
   case WSAEUSERS:               return VC_CONTAINER_NET_ERROR_NO_MEMORY;
   case WSAEDQUOT:               return VC_CONTAINER_NET_ERROR_NO_MEMORY;
   case WSAESTALE:               return VC_CONTAINER_NET_ERROR_INVALID_SOCKET;
   case WSAEDISCON:              return VC_CONTAINER_NET_ERROR_CONNECTION_LOST;
   case WSAHOST_NOT_FOUND:       return VC_CONTAINER_NET_ERROR_HOST_NOT_FOUND;
   case WSATRY_AGAIN:            return VC_CONTAINER_NET_ERROR_TRY_AGAIN;
   case WSANO_RECOVERY:          return VC_CONTAINER_NET_ERROR_HOST_NOT_FOUND;
   case WSANO_DATA:              return VC_CONTAINER_NET_ERROR_HOST_NOT_FOUND;

   /* All other errors are unexpected, so just map to a general purpose error code. */
   default:
      return VC_CONTAINER_NET_ERROR_GENERAL;
   }
}