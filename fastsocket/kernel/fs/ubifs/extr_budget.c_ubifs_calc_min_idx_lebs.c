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
struct ubifs_info {long long old_idx_sz; long long budg_idx_growth; long long budg_uncommitted_idx; scalar_t__ idx_leb_size; } ;

/* Variables and functions */
 int MIN_INDEX_LEBS ; 
 int div_u64 (scalar_t__,scalar_t__) ; 

int ubifs_calc_min_idx_lebs(struct ubifs_info *c)
{
	int idx_lebs;
	long long idx_size;

	idx_size = c->old_idx_sz + c->budg_idx_growth + c->budg_uncommitted_idx;
	/* And make sure we have thrice the index size of space reserved */
	idx_size += idx_size << 1;
	/*
	 * We do not maintain 'old_idx_size' as 'old_idx_lebs'/'old_idx_bytes'
	 * pair, nor similarly the two variables for the new index size, so we
	 * have to do this costly 64-bit division on fast-path.
	 */
	idx_lebs = div_u64(idx_size + c->idx_leb_size - 1, c->idx_leb_size);
	/*
	 * The index head is not available for the in-the-gaps method, so add an
	 * extra LEB to compensate.
	 */
	idx_lebs += 1;
	if (idx_lebs < MIN_INDEX_LEBS)
		idx_lebs = MIN_INDEX_LEBS;
	return idx_lebs;
}