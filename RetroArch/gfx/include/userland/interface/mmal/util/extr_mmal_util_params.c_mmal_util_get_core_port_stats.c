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
typedef  int /*<<< orphan*/  param ;
struct TYPE_5__ {int size; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  stats; TYPE_2__ hdr; int /*<<< orphan*/  reset; int /*<<< orphan*/  dir; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_1__ MMAL_PARAMETER_CORE_STATISTICS_T ;
typedef  int /*<<< orphan*/  MMAL_CORE_STATS_DIR ;
typedef  int /*<<< orphan*/  MMAL_CORE_STATISTICS_T ;
typedef  int /*<<< orphan*/  MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_CORE_STATISTICS ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmal_port_parameter_get (int /*<<< orphan*/ *,TYPE_2__*) ; 

MMAL_STATUS_T mmal_util_get_core_port_stats(MMAL_PORT_T *port,
                                            MMAL_CORE_STATS_DIR dir,
                                            MMAL_BOOL_T reset,
                                            MMAL_CORE_STATISTICS_T *stats)
{
   MMAL_PARAMETER_CORE_STATISTICS_T param;
   MMAL_STATUS_T ret;

   memset(&param, 0, sizeof(param));
   param.hdr.id = MMAL_PARAMETER_CORE_STATISTICS;
   param.hdr.size = sizeof(param);
   param.dir = dir;
   param.reset = reset;
   // coverity[overrun-buffer-val] Structure accessed correctly via size field
   ret = mmal_port_parameter_get(port, &param.hdr);
   if (ret == MMAL_SUCCESS)
      *stats = param.stats;
   return ret;
}