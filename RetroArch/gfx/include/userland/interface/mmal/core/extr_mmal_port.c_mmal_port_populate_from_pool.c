#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  queue; } ;
struct TYPE_10__ {scalar_t__ buffer_num; int /*<<< orphan*/  name; TYPE_1__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  pf_send; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_POOL_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ MMAL_ENOMEM ; 
 scalar_t__ MMAL_ENOSYS ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_buffer_header_release (int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_send_buffer (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_populate_from_pool(MMAL_PORT_T* port, MMAL_POOL_T* pool)
{
   MMAL_STATUS_T status = MMAL_SUCCESS;
   uint32_t buffer_idx;
   MMAL_BUFFER_HEADER_T *buffer;

   if (!port->priv->pf_send)
      return MMAL_ENOSYS;

   LOG_TRACE("%s port %p, pool: %p", port->name, port, pool);

   /* Populate port from pool */
   for (buffer_idx = 0; buffer_idx < port->buffer_num; buffer_idx++)
   {
      buffer = mmal_queue_get(pool->queue);
      if (!buffer)
      {
         LOG_ERROR("too few buffers in the pool");
         status = MMAL_ENOMEM;
         break;
      }

      status = mmal_port_send_buffer(port, buffer);
      if (status != MMAL_SUCCESS)
      {
         LOG_ERROR("failed to send buffer to port");
         mmal_buffer_header_release(buffer);
         break;
      }
   }

   return status;
}