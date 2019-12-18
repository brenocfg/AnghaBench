#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int connection_num; unsigned int component_num; int /*<<< orphan*/  sema; int /*<<< orphan*/ * component; int /*<<< orphan*/ * connection; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* pf_destroy ) (TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_GRAPH_T ;
typedef  TYPE_2__ MMAL_GRAPH_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_component_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_connection_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

MMAL_STATUS_T mmal_graph_destroy(MMAL_GRAPH_T *graph)
{
   unsigned i;
   MMAL_GRAPH_PRIVATE_T *private = (MMAL_GRAPH_PRIVATE_T *)graph;

   if (!graph)
      return MMAL_EINVAL;

   LOG_TRACE("%p", graph);

   /* Notify client of destruction */
   if (graph->pf_destroy)
      graph->pf_destroy(graph);

   for (i = 0; i < private->connection_num; i++)
      mmal_connection_release(private->connection[i]);

   for (i = 0; i < private->component_num; i++)
      mmal_component_release(private->component[i]);

   vcos_semaphore_delete(&private->sema);

   vcos_free(graph);
   return MMAL_SUCCESS;
}