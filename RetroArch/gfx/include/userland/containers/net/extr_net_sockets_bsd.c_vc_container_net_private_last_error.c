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
#define  EACCES 153 
#define  EADDRINUSE 152 
#define  EADDRNOTAVAIL 151 
#define  EALREADY 150 
#define  ECONNABORTED 149 
#define  ECONNREFUSED 148 
#define  ECONNRESET 147 
#define  EDQUOT 146 
#define  EFAULT 145 
#define  EHOSTDOWN 144 
#define  EHOSTUNREACH 143 
#define  EINPROGRESS 142 
#define  EINVAL 141 
#define  ELOOP 140 
#define  EMFILE 139 
#define  ENAMETOOLONG 138 
#define  ENETDOWN 137 
#define  ENETRESET 136 
#define  ENETUNREACH 135 
#define  ENOBUFS 134 
#define  ENOTCONN 133 
#define  ESHUTDOWN 132 
#define  ESTALE 131 
#define  ETIMEDOUT 130 
#define  EUSERS 129 
#define  EWOULDBLOCK 128 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_CONNECTION_LOST ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_CONNECTION_REFUSED ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_GENERAL ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_INVALID_SOCKET ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_IN_PROGRESS ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_IN_USE ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NETWORK ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NOT_CONNECTED ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_TIMED_OUT ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_TOO_BIG ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_WOULD_BLOCK ; 
 int errno ; 

vc_container_net_status_t vc_container_net_private_last_error()
{
   switch (errno)
   {
   case EACCES:               return VC_CONTAINER_NET_ERROR_ACCESS_DENIED;
   case EFAULT:               return VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   case EINVAL:               return VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   case EMFILE:               return VC_CONTAINER_NET_ERROR_TOO_BIG;
   case EWOULDBLOCK:          return VC_CONTAINER_NET_ERROR_WOULD_BLOCK;
   case EINPROGRESS:          return VC_CONTAINER_NET_ERROR_IN_PROGRESS;
   case EALREADY:             return VC_CONTAINER_NET_ERROR_IN_PROGRESS;
   case EADDRINUSE:           return VC_CONTAINER_NET_ERROR_IN_USE;
   case EADDRNOTAVAIL:        return VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   case ENETDOWN:             return VC_CONTAINER_NET_ERROR_NETWORK;
   case ENETUNREACH:          return VC_CONTAINER_NET_ERROR_NETWORK;
   case ENETRESET:            return VC_CONTAINER_NET_ERROR_CONNECTION_LOST;
   case ECONNABORTED:         return VC_CONTAINER_NET_ERROR_CONNECTION_LOST;
   case ECONNRESET:           return VC_CONTAINER_NET_ERROR_CONNECTION_LOST;
   case ENOBUFS:              return VC_CONTAINER_NET_ERROR_NO_MEMORY;
   case ENOTCONN:             return VC_CONTAINER_NET_ERROR_NOT_CONNECTED;
   case ESHUTDOWN:            return VC_CONTAINER_NET_ERROR_CONNECTION_LOST;
   case ETIMEDOUT:            return VC_CONTAINER_NET_ERROR_TIMED_OUT;
   case ECONNREFUSED:         return VC_CONTAINER_NET_ERROR_CONNECTION_REFUSED;
   case ELOOP:                return VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   case ENAMETOOLONG:         return VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   case EHOSTDOWN:            return VC_CONTAINER_NET_ERROR_NETWORK;
   case EHOSTUNREACH:         return VC_CONTAINER_NET_ERROR_NETWORK;
   case EUSERS:               return VC_CONTAINER_NET_ERROR_NO_MEMORY;
   case EDQUOT:               return VC_CONTAINER_NET_ERROR_NO_MEMORY;
   case ESTALE:               return VC_CONTAINER_NET_ERROR_INVALID_SOCKET;

   /* All other errors are unexpected, so just map to a general purpose error code. */
   default:
      return VC_CONTAINER_NET_ERROR_GENERAL;
   }
}