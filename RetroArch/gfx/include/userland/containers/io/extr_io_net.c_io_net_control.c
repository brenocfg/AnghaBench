#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vc_container_net_status_t ;
typedef  int /*<<< orphan*/  va_list ;
struct VC_CONTAINER_IO_T {int /*<<< orphan*/  status; TYPE_1__* module; } ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int VC_CONTAINER_CONTROL_T ;
struct TYPE_2__ {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
#define  VC_CONTAINER_CONTROL_IO_SET_READ_BUFFER_SIZE 129 
#define  VC_CONTAINER_CONTROL_IO_SET_READ_TIMEOUT_MS 128 
 int /*<<< orphan*/  VC_CONTAINER_NET_CONTROL_SET_READ_BUFFER_SIZE ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_CONTROL_SET_READ_TIMEOUT_MS ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NOT_ALLOWED ; 
 int /*<<< orphan*/  translate_net_status_to_container_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_net_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T io_net_control(struct VC_CONTAINER_IO_T *p_ctx,
      VC_CONTAINER_CONTROL_T operation,
      va_list args)
{
   vc_container_net_status_t net_status;
   VC_CONTAINER_STATUS_T status;

   switch (operation)
   {
   case VC_CONTAINER_CONTROL_IO_SET_READ_BUFFER_SIZE:
      net_status = vc_container_net_control(p_ctx->module->sock, VC_CONTAINER_NET_CONTROL_SET_READ_BUFFER_SIZE, args);
      break;
   case VC_CONTAINER_CONTROL_IO_SET_READ_TIMEOUT_MS:
      net_status = vc_container_net_control(p_ctx->module->sock, VC_CONTAINER_NET_CONTROL_SET_READ_TIMEOUT_MS, args);
      break;
   default:
      net_status = VC_CONTAINER_NET_ERROR_NOT_ALLOWED;
   }

   status = translate_net_status_to_container_status(net_status);
   p_ctx->status = status;

   return status;
}