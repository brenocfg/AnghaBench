#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  name; } ;
struct TYPE_17__ {struct TYPE_17__* next; } ;
struct TYPE_16__ {TYPE_9__* component; TYPE_2__* priv; int /*<<< orphan*/  is_enabled; scalar_t__ index; scalar_t__ type; } ;
struct TYPE_15__ {scalar_t__ (* pf_flush ) (TYPE_3__*) ;TYPE_1__* core; } ;
struct TYPE_14__ {TYPE_4__* queue_first; TYPE_4__** queue_last; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_SENDING (TYPE_3__*) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int,int,TYPE_3__*) ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOSYS ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  UNLOCK_SENDING (TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_component_action_lock (TYPE_9__*) ; 
 int /*<<< orphan*/  mmal_component_action_unlock (TYPE_9__*) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ stub1 (TYPE_3__*) ; 

MMAL_STATUS_T mmal_port_flush(MMAL_PORT_T *port)
{
   MMAL_BUFFER_HEADER_T *buffer = 0;
   MMAL_STATUS_T status;

   if (!port || !port->priv)
      return MMAL_EINVAL;

   LOG_TRACE("%s(%i:%i) port %p", port->component->name,
             (int)port->type, (int)port->index, port);

   if (!port->priv->pf_flush)
      return MMAL_ENOSYS;

   /* N.B. must take action lock *before* sending lock */
   mmal_component_action_lock(port->component);
   LOCK_SENDING(port);

   if (!port->is_enabled)
   {
      UNLOCK_SENDING(port);
      mmal_component_action_unlock(port->component);
      return MMAL_SUCCESS;
   }

   status = port->priv->pf_flush(port);
   if (status == MMAL_SUCCESS)
   {
      /* Flush our internal queue */
      buffer = port->priv->core->queue_first;
      port->priv->core->queue_first = 0;
      port->priv->core->queue_last = &port->priv->core->queue_first;
   }

   UNLOCK_SENDING(port);
   mmal_component_action_unlock(port->component);

   while (buffer)
   {
      MMAL_BUFFER_HEADER_T *next = buffer->next;
      mmal_port_buffer_header_callback(port, buffer);
      buffer = next;
   }
   return status;
}