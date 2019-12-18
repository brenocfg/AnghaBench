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
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ VC_CONTAINER_NET_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_INVALID_SOCKET ; 

vc_container_net_status_t vc_container_net_status( VC_CONTAINER_NET_T *p_ctx )
{
   if (!p_ctx)
      return VC_CONTAINER_NET_ERROR_INVALID_SOCKET;
   return p_ctx->status;
}