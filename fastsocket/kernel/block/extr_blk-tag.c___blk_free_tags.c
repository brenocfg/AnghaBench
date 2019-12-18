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
struct blk_queue_tag {scalar_t__ max_depth; struct blk_queue_tag* tag_map; struct blk_queue_tag* tag_index; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ find_first_bit (struct blk_queue_tag*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct blk_queue_tag*) ; 

__attribute__((used)) static int __blk_free_tags(struct blk_queue_tag *bqt)
{
	int retval;

	retval = atomic_dec_and_test(&bqt->refcnt);
	if (retval) {
		BUG_ON(find_first_bit(bqt->tag_map, bqt->max_depth) <
							bqt->max_depth);

		kfree(bqt->tag_index);
		bqt->tag_index = NULL;

		kfree(bqt->tag_map);
		bqt->tag_map = NULL;

		kfree(bqt);
	}

	return retval;
}