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
struct TYPE_6__ {unsigned int input_num; unsigned int output_num; unsigned int clock_num; TYPE_1__** clock; TYPE_1__** output; TYPE_1__** input; } ;
struct TYPE_5__ {int type; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_GRAPH_T ;
typedef  TYPE_2__ MMAL_GRAPH_PRIVATE_T ;

/* Variables and functions */
 unsigned int GRAPH_CONNECTIONS_MAX ; 
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ENOSPC ; 
#define  MMAL_PORT_TYPE_CLOCK 130 
#define  MMAL_PORT_TYPE_INPUT 129 
#define  MMAL_PORT_TYPE_OUTPUT 128 
 int /*<<< orphan*/  MMAL_SUCCESS ; 

MMAL_STATUS_T mmal_graph_add_port(MMAL_GRAPH_T *graph, MMAL_PORT_T *port)
{
   MMAL_GRAPH_PRIVATE_T *private = (MMAL_GRAPH_PRIVATE_T *)graph;
   MMAL_PORT_T **list;
   unsigned int *list_num;

   LOG_TRACE("graph: %p, port: %s(%p)", graph, port ? port->name: 0, port);

   if (!port)
      return MMAL_EINVAL;

   switch (port->type)
   {
   case MMAL_PORT_TYPE_INPUT:
      list = private->input;
      list_num = &private->input_num;
      break;
   case MMAL_PORT_TYPE_OUTPUT:
      list = private->output;
      list_num = &private->output_num;
      break;
   case MMAL_PORT_TYPE_CLOCK:
      list = private->clock;
      list_num = &private->clock_num;
      break;
   default:
      return MMAL_EINVAL;
   }

   if (*list_num >= GRAPH_CONNECTIONS_MAX)
   {
      LOG_ERROR("no space for port %s", port->name);
      return MMAL_ENOSPC;
   }

   list[(*list_num)++] = port;
   return MMAL_SUCCESS;
}