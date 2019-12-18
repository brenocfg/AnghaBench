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
struct request {int cmd_flags; unsigned long start_time; int /*<<< orphan*/  rq_disk; } ;
struct hd_struct {int dummy; } ;

/* Variables and functions */
 int REQ_FLUSH_SEQ ; 
 scalar_t__ blk_do_io_stat (struct request*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 struct hd_struct* disk_map_sector_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ios ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  part_dec_in_flight (struct hd_struct*,int const) ; 
 int /*<<< orphan*/  part_round_stats (int,struct hd_struct*) ; 
 int /*<<< orphan*/  part_stat_add (int,struct hd_struct*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  part_stat_inc (int,struct hd_struct*,int /*<<< orphan*/ ) ; 
 int part_stat_lock () ; 
 int /*<<< orphan*/  part_stat_unlock () ; 
 int rq_data_dir (struct request*) ; 
 int /*<<< orphan*/ * ticks ; 

__attribute__((used)) static void blk_account_io_done(struct request *req)
{
	/*
	 * Account IO completion.  flush_rq isn't accounted as a
	 * normal IO on queueing nor completion.  Accounting the
	 * containing request is enough.
	 */
	if (blk_do_io_stat(req) && !(req->cmd_flags & REQ_FLUSH_SEQ)) {
		unsigned long duration = jiffies - req->start_time;
		const int rw = rq_data_dir(req);
		struct hd_struct *part;
		int cpu;

		cpu = part_stat_lock();
		part = disk_map_sector_rcu(req->rq_disk, blk_rq_pos(req));

		part_stat_inc(cpu, part, ios[rw]);
		part_stat_add(cpu, part, ticks[rw], duration);
		part_round_stats(cpu, part);
		part_dec_in_flight(part, rw);

		part_stat_unlock();
	}
}