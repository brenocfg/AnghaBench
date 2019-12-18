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
typedef  int vc_container_net_control_t ;
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  VC_CONTAINER_NET_T ;

/* Variables and functions */
#define  VC_CONTAINER_NET_CONTROL_SET_READ_BUFFER_SIZE 129 
#define  VC_CONTAINER_NET_CONTROL_SET_READ_TIMEOUT_MS 128 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NOT_ALLOWED ; 
 int /*<<< orphan*/  socket_set_read_buffer_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_set_read_timeout_ms (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint32_t ; 
 int /*<<< orphan*/  va_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vc_container_net_status_t vc_container_net_control( VC_CONTAINER_NET_T *p_ctx,
      vc_container_net_control_t operation,
      va_list args)
{
   vc_container_net_status_t status;

   switch (operation)
   {
   case VC_CONTAINER_NET_CONTROL_SET_READ_BUFFER_SIZE:
      status = socket_set_read_buffer_size(p_ctx, va_arg(args, uint32_t));
      break;
   case VC_CONTAINER_NET_CONTROL_SET_READ_TIMEOUT_MS:
      status = socket_set_read_timeout_ms(p_ctx, va_arg(args, uint32_t));
      break;
   default:
      status = VC_CONTAINER_NET_ERROR_NOT_ALLOWED;
   }

   return status;
}