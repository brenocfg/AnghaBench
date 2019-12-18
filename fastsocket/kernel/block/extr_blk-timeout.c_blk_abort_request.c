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
struct request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_delete_timer (struct request*) ; 
 scalar_t__ blk_mark_rq_complete (struct request*) ; 
 int /*<<< orphan*/  blk_rq_timed_out (struct request*) ; 

void blk_abort_request(struct request *req)
{
	if (blk_mark_rq_complete(req))
		return;
	blk_delete_timer(req);
	blk_rq_timed_out(req);
}