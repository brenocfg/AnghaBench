#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* priv; } ;
struct TYPE_14__ {TYPE_1__* priv; } ;
struct TYPE_13__ {TYPE_9__* component; } ;
struct TYPE_12__ {TYPE_2__* module; } ;
struct TYPE_11__ {int /*<<< orphan*/  callback_queue; } ;
struct TYPE_10__ {void* component_data; } ;
typedef  TYPE_4__ MMAL_PORT_T ;
typedef  TYPE_5__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_component_action_trigger (TYPE_9__*) ; 
 int /*<<< orphan*/  mmal_queue_put (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static void mmal_vc_port_send_event_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   /* Queue the event to be delivered by the action thread */
   buffer->priv->component_data = (void *)port;
   mmal_queue_put(port->component->priv->module->callback_queue, buffer);
   mmal_component_action_trigger(port->component);
}