#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {scalar_t__ headers_num; int /*<<< orphan*/  queue; } ;
struct TYPE_10__ {scalar_t__ type; size_t index; int /*<<< orphan*/  is_enabled; int /*<<< orphan*/  name; scalar_t__ userdata; } ;
struct TYPE_8__ {scalar_t__ time_disable; int /*<<< orphan*/ ** output_queue; TYPE_4__** output_pool; } ;
struct TYPE_9__ {TYPE_1__ wrapper; } ;
typedef  TYPE_1__ MMAL_WRAPPER_T ;
typedef  TYPE_2__ MMAL_WRAPPER_PRIVATE_T ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_QUEUE_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_POOL_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_PORT_TYPE_INPUT ; 
 scalar_t__ MMAL_PORT_TYPE_OUTPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_buffer_header_release (int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_disable (TYPE_3__*) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_queue_length (int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_getmicrosecs () ; 
 int /*<<< orphan*/  vcos_verify (int) ; 

MMAL_STATUS_T mmal_wrapper_port_disable(MMAL_PORT_T *port)
{
   MMAL_WRAPPER_PRIVATE_T *private = (MMAL_WRAPPER_PRIVATE_T *)port->userdata;
   MMAL_WRAPPER_T *wrapper = &private->wrapper;
   int64_t start_time = vcos_getmicrosecs();
   MMAL_STATUS_T status;

   LOG_TRACE("%p, %s", wrapper, port->name);

   if (port->type != MMAL_PORT_TYPE_INPUT && port->type != MMAL_PORT_TYPE_OUTPUT)
      return MMAL_EINVAL;

   if (!port->is_enabled)
      return MMAL_SUCCESS;

   /* Disable port */
   status = mmal_port_disable(port);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("could not disable port");
      return status;
   }

   /* Flush the queue */
   if (port->type == MMAL_PORT_TYPE_OUTPUT)
   {
      MMAL_POOL_T *pool = wrapper->output_pool[port->index];
      MMAL_QUEUE_T *queue = wrapper->output_queue[port->index];
      MMAL_BUFFER_HEADER_T *buffer;

      while ((buffer = mmal_queue_get(queue)) != NULL)
         mmal_buffer_header_release(buffer);

      if ( !vcos_verify(mmal_queue_length(pool->queue) == pool->headers_num) )
      {
         LOG_ERROR("coul dnot release all buffers");
      }
   }

   wrapper->time_disable = vcos_getmicrosecs() - start_time;
   return status;
}