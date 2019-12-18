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
struct request {int /*<<< orphan*/  q; struct completion* end_io_data; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_put_request (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  complete (struct completion*) ; 

__attribute__((used)) static void blk_end_sync_rq(struct request *rq, int error)
{
	struct completion *waiting = rq->end_io_data;

	rq->end_io_data = NULL;
	__blk_put_request(rq->q, rq);

	/*
	 * complete last, if this is a stack request the process (and thus
	 * the rq pointer) could be invalid right after this complete()
	 */
	complete(waiting);
}