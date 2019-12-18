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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct dm_thin_lookup_result {int /*<<< orphan*/  shared; int /*<<< orphan*/  block; } ;
struct dm_thin_device {int /*<<< orphan*/  id; struct dm_pool_metadata* pmd; } ;
struct dm_btree_info {int dummy; } ;
struct dm_pool_metadata {int /*<<< orphan*/  root_lock; int /*<<< orphan*/  root; scalar_t__ fail_io; struct dm_btree_info nb_info; struct dm_btree_info info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int EINVAL ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  __snapshotted_since (struct dm_thin_device*,int /*<<< orphan*/ ) ; 
 int dm_btree_lookup (struct dm_btree_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpack_block_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int dm_thin_find_block(struct dm_thin_device *td, dm_block_t block,
		       int can_block, struct dm_thin_lookup_result *result)
{
	int r = -EINVAL;
	uint64_t block_time = 0;
	__le64 value;
	struct dm_pool_metadata *pmd = td->pmd;
	dm_block_t keys[2] = { td->id, block };
	struct dm_btree_info *info;

	if (can_block) {
		down_read(&pmd->root_lock);
		info = &pmd->info;
	} else if (down_read_trylock(&pmd->root_lock))
		info = &pmd->nb_info;
	else
		return -EWOULDBLOCK;

	if (pmd->fail_io)
		goto out;

	r = dm_btree_lookup(info, pmd->root, keys, &value);
	if (!r)
		block_time = le64_to_cpu(value);

out:
	up_read(&pmd->root_lock);

	if (!r) {
		dm_block_t exception_block;
		uint32_t exception_time;
		unpack_block_time(block_time, &exception_block,
				  &exception_time);
		result->block = exception_block;
		result->shared = __snapshotted_since(td, exception_time);
	}

	return r;
}