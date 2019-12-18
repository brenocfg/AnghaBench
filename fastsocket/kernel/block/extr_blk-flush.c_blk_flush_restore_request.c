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
struct request {int /*<<< orphan*/ * end_io; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  biotail; int /*<<< orphan*/  bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_FLUSH_SEQ ; 

__attribute__((used)) static void blk_flush_restore_request(struct request *rq)
{
	/*
	 * After flush data completion, @rq->bio is %NULL but we need to
	 * complete the bio again.  @rq->biotail is guaranteed to equal the
	 * original @rq->bio.  Restore it.
	 */
	rq->bio = rq->biotail;

	/* make @rq a normal request */
	rq->cmd_flags &= ~REQ_FLUSH_SEQ;
	rq->end_io = NULL;
}