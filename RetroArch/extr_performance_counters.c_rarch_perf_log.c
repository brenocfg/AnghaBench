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

/* Variables and functions */
 int /*<<< orphan*/  RARCH_CTL_IS_PERFCNT_ENABLE ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  log_counters (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_counters_rarch ; 
 int /*<<< orphan*/  perf_ptr_rarch ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rarch_perf_log(void)
{
   if (!rarch_ctl(RARCH_CTL_IS_PERFCNT_ENABLE, NULL))
      return;

   RARCH_LOG("[PERF]: Performance counters (RetroArch):\n");
   log_counters(perf_counters_rarch, perf_ptr_rarch);
}