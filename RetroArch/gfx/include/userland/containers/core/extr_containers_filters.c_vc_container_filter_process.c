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
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_PACKET_T ;
struct TYPE_4__ {int /*<<< orphan*/  (* pf_process ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ VC_CONTAINER_FILTER_T ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

VC_CONTAINER_STATUS_T vc_container_filter_process( VC_CONTAINER_FILTER_T *p_ctx, VC_CONTAINER_PACKET_T *p_packet )
{
   VC_CONTAINER_STATUS_T status;
   status = p_ctx->pf_process(p_ctx, p_packet);
   return status;
}