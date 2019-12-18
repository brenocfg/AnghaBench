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
struct request {int /*<<< orphan*/  q; int /*<<< orphan*/  start_time; int /*<<< orphan*/  cmd_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_IO_STAT ; 
 int blk_insert_cloned_request (int /*<<< orphan*/ ,struct request*) ; 
 scalar_t__ blk_queue_io_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_complete_request (struct request*,int) ; 
 int /*<<< orphan*/  jiffies ; 

void dm_dispatch_request(struct request *rq)
{
	int r;

	if (blk_queue_io_stat(rq->q))
		rq->cmd_flags |= REQ_IO_STAT;

	rq->start_time = jiffies;
	r = blk_insert_cloned_request(rq->q, rq);
	if (r)
		dm_complete_request(rq, r);
}