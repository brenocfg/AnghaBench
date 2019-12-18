#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ (* pf_parameter_set ) (TYPE_6__*,TYPE_2__*,TYPE_3__ const*) ;} ;
struct TYPE_21__ {unsigned int input_num; unsigned int output_num; int /*<<< orphan*/ * output; int /*<<< orphan*/ * input; TYPE_1__* priv; } ;
struct TYPE_20__ {TYPE_6__ graph; } ;
struct TYPE_19__ {scalar_t__ id; } ;
struct TYPE_18__ {TYPE_5__* component; } ;
struct TYPE_17__ {TYPE_4__* module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_4__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_5__ MMAL_COMPONENT_T ;

/* Variables and functions */
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOSYS ; 
 scalar_t__ MMAL_PARAMETER_BUFFER_REQUIREMENTS ; 
 scalar_t__ MMAL_SUCCESS ; 
 TYPE_2__* find_port_from_graph (TYPE_4__*,TYPE_2__*) ; 
 scalar_t__ graph_port_update_requirements (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_parameter_set (TYPE_2__*,TYPE_3__ const*) ; 
 scalar_t__ stub1 (TYPE_6__*,TYPE_2__*,TYPE_3__ const*) ; 

__attribute__((used)) static MMAL_STATUS_T graph_port_parameter_set(MMAL_PORT_T *graph_port,
   const MMAL_PARAMETER_HEADER_T *param)
{
   MMAL_GRAPH_PRIVATE_T *graph_private = graph_port->component->priv->module;
   MMAL_STATUS_T status;
   MMAL_PORT_T *port;

   /* Call user defined function first */
   if (graph_private->graph.pf_parameter_set)
   {
      status = graph_private->graph.pf_parameter_set(&graph_private->graph, graph_port, param);
      if (status != MMAL_ENOSYS)
         return status;
   }

   port = find_port_from_graph(graph_private, graph_port);
   if (!port)
      return MMAL_EINVAL;

   /* Forward the call */
   status = mmal_port_parameter_set(port, param);
   if (status != MMAL_SUCCESS)
      goto end;

   if (param->id == MMAL_PARAMETER_BUFFER_REQUIREMENTS)
   {
      /* This might have changed the buffer requirements of other ports so fetch them all */
      MMAL_COMPONENT_T *component = graph_port->component;
      unsigned int i;
      for (i = 0; status == MMAL_SUCCESS && i < component->input_num; i++)
         status = graph_port_update_requirements(graph_private, component->input[i]);
      for (i = 0; status == MMAL_SUCCESS && i < component->output_num; i++)
         status = graph_port_update_requirements(graph_private, component->output[i]);
   }

 end:
   return status;
}