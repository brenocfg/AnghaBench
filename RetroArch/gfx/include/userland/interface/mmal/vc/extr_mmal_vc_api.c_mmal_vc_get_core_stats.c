#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  reply ;
struct TYPE_4__ {int /*<<< orphan*/  component_name; int /*<<< orphan*/  result; int /*<<< orphan*/  stats; } ;
typedef  TYPE_1__ mmal_worker_get_core_stats_for_port_reply ;
struct TYPE_5__ {unsigned int component_index; unsigned int port_index; int /*<<< orphan*/  header; int /*<<< orphan*/  dir; int /*<<< orphan*/  reset; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ mmal_worker_get_core_stats_for_port ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_STATS_RESULT_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_TYPE_T ;
typedef  int /*<<< orphan*/  MMAL_CORE_STATS_DIR ;
typedef  int /*<<< orphan*/  MMAL_CORE_STATISTICS_T ;
typedef  int /*<<< orphan*/  MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_FALSE ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_WORKER_GET_CORE_STATS_FOR_PORT ; 
 int /*<<< orphan*/  mmal_vc_get_client () ; 
 scalar_t__ mmal_vc_sendwait_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

MMAL_STATUS_T mmal_vc_get_core_stats(MMAL_CORE_STATISTICS_T *stats,
                                     MMAL_STATS_RESULT_T *result,
                                     char *name,
                                     size_t namelen,
                                     MMAL_PORT_TYPE_T type,
                                     unsigned component_index,
                                     unsigned port_index,
                                     MMAL_CORE_STATS_DIR dir,
                                     MMAL_BOOL_T reset)
{
   mmal_worker_get_core_stats_for_port req;
   mmal_worker_get_core_stats_for_port_reply reply;
   MMAL_STATUS_T status;
   size_t len = sizeof(reply);

   req.component_index = component_index;
   req.port_index = port_index;
   req.type = type;
   req.reset = reset;
   req.dir = dir;

   status = mmal_vc_sendwait_message(mmal_vc_get_client(),
                                     &req.header, sizeof(req),
                                     MMAL_WORKER_GET_CORE_STATS_FOR_PORT,
                                     &reply, &len, MMAL_FALSE);

   if (status == MMAL_SUCCESS)
   {
      vcos_assert(len == sizeof(reply));
      *stats = reply.stats;
      *result = reply.result;
      strncpy(name, reply.component_name, namelen);
      name[namelen-1] = '\0';
   }
   return status;
}