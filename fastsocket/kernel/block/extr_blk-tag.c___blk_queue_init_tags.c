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
struct request_queue {int dummy; } ;
struct blk_queue_tag {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ init_tag_map (struct request_queue*,struct blk_queue_tag*,int) ; 
 int /*<<< orphan*/  kfree (struct blk_queue_tag*) ; 
 struct blk_queue_tag* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct blk_queue_tag *__blk_queue_init_tags(struct request_queue *q,
						   int depth)
{
	struct blk_queue_tag *tags;

	tags = kmalloc(sizeof(struct blk_queue_tag), GFP_ATOMIC);
	if (!tags)
		goto fail;

	if (init_tag_map(q, tags, depth))
		goto fail;

	atomic_set(&tags->refcnt, 1);
	return tags;
fail:
	kfree(tags);
	return NULL;
}