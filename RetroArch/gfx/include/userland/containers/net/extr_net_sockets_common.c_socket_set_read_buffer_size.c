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
typedef  int /*<<< orphan*/  buffer_size ;
struct TYPE_3__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ VC_CONTAINER_NET_T ;
typedef  int /*<<< orphan*/  SOCKOPT_CAST_T ;

/* Variables and functions */
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_SUCCESS ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  vc_container_net_private_last_error () ; 

__attribute__((used)) static vc_container_net_status_t socket_set_read_buffer_size(VC_CONTAINER_NET_T *p_ctx,
      uint32_t buffer_size)
{
   int result;
   const SOCKOPT_CAST_T optptr = (const SOCKOPT_CAST_T)&buffer_size;

   result = setsockopt(p_ctx->socket, SOL_SOCKET, SO_RCVBUF, optptr, sizeof(buffer_size));

   if (result == SOCKET_ERROR)
      return vc_container_net_private_last_error();

   return VC_CONTAINER_NET_SUCCESS;
}