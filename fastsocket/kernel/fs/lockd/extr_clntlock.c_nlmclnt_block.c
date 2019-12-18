#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nlm_wait {scalar_t__ b_status; int /*<<< orphan*/  b_wait; } ;
struct TYPE_2__ {scalar_t__ status; } ;
struct nlm_rqst {TYPE_1__ a_res; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ERESTARTSYS ; 
 scalar_t__ nlm_lck_blocked ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,long) ; 

int nlmclnt_block(struct nlm_wait *block, struct nlm_rqst *req, long timeout)
{
	long ret;

	/* A borken server might ask us to block even if we didn't
	 * request it. Just say no!
	 */
	if (block == NULL)
		return -EAGAIN;

	/* Go to sleep waiting for GRANT callback. Some servers seem
	 * to lose callbacks, however, so we're going to poll from
	 * time to time just to make sure.
	 *
	 * For now, the retry frequency is pretty high; normally 
	 * a 1 minute timeout would do. See the comment before
	 * nlmclnt_lock for an explanation.
	 */
	ret = wait_event_interruptible_timeout(block->b_wait,
			block->b_status != nlm_lck_blocked,
			timeout);
	if (ret < 0)
		return -ERESTARTSYS;
	req->a_res.status = block->b_status;
	return 0;
}