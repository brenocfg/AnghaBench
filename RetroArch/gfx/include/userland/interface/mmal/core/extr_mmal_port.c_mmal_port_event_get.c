#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_16__ {scalar_t__ alloc_size; scalar_t__ length; int /*<<< orphan*/  data; scalar_t__ cmd; } ;
struct TYPE_15__ {scalar_t__ index; scalar_t__ type; TYPE_3__* component; int /*<<< orphan*/  priv; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; TYPE_2__* priv; } ;
struct TYPE_13__ {TYPE_1__* event_pool; } ;
struct TYPE_12__ {int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_EVENT_FORMAT_CHANGED_T ;
typedef  int /*<<< orphan*/  MMAL_ES_SPECIFIC_FORMAT_T ;
typedef  int /*<<< orphan*/  MMAL_ES_FORMAT_T ;
typedef  TYPE_5__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ,int,int,TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int,int,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ENOSPC ; 
 scalar_t__ MMAL_EVENT_FORMAT_CHANGED ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_5__*) ; 
 TYPE_5__* mmal_queue_get (int /*<<< orphan*/ ) ; 

MMAL_STATUS_T mmal_port_event_get(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T **buffer, uint32_t event)
{
   if (!port || !port->priv || !buffer)
      return MMAL_EINVAL;

   LOG_TRACE("%s(%i:%i) port %p, event %4.4s", port->component->name,
             (int)port->type, (int)port->index, port, (char *)&event);

   /* Get an event buffer from our event pool */
   *buffer = mmal_queue_get(port->component->priv->event_pool->queue);
   if (!*buffer)
   {
      LOG_ERROR("%s(%i:%i) port %p, no event buffer left for %4.4s", port->component->name,
                (int)port->type, (int)port->index, port, (char *)&event);
      return MMAL_ENOSPC;
   }

   (*buffer)->cmd = event;
   (*buffer)->length = 0;

   /* Special case for the FORMAT_CHANGED event. We need to properly initialise the event
    * buffer so that it contains an initialised MMAL_ES_FORMAT_T structure. */
   if (event == MMAL_EVENT_FORMAT_CHANGED)
   {
      uint32_t size = sizeof(MMAL_EVENT_FORMAT_CHANGED_T);
      size += sizeof(MMAL_ES_FORMAT_T) + sizeof(MMAL_ES_SPECIFIC_FORMAT_T);

      if ((*buffer)->alloc_size < size)
      {
         LOG_ERROR("%s(%i:%i) port %p, event buffer for %4.4s is too small (%i/%i)",
                   port->component->name, (int)port->type, (int)port->index, port,
                   (char *)&event, (int)(*buffer)->alloc_size, (int)size);
         goto error;
      }

      memset((*buffer)->data, 0, size);
      (*buffer)->length = size;
   }

   return MMAL_SUCCESS;

error:
   if (*buffer)
      mmal_buffer_header_release(*buffer);
   *buffer = NULL;
   return MMAL_ENOSPC;
}