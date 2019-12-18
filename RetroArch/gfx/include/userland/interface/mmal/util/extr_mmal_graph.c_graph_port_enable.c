#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* priv; } ;
struct TYPE_17__ {scalar_t__ (* pf_enable ) (TYPE_4__*,TYPE_2__*) ;} ;
struct TYPE_16__ {TYPE_4__ graph; } ;
struct TYPE_15__ {TYPE_7__* component; void* userdata; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buffer_num; } ;
struct TYPE_14__ {TYPE_3__* module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_BH_CB_T ;
typedef  TYPE_3__ MMAL_GRAPH_PRIVATE_T ;

/* Variables and functions */
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_SUCCESS ; 
 TYPE_2__* find_port_from_graph (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  graph_port_enable_cb ; 
 scalar_t__ graph_port_state_propagate (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  mmal_component_action_trigger (TYPE_7__*) ; 
 scalar_t__ mmal_port_enable (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static MMAL_STATUS_T graph_port_enable(MMAL_PORT_T *graph_port, MMAL_PORT_BH_CB_T cb)
{
   MMAL_GRAPH_PRIVATE_T *graph_private = graph_port->component->priv->module;
   MMAL_PORT_T *port;
   MMAL_STATUS_T status;
   MMAL_PARAM_UNUSED(cb);

   port = find_port_from_graph(graph_private, graph_port);
   if (!port)
      return MMAL_EINVAL;

   /* Update the buffer requirements */
   port->buffer_num = graph_port->buffer_num;
   port->buffer_size = graph_port->buffer_size;

   /* Call user defined function first */
   if (graph_private->graph.pf_enable)
   {
      status = graph_private->graph.pf_enable(&graph_private->graph, graph_port);
      if (status != MMAL_ENOSYS)
         return status;
   }

   /* We'll intercept the callback */
   port->userdata = (void *)graph_private;
   status = mmal_port_enable(port, graph_port_enable_cb);
   if (status != MMAL_SUCCESS)
      return status;

   /* We need to enable all the connected connections */
   status = graph_port_state_propagate(graph_private, port, 1);

   mmal_component_action_trigger(graph_port->component);
   return status;
}