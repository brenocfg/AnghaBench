#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_16__ {scalar_t__ (* pf_payload_alloc ) (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;} ;
struct TYPE_15__ {TYPE_5__ graph; } ;
struct TYPE_14__ {TYPE_2__* component; } ;
struct TYPE_13__ {TYPE_1__* priv; } ;
struct TYPE_12__ {TYPE_4__* module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_GRAPH_PRIVATE_T ;

/* Variables and functions */
 scalar_t__ MMAL_ENOSYS ; 
 scalar_t__ MMAL_SUCCESS ; 
 TYPE_3__* find_port_from_graph (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * mmal_port_payload_alloc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static uint8_t *graph_port_payload_alloc(MMAL_PORT_T *graph_port, uint32_t payload_size)
{
   MMAL_GRAPH_PRIVATE_T *graph_private = graph_port->component->priv->module;
   MMAL_STATUS_T status;
   MMAL_PORT_T *port;
   uint8_t *payload;

   port = find_port_from_graph(graph_port->component->priv->module, graph_port);
   if (!port)
      return 0;

   /* Call user defined function first */
   if (graph_private->graph.pf_payload_alloc)
   {
      status = graph_private->graph.pf_payload_alloc(&graph_private->graph, graph_port,
         payload_size, &payload);
      if (status != MMAL_ENOSYS)
         return status == MMAL_SUCCESS ? payload : NULL;
   }

   /* Forward the call */
   return mmal_port_payload_alloc(port, payload_size);
}