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
struct request {int /*<<< orphan*/  bio; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __blk_put_request (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  blk_end_request (struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _put_request(struct request *rq , bool is_async)
{
	if (is_async) {
		WARN_ON(rq->bio);
		__blk_put_request(rq->q, rq);
	} else {
		/*
		 * If osd_finalize_request() was called but the request was not
		 * executed through the block layer, then we must release BIOs.
		 * TODO: Keep error code in or->async_error. Need to audit all
		 *       code paths.
		 */
		if (unlikely(rq->bio))
			blk_end_request(rq, -ENOMEM, blk_rq_bytes(rq));
		else
			blk_put_request(rq);
	}
}