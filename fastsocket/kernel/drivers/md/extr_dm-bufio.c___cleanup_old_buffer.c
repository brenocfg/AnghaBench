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
struct dm_buffer {unsigned long last_accessed; scalar_t__ hold_count; int /*<<< orphan*/  state; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_DIRTY ; 
 int /*<<< orphan*/  B_READING ; 
 int /*<<< orphan*/  B_WRITING ; 
 int __GFP_IO ; 
 int /*<<< orphan*/  __free_buffer_wake (struct dm_buffer*) ; 
 int /*<<< orphan*/  __make_buffer_clean (struct dm_buffer*) ; 
 int /*<<< orphan*/  __unlink_buffer (struct dm_buffer*) ; 
 unsigned long jiffies ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __cleanup_old_buffer(struct dm_buffer *b, gfp_t gfp,
				unsigned long max_jiffies)
{
	if (jiffies - b->last_accessed < max_jiffies)
		return 1;

	if (!(gfp & __GFP_IO)) {
		if (test_bit(B_READING, &b->state) ||
		    test_bit(B_WRITING, &b->state) ||
		    test_bit(B_DIRTY, &b->state))
			return 1;
	}

	if (b->hold_count)
		return 1;

	__make_buffer_clean(b);
	__unlink_buffer(b);
	__free_buffer_wake(b);

	return 0;
}