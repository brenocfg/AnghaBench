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
struct TYPE_7__ {unsigned int component_num; scalar_t__* topology; int /*<<< orphan*/ ** component; } ;
struct TYPE_6__ {scalar_t__ index; int /*<<< orphan*/ * component; } ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_GRAPH_PRIVATE_T ;
typedef  int /*<<< orphan*/  MMAL_COMPONENT_T ;
typedef  int MMAL_BOOL_T ;

/* Variables and functions */
 int MMAL_FALSE ; 
 scalar_t__ MMAL_GRAPH_TOPOLOGY_STRAIGHT ; 
 int MMAL_TRUE ; 

__attribute__((used)) static MMAL_BOOL_T graph_component_topology_ports_linked(MMAL_GRAPH_PRIVATE_T *graph,
   MMAL_PORT_T *port1, MMAL_PORT_T *port2)
{
   MMAL_COMPONENT_T *component = port1->component;
   unsigned int i;

   for (i = 0; i < graph->component_num; i++)
      if (component == graph->component[i])
         break;

   if (i == graph->component_num)
      return MMAL_FALSE; /* Component not found */

   if (graph->topology[i] == MMAL_GRAPH_TOPOLOGY_STRAIGHT)
      return port1->index == port2->index;

   return MMAL_TRUE;
}