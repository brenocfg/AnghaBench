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
struct request {int /*<<< orphan*/  errors; struct bsg_job* special; } ;
struct bsg_job {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsg_destroy_job (struct bsg_job*) ; 

__attribute__((used)) static void bsg_softirq_done(struct request *rq)
{
	struct bsg_job *job = rq->special;

	blk_end_request_all(rq, rq->errors);
	bsg_destroy_job(job);
}