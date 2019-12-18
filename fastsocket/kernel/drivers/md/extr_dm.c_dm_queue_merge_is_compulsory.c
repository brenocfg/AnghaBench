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
struct request_queue {scalar_t__ make_request_fn; struct mapped_device* queuedata; int /*<<< orphan*/  merge_bvec_fn; } ;
struct mapped_device {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_MERGE_IS_OPTIONAL ; 
 scalar_t__ dm_request ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dm_queue_merge_is_compulsory(struct request_queue *q)
{
	struct mapped_device *dev_md;

	if (!q->merge_bvec_fn)
		return 0;

	if (q->make_request_fn == dm_request) {
		dev_md = q->queuedata;
		if (test_bit(DMF_MERGE_IS_OPTIONAL, &dev_md->flags))
			return 0;
	}

	return 1;
}