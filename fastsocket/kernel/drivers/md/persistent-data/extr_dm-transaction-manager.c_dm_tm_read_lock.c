#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dm_transaction_manager {int /*<<< orphan*/  bm; TYPE_1__* real; scalar_t__ is_clone; } ;
struct dm_block_validator {int dummy; } ;
struct dm_block {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
struct TYPE_2__ {int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int dm_bm_read_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_block_validator*,struct dm_block**) ; 
 int dm_bm_read_try_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_block_validator*,struct dm_block**) ; 

int dm_tm_read_lock(struct dm_transaction_manager *tm, dm_block_t b,
		    struct dm_block_validator *v,
		    struct dm_block **blk)
{
	if (tm->is_clone)
		return dm_bm_read_try_lock(tm->real->bm, b, v, blk);

	return dm_bm_read_lock(tm->bm, b, v, blk);
}