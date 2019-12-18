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
struct retro_perf_counter {scalar_t__ start; int /*<<< orphan*/  total; } ;

/* Variables and functions */
 scalar_t__ cpu_features_get_perf_counter () ; 
 scalar_t__ runloop_perfcnt_enable ; 

__attribute__((used)) static void core_performance_counter_stop(struct retro_perf_counter *perf)
{
   if (runloop_perfcnt_enable)
      perf->total += cpu_features_get_perf_counter() - perf->start;
}