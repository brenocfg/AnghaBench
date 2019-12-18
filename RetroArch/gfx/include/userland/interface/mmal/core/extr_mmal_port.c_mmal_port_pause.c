#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {struct TYPE_13__* next; } ;
struct TYPE_12__ {TYPE_2__* priv; scalar_t__ is_enabled; } ;
struct TYPE_11__ {scalar_t__ (* pf_send ) (TYPE_3__*,TYPE_4__*) ;TYPE_1__* core; } ;
struct TYPE_10__ {scalar_t__ is_paused; TYPE_4__* queue_first; TYPE_4__** queue_last; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_BUFFER_HEADER_T ;
typedef  scalar_t__ MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_SENDING (TYPE_3__*) ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  UNLOCK_SENDING (TYPE_3__*) ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_4__*) ; 

MMAL_STATUS_T mmal_port_pause(MMAL_PORT_T *port, MMAL_BOOL_T pause)
{
   MMAL_STATUS_T status = MMAL_SUCCESS;

   LOCK_SENDING(port);

   /* When resuming from pause, we send all our queued buffers to the port */
   if (!pause && port->is_enabled)
   {
      MMAL_BUFFER_HEADER_T *buffer = port->priv->core->queue_first;
      while (buffer)
      {
         MMAL_BUFFER_HEADER_T *next = buffer->next;
         status = port->priv->pf_send(port, buffer);
         if (status != MMAL_SUCCESS)
         {
            buffer->next = next;
            break;
         }
         buffer = next;
      }

      /* If for some reason we could not send one of the buffers, we just
       * leave all the buffers in our internal queue and return an error. */
      if (status != MMAL_SUCCESS)
      {
         port->priv->core->queue_first = buffer;
      }
      else
      {
         port->priv->core->queue_first = 0;
         port->priv->core->queue_last = &port->priv->core->queue_first;
      }
   }

   if (status == MMAL_SUCCESS)
      port->priv->core->is_paused = pause;

   UNLOCK_SENDING(port);
   return status;
}