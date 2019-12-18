#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* pf_graph_enable ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {TYPE_4__ graph; } ;
struct TYPE_6__ {TYPE_2__* module; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T graph_component_enable(MMAL_COMPONENT_T *component)
{
   MMAL_GRAPH_PRIVATE_T *graph_private = component->priv->module;
   MMAL_STATUS_T status = MMAL_ENOSYS;

   /* Call user defined function first */
   if (graph_private->graph.pf_graph_enable)
      status = graph_private->graph.pf_graph_enable(&graph_private->graph, MMAL_TRUE);

   return status;
}