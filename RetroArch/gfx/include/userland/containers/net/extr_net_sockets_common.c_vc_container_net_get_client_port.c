#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vc_container_net_status_t ;
struct TYPE_8__ {int /*<<< orphan*/  sin6_port; } ;
struct TYPE_7__ {int /*<<< orphan*/  sin_port; } ;
struct TYPE_10__ {int sa_family; } ;
struct TYPE_9__ {TYPE_2__ in6; TYPE_1__ in; TYPE_4__ sa; } ;
struct TYPE_11__ {scalar_t__ socket; int /*<<< orphan*/  status; TYPE_3__ to_addr; } ;
typedef  TYPE_5__ VC_CONTAINER_NET_T ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_GENERAL ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_INVALID_SOCKET ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NOT_CONNECTED ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_SUCCESS ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 

vc_container_net_status_t vc_container_net_get_client_port( VC_CONTAINER_NET_T *p_ctx , unsigned short *port )
{
   if (!p_ctx)
      return VC_CONTAINER_NET_ERROR_INVALID_SOCKET;

   if (p_ctx->socket == INVALID_SOCKET)
      p_ctx->status = VC_CONTAINER_NET_ERROR_NOT_CONNECTED;
   else if (!port)
      p_ctx->status = VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   else
   {
      p_ctx->status = VC_CONTAINER_NET_SUCCESS;
      switch (p_ctx->to_addr.sa.sa_family)
      {
      case AF_INET:
         *port = ntohs(p_ctx->to_addr.in.sin_port);
         break;
      case AF_INET6:
         *port = ntohs(p_ctx->to_addr.in6.sin6_port);
         break;
      default:
         /* Highly unexepcted address family! */
         p_ctx->status = VC_CONTAINER_NET_ERROR_GENERAL;
      }
   }

   return p_ctx->status;
}