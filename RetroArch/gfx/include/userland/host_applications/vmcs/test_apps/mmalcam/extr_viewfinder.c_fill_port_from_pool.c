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
struct TYPE_3__ {int /*<<< orphan*/ * queue; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_QUEUE_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_1__ MMAL_POOL_T ;

/* Variables and functions */
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_queue_length (int /*<<< orphan*/ *) ; 
 scalar_t__ send_buffer_from_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T fill_port_from_pool(MMAL_PORT_T *port, MMAL_POOL_T *pool)
{
   MMAL_STATUS_T status = MMAL_SUCCESS;
   MMAL_QUEUE_T *queue;

   if (!pool)
      return MMAL_SUCCESS;

   queue = pool->queue;
   while (status == MMAL_SUCCESS && mmal_queue_length(queue) > 0)
      status = send_buffer_from_queue(port, queue);

   return status;
}