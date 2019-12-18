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
struct thin_disk_superblock {void* flags; void* trans_id; void* device_details_root; void* data_mapping_root; void* time; } ;
struct dm_pool_metadata {int /*<<< orphan*/  tm; int /*<<< orphan*/  flags; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  details_root; int /*<<< orphan*/  root; int /*<<< orphan*/  time; int /*<<< orphan*/  data_sm; int /*<<< orphan*/  metadata_sm; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int __write_changed_details (struct dm_pool_metadata*) ; 
 int /*<<< orphan*/  copy_sm_roots (struct dm_pool_metadata*,struct thin_disk_superblock*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct thin_disk_superblock* dm_block_data (struct dm_block*) ; 
 int dm_sm_commit (int /*<<< orphan*/ ) ; 
 int dm_sm_root_size (int /*<<< orphan*/ ,size_t*) ; 
 int dm_tm_commit (int /*<<< orphan*/ ,struct dm_block*) ; 
 int dm_tm_pre_commit (int /*<<< orphan*/ ) ; 
 int save_sm_roots (struct dm_pool_metadata*) ; 
 int superblock_lock (struct dm_pool_metadata*,struct dm_block**) ; 

__attribute__((used)) static int __commit_transaction(struct dm_pool_metadata *pmd)
{
	int r;
	size_t metadata_len, data_len;
	struct thin_disk_superblock *disk_super;
	struct dm_block *sblock;

	/*
	 * We need to know if the thin_disk_superblock exceeds a 512-byte sector.
	 */
	BUILD_BUG_ON(sizeof(struct thin_disk_superblock) > 512);

	r = __write_changed_details(pmd);
	if (r < 0)
		return r;

	r = dm_sm_commit(pmd->data_sm);
	if (r < 0)
		return r;

	r = dm_tm_pre_commit(pmd->tm);
	if (r < 0)
		return r;

	r = dm_sm_root_size(pmd->metadata_sm, &metadata_len);
	if (r < 0)
		return r;

	r = dm_sm_root_size(pmd->data_sm, &data_len);
	if (r < 0)
		return r;

	r = save_sm_roots(pmd);
	if (r < 0)
		return r;

	r = superblock_lock(pmd, &sblock);
	if (r)
		return r;

	disk_super = dm_block_data(sblock);
	disk_super->time = cpu_to_le32(pmd->time);
	disk_super->data_mapping_root = cpu_to_le64(pmd->root);
	disk_super->device_details_root = cpu_to_le64(pmd->details_root);
	disk_super->trans_id = cpu_to_le64(pmd->trans_id);
	disk_super->flags = cpu_to_le32(pmd->flags);

	copy_sm_roots(pmd, disk_super);

	return dm_tm_commit(pmd->tm, sblock);
}