#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  link; int /*<<< orphan*/  event; int /*<<< orphan*/ * port; } ;
struct TYPE_11__ {TYPE_3__* priv; } ;
struct TYPE_10__ {TYPE_2__* module; } ;
struct TYPE_8__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  free; } ;
struct TYPE_9__ {TYPE_1__ events; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_EVENT_T ;
typedef  TYPE_5__ CLOCK_PORT_EVENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  MMAL_ENOSPC ; 
 int /*<<< orphan*/  mmal_component_action_trigger (TYPE_4__*) ; 
 scalar_t__ mmal_list_pop_front (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_list_push_back (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T clock_event_queue(MMAL_COMPONENT_T *component, MMAL_PORT_T *port, const MMAL_CLOCK_EVENT_T *event)
{
   CLOCK_PORT_EVENT_T *slot = (CLOCK_PORT_EVENT_T*)mmal_list_pop_front(component->priv->module->events.free);
   if (!slot)
   {
      LOG_ERROR("no event slots available");
      return MMAL_ENOSPC;
   }

   slot->port = port;
   slot->event = *event;
   mmal_list_push_back(component->priv->module->events.queue, &slot->link);

   return mmal_component_action_trigger(component);
}