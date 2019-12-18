#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ (* pf_disable ) (TYPE_5__*,TYPE_3__*) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  input_num; TYPE_5__ graph; } ;
struct TYPE_16__ {scalar_t__ type; TYPE_2__* component; } ;
struct TYPE_15__ {TYPE_1__* priv; } ;
struct TYPE_14__ {TYPE_4__* module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_GRAPH_PRIVATE_T ;

/* Variables and functions */
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOSYS ; 
 scalar_t__ MMAL_PORT_TYPE_INPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 TYPE_3__* find_port_from_graph (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ graph_port_state_propagate (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_disable (TYPE_3__*) ; 
 scalar_t__ stub1 (TYPE_5__*,TYPE_3__*) ; 

__attribute__((used)) static MMAL_STATUS_T graph_port_disable(MMAL_PORT_T *graph_port)
{
   MMAL_GRAPH_PRIVATE_T *graph_private = graph_port->component->priv->module;
   MMAL_STATUS_T status;
   MMAL_PORT_T *port;

   port = find_port_from_graph(graph_port->component->priv->module, graph_port);
   if (!port)
      return MMAL_EINVAL;

   /* Call user defined function first */
   if (graph_private->graph.pf_disable)
   {
      status = graph_private->graph.pf_disable(&graph_private->graph, graph_port);
      if (status != MMAL_ENOSYS)
         return status;
   }

   /* We need to disable all the connected connections.
    * Since disable does an implicit flush, we only want to do that if
    * we're acting on an input port or we risk discarding buffers along
    * the way. */
   if (!graph_private->input_num || port->type == MMAL_PORT_TYPE_INPUT)
   {
      MMAL_STATUS_T status = graph_port_state_propagate(graph_private, port, 0);
      if (status != MMAL_SUCCESS)
         return status;
   }

   /* Forward the call */
   return mmal_port_disable(port);
}