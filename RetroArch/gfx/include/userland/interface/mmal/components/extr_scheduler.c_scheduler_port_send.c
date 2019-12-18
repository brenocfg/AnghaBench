#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  pts; int /*<<< orphan*/  cmd; } ;
struct TYPE_16__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {int /*<<< orphan*/ * clock; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_2__* priv; TYPE_4__* component; } ;
struct TYPE_13__ {TYPE_1__* module; } ;
struct TYPE_12__ {int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;
typedef  TYPE_5__ MMAL_CLOCK_BUFFER_INFO_T ;
typedef  TYPE_6__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 scalar_t__ MMAL_PORT_TYPE_INPUT ; 
 int /*<<< orphan*/  mmal_component_action_trigger (TYPE_4__*) ; 
 int /*<<< orphan*/  mmal_port_clock_input_buffer_info (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_queue_put (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  vcos_getmicrosecs () ; 

__attribute__((used)) static MMAL_STATUS_T scheduler_port_send(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_COMPONENT_T *component = port->component;

   /* notify the clock port */
   if (port->type == MMAL_PORT_TYPE_INPUT && !buffer->cmd)
   {
      MMAL_CLOCK_BUFFER_INFO_T info = { buffer->pts, vcos_getmicrosecs() };
      mmal_port_clock_input_buffer_info(port->component->clock[0], &info);
   }

   mmal_queue_put(port->priv->module->queue, buffer);
   return mmal_component_action_trigger(component);
}