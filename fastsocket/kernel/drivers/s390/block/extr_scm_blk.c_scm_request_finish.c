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
struct scm_request {int /*<<< orphan*/  error; int /*<<< orphan*/  request; struct scm_blk_dev* bdev; } ;
struct scm_blk_dev {int /*<<< orphan*/  queued_reqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_end_request_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scm_release_cluster (struct scm_request*) ; 
 int /*<<< orphan*/  scm_request_done (struct scm_request*) ; 

void scm_request_finish(struct scm_request *scmrq)
{
	struct scm_blk_dev *bdev = scmrq->bdev;

	scm_release_cluster(scmrq);
	blk_end_request_all(scmrq->request, scmrq->error);
	atomic_dec(&bdev->queued_reqs);
	scm_request_done(scmrq);
}