#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  queue; } ;
struct TYPE_9__ {scalar_t__ type; size_t index; int /*<<< orphan*/  name; scalar_t__ userdata; } ;
struct TYPE_7__ {scalar_t__ status; TYPE_4__** output_pool; TYPE_4__** input_pool; } ;
struct TYPE_8__ {int /*<<< orphan*/  sema; TYPE_1__ wrapper; } ;
typedef  TYPE_1__ MMAL_WRAPPER_T ;
typedef  TYPE_2__ MMAL_WRAPPER_PRIVATE_T ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_POOL_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_EAGAIN ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_PORT_TYPE_INPUT ; 
 scalar_t__ MMAL_PORT_TYPE_OUTPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 int MMAL_WRAPPER_FLAG_WAIT ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 

MMAL_STATUS_T mmal_wrapper_buffer_get_empty(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T **buffer,
   uint32_t flags)
{
   MMAL_WRAPPER_PRIVATE_T *private = (MMAL_WRAPPER_PRIVATE_T *)port->userdata;
   MMAL_WRAPPER_T *wrapper = &private->wrapper;
   MMAL_POOL_T *pool;

   LOG_TRACE("%p, %s", wrapper, port->name);

   if (!buffer || (port->type != MMAL_PORT_TYPE_INPUT && port->type != MMAL_PORT_TYPE_OUTPUT))
      return MMAL_EINVAL;

   pool = port->type == MMAL_PORT_TYPE_INPUT ?
      wrapper->input_pool[port->index] : wrapper->output_pool[port->index];

   while (wrapper->status == MMAL_SUCCESS &&
          (*buffer = mmal_queue_get(pool->queue)) == NULL)
   {
      if (!(flags & MMAL_WRAPPER_FLAG_WAIT))
         break;
      vcos_semaphore_wait(&private->sema);
   }

   return wrapper->status == MMAL_SUCCESS && !*buffer ? MMAL_EAGAIN : wrapper->status;
}