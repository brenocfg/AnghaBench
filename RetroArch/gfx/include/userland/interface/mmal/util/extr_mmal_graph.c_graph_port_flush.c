#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ (* pf_flush ) (TYPE_5__*,TYPE_3__*) ;} ;
struct TYPE_16__ {TYPE_5__ graph; } ;
struct TYPE_15__ {TYPE_2__* component; } ;
struct TYPE_14__ {TYPE_1__* priv; } ;
struct TYPE_13__ {TYPE_4__* module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_GRAPH_PRIVATE_T ;

/* Variables and functions */
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOSYS ; 
 TYPE_3__* find_port_from_graph (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ graph_port_flush_propagate (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ stub1 (TYPE_5__*,TYPE_3__*) ; 

__attribute__((used)) static MMAL_STATUS_T graph_port_flush(MMAL_PORT_T *graph_port)
{
   MMAL_GRAPH_PRIVATE_T *graph_private = graph_port->component->priv->module;
   MMAL_STATUS_T status;
   MMAL_PORT_T *port;

   port = find_port_from_graph(graph_private, graph_port);
   if (!port)
      return MMAL_EINVAL;

   /* Call user defined function first */
   if (graph_private->graph.pf_flush)
   {
      status = graph_private->graph.pf_flush(&graph_private->graph, graph_port);
      if (status != MMAL_ENOSYS)
         return status;
   }

   /* Forward the call */
   return graph_port_flush_propagate(graph_private, port);
}