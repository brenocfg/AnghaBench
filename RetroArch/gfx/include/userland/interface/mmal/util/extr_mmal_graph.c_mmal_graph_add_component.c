#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ component_num; TYPE_2__** component; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_GRAPH_T ;
typedef  TYPE_1__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;

/* Variables and functions */
 scalar_t__ GRAPH_CONNECTIONS_MAX ; 
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ENOSPC ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_component_acquire (TYPE_2__*) ; 

MMAL_STATUS_T mmal_graph_add_component(MMAL_GRAPH_T *graph, MMAL_COMPONENT_T *component)
{
   MMAL_GRAPH_PRIVATE_T *private = (MMAL_GRAPH_PRIVATE_T *)graph;

   LOG_TRACE("graph: %p, component: %s(%p)", graph, component ? component->name: 0, component);

   if (!component)
      return MMAL_EINVAL;

   if (private->component_num >= GRAPH_CONNECTIONS_MAX)
   {
      LOG_ERROR("no space for component %s", component->name);
      return MMAL_ENOSPC;
   }

   mmal_component_acquire(component);
   private->component[private->component_num++] = component;

   return MMAL_SUCCESS;
}