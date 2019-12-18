#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  int /*<<< orphan*/  MMAL_GRAPH_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T aggregator_parameter_get(MMAL_GRAPH_T *graph,
      MMAL_PORT_T *port, MMAL_PARAMETER_HEADER_T *param)
{
   MMAL_PARAM_UNUSED(graph);
   MMAL_PARAM_UNUSED(port);
   MMAL_PARAM_UNUSED(param);
   LOG_TRACE("graph %p, port %p, param %p", graph, port, param);
   return MMAL_ENOSYS;
}