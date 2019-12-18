#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ VC_CONTAINER_NET_T ;

/* Variables and functions */
 scalar_t__ DATAGRAM_SENDER ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NOT_ALLOWED ; 
 int socket_wait_for_data (TYPE_1__*,int /*<<< orphan*/ ) ; 

bool vc_container_net_is_data_available( VC_CONTAINER_NET_T *p_ctx )
{
   if (!p_ctx)
      return false;

   if (p_ctx->type == DATAGRAM_SENDER)
   {
      p_ctx->status = VC_CONTAINER_NET_ERROR_NOT_ALLOWED;
      return false;
   }

   return socket_wait_for_data(p_ctx, 0);
}