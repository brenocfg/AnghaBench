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
struct retro_perf_counter {scalar_t__ call_cnt; scalar_t__ total; } ;

/* Variables and functions */

__attribute__((used)) static int generic_action_start_performance_counters(struct retro_perf_counter **counters,
      unsigned offset, unsigned type, const char *label)
{
   if (counters[offset])
   {
      counters[offset]->total    = 0;
      counters[offset]->call_cnt = 0;
   }

   return 0;
}