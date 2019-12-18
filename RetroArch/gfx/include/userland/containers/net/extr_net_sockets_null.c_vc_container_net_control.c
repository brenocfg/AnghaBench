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
typedef  int /*<<< orphan*/ * vc_container_net_control_t ;
typedef  int /*<<< orphan*/ * va_list ;
typedef  int /*<<< orphan*/  VC_CONTAINER_NET_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NOT_ALLOWED ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ *) ; 

vc_container_net_status_t vc_container_net_control( VC_CONTAINER_NET_T *p_ctx,
      vc_container_net_control_t operation,
      va_list args)
{
   VC_CONTAINER_PARAM_UNUSED(p_ctx);
   VC_CONTAINER_PARAM_UNUSED(operation);
   VC_CONTAINER_PARAM_UNUSED(args);

   return VC_CONTAINER_NET_ERROR_NOT_ALLOWED;
}