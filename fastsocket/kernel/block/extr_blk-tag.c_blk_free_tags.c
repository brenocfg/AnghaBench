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
struct blk_queue_tag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  __blk_free_tags (struct blk_queue_tag*) ; 
 scalar_t__ unlikely (int) ; 

void blk_free_tags(struct blk_queue_tag *bqt)
{
	if (unlikely(!__blk_free_tags(bqt)))
		BUG();
}