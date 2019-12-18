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
struct hd_struct {unsigned long stamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __part_stat_add (int,struct hd_struct*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  io_ticks ; 
 unsigned long part_in_flight (struct hd_struct*) ; 
 int /*<<< orphan*/  time_in_queue ; 

__attribute__((used)) static void part_round_stats_single(int cpu, struct hd_struct *part,
				    unsigned long now)
{
	if (now == part->stamp)
		return;

	if (part_in_flight(part)) {
		__part_stat_add(cpu, part, time_in_queue,
				part_in_flight(part) * (now - part->stamp));
		__part_stat_add(cpu, part, io_ticks, (now - part->stamp));
	}
	part->stamp = now;
}