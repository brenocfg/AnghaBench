#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/ * pool_for_connection; int /*<<< orphan*/  core_owns_connection; } ;
struct TYPE_9__ {scalar_t__ type; int capabilities; TYPE_1__* priv; void* buffer_size; void* buffer_num; } ;
struct TYPE_8__ {TYPE_3__* core; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_PORT_PRIVATE_CORE_T ;
typedef  int /*<<< orphan*/  MMAL_POOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  MMAL_ENOMEM ; 
 void* MMAL_MAX (void*,void*) ; 
 int MMAL_PORT_CAPABILITY_ALLOCATION ; 
 int MMAL_PORT_CAPABILITY_PASSTHROUGH ; 
 scalar_t__ MMAL_PORT_TYPE_INPUT ; 
 scalar_t__ MMAL_PORT_TYPE_OUTPUT ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_pool_callback_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_port_connected_pool_cb ; 
 int /*<<< orphan*/ * mmal_port_pool_create (TYPE_2__*,void*,void*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_connection_enable(MMAL_PORT_T *port, MMAL_PORT_T *connected_port)
{
   MMAL_PORT_T *output = port->type == MMAL_PORT_TYPE_OUTPUT ? port : connected_port;
   MMAL_PORT_T *input = connected_port->type == MMAL_PORT_TYPE_INPUT ? connected_port : port;
   MMAL_PORT_T *pool_port = (output->capabilities & MMAL_PORT_CAPABILITY_ALLOCATION) ? output : input;
   MMAL_PORT_PRIVATE_CORE_T *pool_core = pool_port->priv->core;
   uint32_t buffer_size, buffer_num;
   MMAL_POOL_T *pool;

   /* At this point both ports hold the connection lock */

   /* Ensure that the buffer numbers and sizes used are the maxima between connected ports. */
   buffer_num  = MMAL_MAX(port->buffer_num,  connected_port->buffer_num);
   buffer_size = MMAL_MAX(port->buffer_size, connected_port->buffer_size);
   port->buffer_num  = connected_port->buffer_num  = buffer_num;
   port->buffer_size = connected_port->buffer_size = buffer_size;

   if (output->capabilities & MMAL_PORT_CAPABILITY_PASSTHROUGH)
      buffer_size = 0;

   if (!port->priv->core->core_owns_connection)
      return MMAL_SUCCESS;

   pool = mmal_port_pool_create(pool_port, buffer_num, buffer_size);
   if (!pool)
   {
      LOG_ERROR("failed to create pool for connection");
      return MMAL_ENOMEM;
   }

   pool_core->pool_for_connection = pool;
   mmal_pool_callback_set(pool, mmal_port_connected_pool_cb, output);
   return MMAL_SUCCESS;
}