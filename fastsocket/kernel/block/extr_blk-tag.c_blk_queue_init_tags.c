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
struct request_queue {int /*<<< orphan*/  tag_busy_list; struct blk_queue_tag* queue_tags; } ;
struct blk_queue_tag {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QUEUE_FLAG_QUEUED ; 
 struct blk_queue_tag* __blk_queue_init_tags (struct request_queue*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int blk_queue_resize_tags (struct request_queue*,int) ; 
 int /*<<< orphan*/  kfree (struct blk_queue_tag*) ; 
 int /*<<< orphan*/  queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  queue_flag_set_unlocked (int /*<<< orphan*/ ,struct request_queue*) ; 

int blk_queue_init_tags(struct request_queue *q, int depth,
			struct blk_queue_tag *tags)
{
	int rc;

	BUG_ON(tags && q->queue_tags && tags != q->queue_tags);

	if (!tags && !q->queue_tags) {
		tags = __blk_queue_init_tags(q, depth);

		if (!tags)
			goto fail;
	} else if (q->queue_tags) {
		rc = blk_queue_resize_tags(q, depth);
		if (rc)
			return rc;
		queue_flag_set(QUEUE_FLAG_QUEUED, q);
		return 0;
	} else
		atomic_inc(&tags->refcnt);

	/*
	 * assign it, all done
	 */
	q->queue_tags = tags;
	queue_flag_set_unlocked(QUEUE_FLAG_QUEUED, q);
	INIT_LIST_HEAD(&q->tag_busy_list);
	return 0;
fail:
	kfree(tags);
	return -ENOMEM;
}