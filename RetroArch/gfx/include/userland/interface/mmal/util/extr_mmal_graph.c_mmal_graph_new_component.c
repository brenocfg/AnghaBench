#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ component_num; int /*<<< orphan*/ ** component; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_GRAPH_T ;
typedef  TYPE_1__ MMAL_GRAPH_PRIVATE_T ;
typedef  int /*<<< orphan*/  MMAL_COMPONENT_T ;

/* Variables and functions */
 scalar_t__ GRAPH_CONNECTIONS_MAX ; 
 int /*<<< orphan*/  LOG_ERROR (char*,char const*,...) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ MMAL_ENOSPC ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_component_acquire (int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_component_create (char const*,int /*<<< orphan*/ **) ; 

MMAL_STATUS_T mmal_graph_new_component(MMAL_GRAPH_T *graph, const char *name,
   MMAL_COMPONENT_T **component)
{
   MMAL_GRAPH_PRIVATE_T *private = (MMAL_GRAPH_PRIVATE_T *)graph;
   MMAL_COMPONENT_T *comp;
   MMAL_STATUS_T status;

   LOG_TRACE("graph: %p, name: %s, component: %p", graph, name, component);

   if (private->component_num >= GRAPH_CONNECTIONS_MAX)
   {
      LOG_ERROR("no space for component %s", name);
      return MMAL_ENOSPC;
   }

   status = mmal_component_create(name, &comp);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("could not create component %s (%i)", name, status);
      return status;
   }

   private->component[private->component_num++] = comp;
   if (component)
   {
      mmal_component_acquire(comp);
      *component = comp;
   }

   return MMAL_SUCCESS;
}