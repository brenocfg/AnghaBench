#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; void* userdata; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buffer_num; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_QUEUE_T ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_POOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_ENOMEM ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  generic_output_port_cb ; 
 int /*<<< orphan*/  mmal_pool_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_enable (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmal_port_pool_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmal_queue_create () ; 
 int /*<<< orphan*/  mmal_queue_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T setup_output_port(MMAL_PORT_T *output_port, MMAL_QUEUE_T **p_queue, MMAL_POOL_T **p_pool)
{
   MMAL_STATUS_T status = MMAL_ENOMEM;
   MMAL_QUEUE_T *queue = NULL;
   MMAL_POOL_T *pool = NULL;

   /* Create a queue for frames filled by the output port.
    * The main loop will pass these on to the input port. */
   queue = mmal_queue_create();
   if (!queue)
   {
      LOG_ERROR("failed to create queue for %s", output_port->name);
      goto error;
   }

   /* Create pool of buffer headers for the output port to consume */
   pool = mmal_port_pool_create(output_port, output_port->buffer_num, output_port->buffer_size);
   if (!pool)
   {
      LOG_ERROR("failed to create pool for %s", output_port->name);
      goto error;
   }

   output_port->userdata = (void *)queue;

   status = mmal_port_enable(output_port, generic_output_port_cb);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("failed to enable %s", output_port->name);
      goto error;
   }

   *p_queue = queue;
   *p_pool = pool;

   return MMAL_SUCCESS;

error:
   if (queue)
      mmal_queue_destroy(queue);
   if (pool)
      mmal_pool_destroy(pool);

   return status;
}