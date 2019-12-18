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

/* Type definitions */
struct TYPE_17__ {unsigned int output_num; TYPE_2__** output; } ;
struct TYPE_16__ {unsigned int connection_num; TYPE_1__** connection; } ;
struct TYPE_15__ {scalar_t__ type; int /*<<< orphan*/  format; scalar_t__ is_enabled; int /*<<< orphan*/  name; TYPE_4__* component; } ;
struct TYPE_14__ {TYPE_2__* out; TYPE_2__* in; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ MMAL_PORT_TYPE_CLOCK ; 
 scalar_t__ MMAL_PORT_TYPE_OUTPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  graph_component_topology_ports_linked (TYPE_3__*,TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ mmal_format_full_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_log_dump_port (TYPE_2__*) ; 
 scalar_t__ mmal_port_format_commit (TYPE_2__*) ; 

__attribute__((used)) static MMAL_STATUS_T graph_port_format_commit_propagate(MMAL_GRAPH_PRIVATE_T *graph,
   MMAL_PORT_T *port)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_STATUS_T status = MMAL_SUCCESS;
   unsigned int i, j;

   LOG_TRACE("graph: %p, port %s(%p)", graph, port->name, port);

   if (port->type == MMAL_PORT_TYPE_OUTPUT || port->type == MMAL_PORT_TYPE_CLOCK)
      return MMAL_SUCCESS; /* Nothing to do */

   /* Loop through all the output ports of the component and if they are not enabled and
    * match one of the connections we maintain, then we need to propagate the format change. */
   for (i = 0; i < component->output_num; i++)
   {
      MMAL_PORT_T *in, *out;

      if (component->output[i]->is_enabled)
         continue;

      /* Find the matching connection */
      for (j = 0; j < graph->connection_num; j++)
         if (graph->connection[j]->out == component->output[i])
            break;

      if (j == graph->connection_num)
         continue; /* No match */

      if (!graph_component_topology_ports_linked(graph, port, component->output[i]))
         continue; /* Ports are independent */

      in = graph->connection[j]->in;
      out = graph->connection[j]->out;

      /* Apply the format to the input port */
      status = mmal_format_full_copy(in->format, out->format);
      if (status != MMAL_SUCCESS)
         break;
      status = mmal_port_format_commit(in);
      if (status != MMAL_SUCCESS)
         break;

      mmal_log_dump_port(out);
      mmal_log_dump_port(in);

      status = graph_port_format_commit_propagate(graph, in);
      if (status != MMAL_SUCCESS)
         break;
   }

   return status;
}