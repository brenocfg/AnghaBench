#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int profile_idc; int constraint_set_flags; } ;
typedef  TYPE_1__ SPS ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int more_rbsp_data_in_pps(const SPS *sps, void *logctx)
{
    int profile_idc = sps->profile_idc;

    if ((profile_idc == 66 || profile_idc == 77 ||
         profile_idc == 88) && (sps->constraint_set_flags & 7)) {
        av_log(logctx, AV_LOG_VERBOSE,
               "Current profile doesn't provide more RBSP data in PPS, skipping\n");
        return 0;
    }

    return 1;
}