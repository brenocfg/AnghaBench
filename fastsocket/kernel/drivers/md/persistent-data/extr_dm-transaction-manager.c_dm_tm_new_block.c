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
struct dm_transaction_manager {int /*<<< orphan*/  sm; int /*<<< orphan*/  bm; scalar_t__ is_clone; } ;
struct dm_block_validator {int dummy; } ;
struct dm_block {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int dm_bm_write_lock_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_block_validator*,struct dm_block**) ; 
 int /*<<< orphan*/  dm_sm_dec_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dm_sm_new_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_shadow (struct dm_transaction_manager*,int /*<<< orphan*/ ) ; 

int dm_tm_new_block(struct dm_transaction_manager *tm,
		    struct dm_block_validator *v,
		    struct dm_block **result)
{
	int r;
	dm_block_t new_block;

	if (tm->is_clone)
		return -EWOULDBLOCK;

	r = dm_sm_new_block(tm->sm, &new_block);
	if (r < 0)
		return r;

	r = dm_bm_write_lock_zero(tm->bm, new_block, v, result);
	if (r < 0) {
		dm_sm_dec_block(tm->sm, new_block);
		return r;
	}

	/*
	 * New blocks count as shadows in that they don't need to be
	 * shadowed again.
	 */
	insert_shadow(tm, new_block);

	return 0;
}