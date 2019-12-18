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
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* in; TYPE_1__* out; } ;
struct TYPE_16__ {unsigned int port_num; TYPE_1__** port; } ;
struct TYPE_15__ {unsigned int connection_num; TYPE_5__** connection; } ;
struct TYPE_14__ {scalar_t__ type; scalar_t__ is_enabled; int /*<<< orphan*/  name; TYPE_3__* component; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  scalar_t__ MMAL_PORT_TYPE_T ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;
typedef  scalar_t__ MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ MMAL_PORT_TYPE_INPUT ; 
 scalar_t__ MMAL_PORT_TYPE_OUTPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  graph_component_topology_ports_linked (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ mmal_connection_disable (TYPE_5__*) ; 
 scalar_t__ mmal_connection_enable (TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_log_dump_port (TYPE_1__*) ; 

__attribute__((used)) static MMAL_STATUS_T graph_port_state_propagate(MMAL_GRAPH_PRIVATE_T *graph,
   MMAL_PORT_T *port, MMAL_BOOL_T enable)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_STATUS_T status = MMAL_SUCCESS;
   MMAL_PORT_TYPE_T type = port->type;
   unsigned int i, j;

   LOG_TRACE("graph: %p, port %s(%p)", graph, port->name, port);

   if (port->type == MMAL_PORT_TYPE_OUTPUT)
      type = MMAL_PORT_TYPE_INPUT;
   if (port->type == MMAL_PORT_TYPE_INPUT)
      type = MMAL_PORT_TYPE_OUTPUT;

   /* Loop through all the output ports of the component and if they are not enabled and
    * match one of the connections we maintain, then we need to propagate the port enable. */
   for (i = 0; i < component->port_num; i++)
   {
      if (component->port[i]->type != type)
         continue;

      if ((component->port[i]->is_enabled && enable) ||
          (!component->port[i]->is_enabled && !enable))
         continue;

      /* Find the matching connection */
      for (j = 0; j < graph->connection_num; j++)
         if (graph->connection[j]->out == component->port[i] ||
             graph->connection[j]->in == component->port[i])
            break;

      if (j == graph->connection_num)
         continue; /* No match */

      if (!graph_component_topology_ports_linked(graph, port, component->port[i]))
            continue; /* Ports are independent */

      if (enable)
      {
         status = mmal_connection_enable(graph->connection[j]);
         if (status != MMAL_SUCCESS)
            break;

         mmal_log_dump_port(graph->connection[j]->out);
         mmal_log_dump_port(graph->connection[j]->in);
      }

      status = graph_port_state_propagate(graph, graph->connection[j]->in == component->port[i] ?
         graph->connection[j]->out : graph->connection[j]->in, enable);
      if (status != MMAL_SUCCESS)
         break;

      if (!enable)
      {
         status = mmal_connection_disable(graph->connection[j]);
         if (status != MMAL_SUCCESS)
            break;
      }
   }

   return status;
}