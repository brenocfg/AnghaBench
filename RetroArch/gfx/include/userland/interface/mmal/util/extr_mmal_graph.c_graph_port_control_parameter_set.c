#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ (* pf_parameter_set ) (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/  const*) ;} ;
struct TYPE_13__ {unsigned int component_num; TYPE_1__** component; TYPE_6__ graph; } ;
struct TYPE_12__ {TYPE_3__* component; } ;
struct TYPE_11__ {TYPE_2__* priv; } ;
struct TYPE_10__ {TYPE_5__* module; } ;
struct TYPE_9__ {int /*<<< orphan*/  control; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_5__ MMAL_GRAPH_PRIVATE_T ;

/* Variables and functions */
 scalar_t__ MMAL_ENOSYS ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ stub1 (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static MMAL_STATUS_T graph_port_control_parameter_set(MMAL_PORT_T *graph_port,
   const MMAL_PARAMETER_HEADER_T *param)
{
   MMAL_GRAPH_PRIVATE_T *graph_private = graph_port->component->priv->module;
   MMAL_STATUS_T status = MMAL_ENOSYS;
   unsigned int i;

   /* Call user defined function first */
   if (graph_private->graph.pf_parameter_set)
   {
      status = graph_private->graph.pf_parameter_set(&graph_private->graph, graph_port, param);
      if (status != MMAL_ENOSYS)
         return status;
   }

   /* By default we do a set parameter on each component until one succeeds */
   for (i = 0; i < graph_private->component_num && status != MMAL_SUCCESS; i++)
      status = mmal_port_parameter_set(graph_private->component[i]->control, param);

   return status;
}