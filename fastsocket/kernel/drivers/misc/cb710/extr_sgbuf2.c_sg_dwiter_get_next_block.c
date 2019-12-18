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
typedef  int /*<<< orphan*/  uint32_t ;
struct sg_mapping_iter {size_t length; size_t consumed; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  needs_unaligned_copy (int /*<<< orphan*/ *) ; 
 scalar_t__ sg_dwiter_is_at_end (struct sg_mapping_iter*) ; 

__attribute__((used)) static bool sg_dwiter_get_next_block(struct sg_mapping_iter *miter, uint32_t **ptr)
{
	size_t len;

	if (sg_dwiter_is_at_end(miter))
		return true;

	len = miter->length - miter->consumed;

	if (likely(len >= 4 && !needs_unaligned_copy(
			miter->addr + miter->consumed))) {
		*ptr = miter->addr + miter->consumed;
		miter->consumed += 4;
		return true;
	}

	return false;
}