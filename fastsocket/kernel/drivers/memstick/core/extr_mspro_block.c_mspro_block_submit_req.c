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
struct request_queue {struct memstick_dev* queuedata; } ;
struct request {int dummy; } ;
struct mspro_block_data {int has_request; scalar_t__ eject; } ;
struct memstick_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 struct mspro_block_data* memstick_get_drvdata (struct memstick_dev*) ; 
 scalar_t__ mspro_block_issue_req (struct memstick_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mspro_block_submit_req(struct request_queue *q)
{
	struct memstick_dev *card = q->queuedata;
	struct mspro_block_data *msb = memstick_get_drvdata(card);
	struct request *req = NULL;

	if (msb->has_request)
		return;

	if (msb->eject) {
		while ((req = blk_fetch_request(q)) != NULL)
			__blk_end_request_all(req, -ENODEV);

		return;
	}

	msb->has_request = 1;
	if (mspro_block_issue_req(card, 0))
		msb->has_request = 0;
}