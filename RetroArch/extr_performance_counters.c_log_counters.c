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
typedef  int uint64_t ;
struct retro_perf_counter {scalar_t__ call_cnt; scalar_t__ total; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_LOG_FMT ; 
 int /*<<< orphan*/  RARCH_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void log_counters(struct retro_perf_counter **counters, unsigned num)
{
   unsigned i;
   for (i = 0; i < num; i++)
   {
      if (counters[i]->call_cnt)
      {
         RARCH_LOG(PERF_LOG_FMT,
               counters[i]->ident,
               (uint64_t)counters[i]->total /
               (uint64_t)counters[i]->call_cnt,
               (uint64_t)counters[i]->call_cnt);
      }
   }
}