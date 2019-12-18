#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_12__ {int /*<<< orphan*/  event_cb_data; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {scalar_t__ index; scalar_t__ type; int /*<<< orphan*/  name; scalar_t__ userdata; } ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_GRAPH_T ;
typedef  TYPE_2__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_3__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void graph_control_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_GRAPH_PRIVATE_T *graph = (MMAL_GRAPH_PRIVATE_T *)port->userdata;

   LOG_TRACE("port: %s(%p), buffer: %p, event: %4.4s", port->name, port,
             buffer, (char *)&buffer->cmd);

   if (graph->event_cb)
   {
      graph->event_cb((MMAL_GRAPH_T *)graph, port, buffer, graph->event_cb_data);
   }
   else
   {
      LOG_ERROR("event lost on port %i,%i (event callback not defined)",
                (int)port->type, (int)port->index);
      mmal_buffer_header_release(buffer);
   }
}