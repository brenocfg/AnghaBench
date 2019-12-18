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
struct thin_disk_superblock {int /*<<< orphan*/  held_root; int /*<<< orphan*/  device_details_root; int /*<<< orphan*/  data_mapping_root; int /*<<< orphan*/  metadata_space_map_root; int /*<<< orphan*/  data_space_map_root; } ;
struct dm_pool_metadata {int /*<<< orphan*/  tm; int /*<<< orphan*/  metadata_sm; } ;
struct dm_block {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMWARN (char*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  THIN_SUPERBLOCK_LOCATION ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct thin_disk_superblock* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_block_location (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_unlock (struct dm_block*) ; 
 int /*<<< orphan*/  dm_sm_inc_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_inc (int /*<<< orphan*/ ,scalar_t__) ; 
 int dm_tm_shadow_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**,int*) ; 
 int /*<<< orphan*/  dm_tm_unlock (int /*<<< orphan*/ ,struct dm_block*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sb_validator ; 
 int superblock_lock (struct dm_pool_metadata*,struct dm_block**) ; 

__attribute__((used)) static int __reserve_metadata_snap(struct dm_pool_metadata *pmd)
{
	int r, inc;
	struct thin_disk_superblock *disk_super;
	struct dm_block *copy, *sblock;
	dm_block_t held_root;

	/*
	 * Copy the superblock.
	 */
	dm_sm_inc_block(pmd->metadata_sm, THIN_SUPERBLOCK_LOCATION);
	r = dm_tm_shadow_block(pmd->tm, THIN_SUPERBLOCK_LOCATION,
			       &sb_validator, &copy, &inc);
	if (r)
		return r;

	BUG_ON(!inc);

	held_root = dm_block_location(copy);
	disk_super = dm_block_data(copy);

	if (le64_to_cpu(disk_super->held_root)) {
		DMWARN("Pool metadata snapshot already exists: release this before taking another.");

		dm_tm_dec(pmd->tm, held_root);
		dm_tm_unlock(pmd->tm, copy);
		return -EBUSY;
	}

	/*
	 * Wipe the spacemap since we're not publishing this.
	 */
	memset(&disk_super->data_space_map_root, 0,
	       sizeof(disk_super->data_space_map_root));
	memset(&disk_super->metadata_space_map_root, 0,
	       sizeof(disk_super->metadata_space_map_root));

	/*
	 * Increment the data structures that need to be preserved.
	 */
	dm_tm_inc(pmd->tm, le64_to_cpu(disk_super->data_mapping_root));
	dm_tm_inc(pmd->tm, le64_to_cpu(disk_super->device_details_root));
	dm_tm_unlock(pmd->tm, copy);

	/*
	 * Write the held root into the superblock.
	 */
	r = superblock_lock(pmd, &sblock);
	if (r) {
		dm_tm_dec(pmd->tm, held_root);
		return r;
	}

	disk_super = dm_block_data(sblock);
	disk_super->held_root = cpu_to_le64(held_root);
	dm_bm_unlock(sblock);
	return 0;
}