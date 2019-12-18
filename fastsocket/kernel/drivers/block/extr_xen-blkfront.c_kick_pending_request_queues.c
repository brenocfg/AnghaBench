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
struct blkfront_info {int /*<<< orphan*/  rq; int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_FULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_blkif_request (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kick_pending_request_queues(struct blkfront_info *info)
{
	if (!RING_FULL(&info->ring)) {
		/* Re-enable calldowns. */
		blk_start_queue(info->rq);
		/* Kick things off immediately. */
		do_blkif_request(info->rq);
	}
}