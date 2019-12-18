#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ (* pf_return_buffer ) (TYPE_4__*,TYPE_1__*,TYPE_3__*) ;} ;
struct TYPE_19__ {scalar_t__ cmd; } ;
struct TYPE_18__ {TYPE_4__ graph; } ;
struct TYPE_17__ {scalar_t__ userdata; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_3__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 scalar_t__ MMAL_ENOSYS ; 
 TYPE_1__* find_port_to_graph (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_port_event_send (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ stub1 (TYPE_4__*,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void graph_port_enable_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_GRAPH_PRIVATE_T *graph_private = (MMAL_GRAPH_PRIVATE_T *)port->userdata;
   MMAL_PORT_T *graph_port;
   MMAL_STATUS_T status;

   graph_port = find_port_to_graph(graph_private, port);
   if (!graph_port)
   {
      vcos_assert(0);
      mmal_buffer_header_release(buffer);
      return;
   }

   /* Call user defined function first */
   if (graph_private->graph.pf_return_buffer)
   {
      status = graph_private->graph.pf_return_buffer(&graph_private->graph, graph_port, buffer);
      if (status != MMAL_ENOSYS)
         return;
   }

   /* Forward the callback */
   if (buffer->cmd)
      mmal_port_event_send(graph_port, buffer);
   else
      mmal_port_buffer_header_callback(graph_port, buffer);
}