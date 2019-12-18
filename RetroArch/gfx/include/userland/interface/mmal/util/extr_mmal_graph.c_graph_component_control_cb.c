#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ (* pf_control_callback ) (TYPE_6__*,TYPE_2__*,TYPE_5__*) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_17__ {int /*<<< orphan*/  control; TYPE_1__* priv; } ;
struct TYPE_16__ {TYPE_6__ graph; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; scalar_t__ userdata; } ;
struct TYPE_14__ {TYPE_3__* module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;
typedef  TYPE_5__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_5__*,char*) ; 
 scalar_t__ MMAL_ENOSYS ; 
 int /*<<< orphan*/  mmal_port_event_send (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ stub1 (TYPE_6__*,TYPE_2__*,TYPE_5__*) ; 

__attribute__((used)) static void graph_component_control_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_COMPONENT_T *graph_component = (MMAL_COMPONENT_T *)port->userdata;
   MMAL_GRAPH_PRIVATE_T *graph_private = graph_component->priv->module;
   MMAL_STATUS_T status;

   LOG_TRACE("%s(%p),%p,%4.4s", port->name, port, buffer, (char *)&buffer->cmd);

   /* Call user defined function first */
   if (graph_private->graph.pf_control_callback)
   {
      status = graph_private->graph.pf_control_callback(&graph_private->graph,
         port, buffer);
      if (status != MMAL_ENOSYS)
         return;
   }

   /* Forward the event on the graph control port */
   mmal_port_event_send(graph_component->control, buffer);
}