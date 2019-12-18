#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vc_container_net_status_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  status; int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ VC_CONTAINER_NET_T ;

/* Variables and functions */
 scalar_t__ SOCKET_ERROR ; 
 scalar_t__ STREAM_SERVER ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_INVALID_SOCKET ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NOT_ALLOWED ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_SUCCESS ; 
 scalar_t__ listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_net_private_last_error () ; 

vc_container_net_status_t vc_container_net_listen( VC_CONTAINER_NET_T *p_ctx, uint32_t maximum_connections )
{
   if (!p_ctx)
      return VC_CONTAINER_NET_ERROR_INVALID_SOCKET;

   p_ctx->status = VC_CONTAINER_NET_SUCCESS;

   if (p_ctx->type == STREAM_SERVER)
   {
      if (listen(p_ctx->socket, maximum_connections) == SOCKET_ERROR)
         p_ctx->status = vc_container_net_private_last_error();
   } else {
      p_ctx->status = VC_CONTAINER_NET_ERROR_NOT_ALLOWED;
   }

   return p_ctx->status;
}