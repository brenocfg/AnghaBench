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
struct request {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_put_request (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  dm_complete_request (struct request*,int) ; 

__attribute__((used)) static void end_clone_request(struct request *clone, int error)
{
	/*
	 * For just cleaning up the information of the queue in which
	 * the clone was dispatched.
	 * The clone is *NOT* freed actually here because it is alloced from
	 * dm own mempool and REQ_ALLOCED isn't set in clone->cmd_flags.
	 */
	__blk_put_request(clone->q, clone);

	/*
	 * Actual request completion is done in a softirq context which doesn't
	 * hold the queue lock.  Otherwise, deadlock could occur because:
	 *     - another request may be submitted by the upper level driver
	 *       of the stacking during the completion
	 *     - the submission which requires queue lock may be done
	 *       against this queue
	 */
	dm_complete_request(clone, error);
}