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
struct request {int /*<<< orphan*/  rq_disk; } ;
struct hd_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_do_io_stat (struct request*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 struct hd_struct* disk_map_sector_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * merges ; 
 int /*<<< orphan*/  part_inc_in_flight (struct hd_struct*,int) ; 
 int /*<<< orphan*/  part_round_stats (int,struct hd_struct*) ; 
 int /*<<< orphan*/  part_stat_inc (int,struct hd_struct*,int /*<<< orphan*/ ) ; 
 int part_stat_lock () ; 
 int /*<<< orphan*/  part_stat_unlock () ; 
 int rq_data_dir (struct request*) ; 

__attribute__((used)) static void drive_stat_acct(struct request *rq, int new_io)
{
	struct hd_struct *part;
	int rw = rq_data_dir(rq);
	int cpu;

	if (!blk_do_io_stat(rq))
		return;

	cpu = part_stat_lock();
	part = disk_map_sector_rcu(rq->rq_disk, blk_rq_pos(rq));

	if (!new_io)
		part_stat_inc(cpu, part, merges[rw]);
	else {
		part_round_stats(cpu, part);
		part_inc_in_flight(part, rw);
	}

	part_stat_unlock();
}