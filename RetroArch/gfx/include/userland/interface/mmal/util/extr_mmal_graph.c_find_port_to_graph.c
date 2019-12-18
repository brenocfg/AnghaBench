#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__** clock; TYPE_1__** output; TYPE_1__** input; } ;
struct TYPE_8__ {unsigned int input_num; unsigned int output_num; unsigned int clock_num; TYPE_1__** clock; TYPE_1__** output; TYPE_1__** input; TYPE_3__* graph_component; } ;
struct TYPE_7__ {int type; } ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;

/* Variables and functions */
#define  MMAL_PORT_TYPE_CLOCK 130 
#define  MMAL_PORT_TYPE_INPUT 129 
#define  MMAL_PORT_TYPE_OUTPUT 128 

__attribute__((used)) static MMAL_PORT_T *find_port_to_graph(MMAL_GRAPH_PRIVATE_T *graph, MMAL_PORT_T *port)
{
   MMAL_COMPONENT_T *component = graph->graph_component;
   MMAL_PORT_T **list, **component_list;
   unsigned int i, *list_num;

   switch (port->type)
   {
   case MMAL_PORT_TYPE_INPUT:
      list = graph->input;
      list_num = &graph->input_num;
      component_list = component->input;
      break;
   case MMAL_PORT_TYPE_OUTPUT:
      list = graph->output;
      list_num = &graph->output_num;
      component_list = component->output;
      break;
   case MMAL_PORT_TYPE_CLOCK:
      list = graph->clock;
      list_num = &graph->clock_num;
      component_list = component->clock;
      break;
   default:
      return 0;
   }

   for (i = 0; i < *list_num; i++)
      if (list[i] == port)
         break;

   if (i == *list_num)
      return 0;
   return component_list[i];
}