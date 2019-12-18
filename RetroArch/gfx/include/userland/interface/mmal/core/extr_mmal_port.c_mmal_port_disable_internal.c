#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {struct TYPE_18__* next; } ;
struct TYPE_17__ {int /*<<< orphan*/ * buffer_header_callback; TYPE_4__* queue_first; TYPE_4__** queue_last; scalar_t__ pool_for_connection; } ;
struct TYPE_16__ {int is_enabled; TYPE_1__* priv; int /*<<< orphan*/  name; int /*<<< orphan*/  component; } ;
struct TYPE_15__ {scalar_t__ (* pf_disable ) (TYPE_2__*) ;TYPE_3__* core; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_PORT_PRIVATE_CORE_T ;
typedef  TYPE_4__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 scalar_t__ IN_TRANSIT_COUNT (TYPE_2__*) ; 
 int /*<<< orphan*/  IN_TRANSIT_WAIT (TYPE_2__*) ; 
 int /*<<< orphan*/  LOCK_PORT (TYPE_2__*) ; 
 int /*<<< orphan*/  LOCK_SENDING (TYPE_2__*) ; 
 int /*<<< orphan*/  LOG_DEBUG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  UNLOCK_PORT (TYPE_2__*) ; 
 int /*<<< orphan*/  UNLOCK_SENDING (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_component_action_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_component_action_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_pool_callback_set (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mmal_status_to_string (scalar_t__) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_disable_internal(MMAL_PORT_T *port)
{
   MMAL_PORT_PRIVATE_CORE_T* core = port->priv->core;
   MMAL_STATUS_T status = MMAL_SUCCESS;
   MMAL_BUFFER_HEADER_T *buffer;

   LOCK_PORT(port);

   if (!port->is_enabled)
      goto end;

   LOCK_SENDING(port);
   port->is_enabled = 0;
   UNLOCK_SENDING(port);

   mmal_component_action_lock(port->component);

   if (core->pool_for_connection)
      mmal_pool_callback_set(core->pool_for_connection, NULL, NULL);

   status = port->priv->pf_disable(port);

   mmal_component_action_unlock(port->component);

   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("port %p could not be disabled (%s)", port->name, mmal_status_to_string(status));
      LOCK_SENDING(port);
      port->is_enabled = 1;
      UNLOCK_SENDING(port);
      goto end;
   }

   /* Flush our internal queue */
   buffer = port->priv->core->queue_first;
   while (buffer)
   {
      MMAL_BUFFER_HEADER_T *next = buffer->next;
      mmal_port_buffer_header_callback(port, buffer);
      buffer = next;
   }
   port->priv->core->queue_first = 0;
   port->priv->core->queue_last = &port->priv->core->queue_first;

   /* Wait for all the buffers to have come back from the component */
   LOG_DEBUG("%s waiting for %i buffers left in transit", port->name, (int)IN_TRANSIT_COUNT(port));
   IN_TRANSIT_WAIT(port);
   LOG_DEBUG("%s has no buffers left in transit", port->name);

   port->priv->core->buffer_header_callback = NULL;

 end:
   UNLOCK_PORT(port);
   return status;
}