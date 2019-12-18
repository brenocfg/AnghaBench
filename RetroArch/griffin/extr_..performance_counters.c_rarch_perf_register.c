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
struct retro_perf_counter {int registered; } ;

/* Variables and functions */
 scalar_t__ MAX_COUNTERS ; 
 int /*<<< orphan*/  RARCH_CTL_IS_PERFCNT_ENABLE ; 
 struct retro_perf_counter** perf_counters_rarch ; 
 scalar_t__ perf_ptr_rarch ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rarch_perf_register(struct retro_perf_counter *perf)
{
   if (
            !rarch_ctl(RARCH_CTL_IS_PERFCNT_ENABLE, NULL)
         || perf->registered
         || perf_ptr_rarch >= MAX_COUNTERS
      )
      return;

   perf_counters_rarch[perf_ptr_rarch++] = perf;
   perf->registered = true;
}