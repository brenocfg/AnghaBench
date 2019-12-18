#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  buffer_alignment_min; int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_size_min; int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_num_min; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_GRAPH_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 TYPE_1__* find_port_from_graph (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static MMAL_STATUS_T graph_port_update_requirements(MMAL_GRAPH_PRIVATE_T *graph,
   MMAL_PORT_T *graph_port)
{
   MMAL_PORT_T *port;

   port = find_port_from_graph(graph, graph_port);
   if (!port)
   {
      LOG_ERROR("could not find matching port for %p", graph_port);
      return MMAL_EINVAL;
   }

   graph_port->buffer_num_min = port->buffer_num_min;
   graph_port->buffer_num_recommended = port->buffer_num_recommended;
   graph_port->buffer_size_min = port->buffer_size_min;
   graph_port->buffer_size_recommended = port->buffer_size_recommended;
   graph_port->buffer_alignment_min = port->buffer_alignment_min;
   return MMAL_SUCCESS;
}