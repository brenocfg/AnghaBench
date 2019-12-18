#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* pf_destroy ) (TYPE_4__*) ;} ;
struct TYPE_9__ {TYPE_4__ graph; } ;
struct TYPE_8__ {scalar_t__ clock_num; int /*<<< orphan*/  clock; scalar_t__ output_num; int /*<<< orphan*/  output; scalar_t__ input_num; int /*<<< orphan*/  input; TYPE_1__* priv; } ;
struct TYPE_7__ {TYPE_3__* module; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;
typedef  TYPE_3__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_graph_destroy (TYPE_4__*) ; 
 int /*<<< orphan*/  mmal_ports_clock_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmal_ports_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static MMAL_STATUS_T graph_component_destroy(MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_MODULE_T *graph = component->priv->module;

   /* Notify client of destruction */
   if (graph->graph.pf_destroy)
      graph->graph.pf_destroy(&graph->graph);
   graph->graph.pf_destroy = NULL;

   if (component->input_num)
      mmal_ports_free(component->input, component->input_num);

   if (component->output_num)
      mmal_ports_free(component->output, component->output_num);

   if (component->clock_num)
      mmal_ports_clock_free(component->clock, component->clock_num);

   /* coverity[address_free] Freeing the first item in the structure is safe */
   mmal_graph_destroy(&graph->graph);
   return MMAL_SUCCESS;
}