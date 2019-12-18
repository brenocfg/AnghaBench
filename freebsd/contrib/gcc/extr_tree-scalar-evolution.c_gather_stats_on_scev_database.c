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
struct chrec_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_chrecs_stats (int /*<<< orphan*/ ,struct chrec_stats*) ; 
 int /*<<< orphan*/  dump_file ; 
 int /*<<< orphan*/  gather_stats_on_scev_database_1 ; 
 int /*<<< orphan*/  htab_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct chrec_stats*) ; 
 int /*<<< orphan*/  reset_chrecs_counters (struct chrec_stats*) ; 
 int /*<<< orphan*/  scalar_evolution_info ; 

void 
gather_stats_on_scev_database (void)
{
  struct chrec_stats stats;
  
  if (!dump_file)
    return;
  
  reset_chrecs_counters (&stats);
 
  htab_traverse (scalar_evolution_info, gather_stats_on_scev_database_1,
		 &stats);

  dump_chrecs_stats (dump_file, &stats);
}