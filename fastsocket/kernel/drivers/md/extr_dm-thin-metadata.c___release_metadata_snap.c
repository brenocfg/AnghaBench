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
struct thin_disk_superblock {int /*<<< orphan*/  device_details_root; int /*<<< orphan*/  data_mapping_root; int /*<<< orphan*/  held_root; } ;
struct dm_pool_metadata {int /*<<< orphan*/  tm; int /*<<< orphan*/  metadata_sm; } ;
struct dm_block {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct thin_disk_superblock* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_unlock (struct dm_block*) ; 
 int /*<<< orphan*/  dm_sm_dec_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dm_tm_read_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**) ; 
 int dm_tm_unlock (int /*<<< orphan*/ ,struct dm_block*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_validator ; 
 int superblock_lock (struct dm_pool_metadata*,struct dm_block**) ; 

__attribute__((used)) static int __release_metadata_snap(struct dm_pool_metadata *pmd)
{
	int r;
	struct thin_disk_superblock *disk_super;
	struct dm_block *sblock, *copy;
	dm_block_t held_root;

	r = superblock_lock(pmd, &sblock);
	if (r)
		return r;

	disk_super = dm_block_data(sblock);
	held_root = le64_to_cpu(disk_super->held_root);
	disk_super->held_root = cpu_to_le64(0);

	dm_bm_unlock(sblock);

	if (!held_root) {
		DMWARN("No pool metadata snapshot found: nothing to release.");
		return -EINVAL;
	}

	r = dm_tm_read_lock(pmd->tm, held_root, &sb_validator, &copy);
	if (r)
		return r;

	disk_super = dm_block_data(copy);
	dm_sm_dec_block(pmd->metadata_sm, le64_to_cpu(disk_super->data_mapping_root));
	dm_sm_dec_block(pmd->metadata_sm, le64_to_cpu(disk_super->device_details_root));
	dm_sm_dec_block(pmd->metadata_sm, held_root);

	return dm_tm_unlock(pmd->tm, copy);
}