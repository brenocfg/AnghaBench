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
struct fc_rport {int /*<<< orphan*/  dev; int /*<<< orphan*/  rqst_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_run_queue_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fc_bsg_goose_queue(struct fc_rport *rport)
{
	if (!rport->rqst_q)
		return;

	/*
	 * This get/put dance makes no sense
	 */
	get_device(&rport->dev);
	blk_run_queue_async(rport->rqst_q);
	put_device(&rport->dev);
}