#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ length; } ;
struct TYPE_13__ {TYPE_7__* buffer; } ;
struct TYPE_15__ {TYPE_4__ event; int /*<<< orphan*/  port; int /*<<< orphan*/  link; } ;
struct TYPE_14__ {TYPE_3__* priv; } ;
struct TYPE_12__ {TYPE_2__* module; } ;
struct TYPE_10__ {int /*<<< orphan*/  free; int /*<<< orphan*/  queue; } ;
struct TYPE_11__ {TYPE_1__ events; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_5__ MMAL_COMPONENT_T ;
typedef  TYPE_6__ CLOCK_PORT_EVENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ mmal_list_pop_front (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_list_push_back (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (int /*<<< orphan*/ ,TYPE_7__*) ; 

__attribute__((used)) static MMAL_STATUS_T clock_event_dequeue(MMAL_COMPONENT_T *component, CLOCK_PORT_EVENT_T *port_event)
{
   CLOCK_PORT_EVENT_T *slot = (CLOCK_PORT_EVENT_T*)mmal_list_pop_front(component->priv->module->events.queue);
   if (!slot)
      return MMAL_EINVAL;

   port_event->port = slot->port;
   port_event->event = slot->event;
   mmal_list_push_back(component->priv->module->events.free, &slot->link);

   if (port_event->event.buffer)
   {
      port_event->event.buffer->length = 0;
      mmal_port_buffer_header_callback(port_event->port, port_event->event.buffer);
   }

   return MMAL_SUCCESS;
}