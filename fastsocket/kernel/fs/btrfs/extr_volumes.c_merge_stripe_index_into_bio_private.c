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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static void *merge_stripe_index_into_bio_private(void *bi_private,
						 unsigned int stripe_index)
{
	/*
	 * with single, dup, RAID0, RAID1 and RAID10, stripe_index is
	 * at most 1.
	 * The alternative solution (instead of stealing bits from the
	 * pointer) would be to allocate an intermediate structure
	 * that contains the old private pointer plus the stripe_index.
	 */
	BUG_ON((((uintptr_t)bi_private) & 3) != 0);
	BUG_ON(stripe_index > 3);
	return (void *)(((uintptr_t)bi_private) | stripe_index);
}