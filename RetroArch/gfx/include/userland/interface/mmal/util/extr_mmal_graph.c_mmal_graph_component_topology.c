#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {unsigned int component_num; scalar_t__* topology; TYPE_2__** component; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  scalar_t__ MMAL_GRAPH_TOPOLOGY_T ;
typedef  int /*<<< orphan*/  MMAL_GRAPH_T ;
typedef  TYPE_1__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ENOSYS ; 
 scalar_t__ MMAL_GRAPH_TOPOLOGY_STRAIGHT ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (unsigned int) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 

MMAL_STATUS_T mmal_graph_component_topology(MMAL_GRAPH_T *graph, MMAL_COMPONENT_T *component,
    MMAL_GRAPH_TOPOLOGY_T topology, int8_t *input, unsigned int input_num,
    int8_t *output, unsigned int output_num)
{
   MMAL_GRAPH_PRIVATE_T *private = (MMAL_GRAPH_PRIVATE_T *)graph;
   MMAL_PARAM_UNUSED(input); MMAL_PARAM_UNUSED(input_num);
   MMAL_PARAM_UNUSED(output); MMAL_PARAM_UNUSED(output_num);
   unsigned int i;

   LOG_TRACE("graph: %p, component: %s(%p)", graph, component ? component->name: 0, component);

   if (!component)
      return MMAL_EINVAL;

   for (i = 0; i < private->component_num; i++)
      if (component == private->component[i])
         break;

   if (i == private->component_num)
      return MMAL_EINVAL; /* Component not found */

   if (topology > MMAL_GRAPH_TOPOLOGY_STRAIGHT)
      return MMAL_ENOSYS; /* Currently not supported */

   private->topology[i] = topology;

   return MMAL_SUCCESS;
}