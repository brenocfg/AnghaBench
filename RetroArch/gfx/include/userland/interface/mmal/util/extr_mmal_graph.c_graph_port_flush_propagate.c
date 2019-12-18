#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {unsigned int port_num; TYPE_10__** port; } ;
struct TYPE_16__ {unsigned int connection_num; TYPE_1__** connection; } ;
struct TYPE_15__ {scalar_t__ type; int /*<<< orphan*/  name; TYPE_4__* component; } ;
struct TYPE_14__ {TYPE_2__* in; scalar_t__ queue; TYPE_10__* out; } ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/  is_enabled; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ MMAL_PORT_TYPE_OUTPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  graph_component_topology_ports_linked (TYPE_3__*,TYPE_2__*,TYPE_10__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_flush (TYPE_2__*) ; 
 int /*<<< orphan*/ * mmal_queue_get (scalar_t__) ; 

__attribute__((used)) static MMAL_STATUS_T graph_port_flush_propagate(MMAL_GRAPH_PRIVATE_T *graph,
   MMAL_PORT_T *port)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_STATUS_T status;
   unsigned int i, j;

   LOG_TRACE("graph: %p, port %s(%p)", graph, port->name, port);

   status = mmal_port_flush(port);
   if (status != MMAL_SUCCESS)
      return status;

   if (port->type == MMAL_PORT_TYPE_OUTPUT)
      return MMAL_SUCCESS;

   /* Loop through all the output ports of the component and if they match one
    * of the connections we maintain, then we need to propagate the flush. */
   for (i = 0; i < component->port_num; i++)
   {
      if (component->port[i]->type != MMAL_PORT_TYPE_OUTPUT)
         continue;
      if (!component->port[i]->is_enabled)
         continue;

      /* Find the matching connection */
      for (j = 0; j < graph->connection_num; j++)
         if (graph->connection[j]->out == component->port[i])
            break;

      if (j == graph->connection_num)
         continue; /* No match */

      if (!graph_component_topology_ports_linked(graph, port, component->port[i]))
         continue; /* Ports are independent */

      /* Flush any buffer waiting in the connection queue */
      if (graph->connection[j]->queue)
      {
         MMAL_BUFFER_HEADER_T *buffer = mmal_queue_get(graph->connection[j]->queue);
         while(buffer)
         {
            mmal_buffer_header_release(buffer);
            buffer = mmal_queue_get(graph->connection[j]->queue);
         }
      }

      status = graph_port_flush_propagate(graph, graph->connection[j]->in);
      if (status != MMAL_SUCCESS)
         break;
   }

   return status;
}