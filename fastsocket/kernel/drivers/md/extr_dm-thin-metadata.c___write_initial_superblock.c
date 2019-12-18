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
struct thin_disk_superblock {void* data_block_size; void* metadata_nr_blocks; void* metadata_block_size; void* device_details_root; void* data_mapping_root; scalar_t__ held_root; scalar_t__ trans_id; scalar_t__ time; void* version; void* magic; int /*<<< orphan*/  uuid; scalar_t__ flags; } ;
struct dm_pool_metadata {int root; int details_root; int /*<<< orphan*/  tm; int /*<<< orphan*/  data_block_size; int /*<<< orphan*/  data_sm; TYPE_1__* bdev; } ;
struct dm_block {int dummy; } ;
typedef  int sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int SECTOR_TO_BLOCK_SHIFT ; 
 int /*<<< orphan*/  THIN_METADATA_BLOCK_SIZE ; 
 int THIN_METADATA_MAX_SECTORS ; 
 int THIN_SUPERBLOCK_MAGIC ; 
 int /*<<< orphan*/  THIN_VERSION ; 
 int /*<<< orphan*/  copy_sm_roots (struct dm_pool_metadata*,struct thin_disk_superblock*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int) ; 
 struct thin_disk_superblock* dm_block_data (struct dm_block*) ; 
 int dm_sm_commit (int /*<<< orphan*/ ) ; 
 int dm_tm_commit (int /*<<< orphan*/ ,struct dm_block*) ; 
 int dm_tm_pre_commit (int /*<<< orphan*/ ) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int save_sm_roots (struct dm_pool_metadata*) ; 
 int superblock_lock_zero (struct dm_pool_metadata*,struct dm_block**) ; 

__attribute__((used)) static int __write_initial_superblock(struct dm_pool_metadata *pmd)
{
	int r;
	struct dm_block *sblock;
	struct thin_disk_superblock *disk_super;
	sector_t bdev_size = i_size_read(pmd->bdev->bd_inode) >> SECTOR_SHIFT;

	if (bdev_size > THIN_METADATA_MAX_SECTORS)
		bdev_size = THIN_METADATA_MAX_SECTORS;

	r = dm_sm_commit(pmd->data_sm);
	if (r < 0)
		return r;

	r = save_sm_roots(pmd);
	if (r < 0)
		return r;

	r = dm_tm_pre_commit(pmd->tm);
	if (r < 0)
		return r;

	r = superblock_lock_zero(pmd, &sblock);
	if (r)
		return r;

	disk_super = dm_block_data(sblock);
	disk_super->flags = 0;
	memset(disk_super->uuid, 0, sizeof(disk_super->uuid));
	disk_super->magic = cpu_to_le64(THIN_SUPERBLOCK_MAGIC);
	disk_super->version = cpu_to_le32(THIN_VERSION);
	disk_super->time = 0;
	disk_super->trans_id = 0;
	disk_super->held_root = 0;

	copy_sm_roots(pmd, disk_super);

	disk_super->data_mapping_root = cpu_to_le64(pmd->root);
	disk_super->device_details_root = cpu_to_le64(pmd->details_root);
	disk_super->metadata_block_size = cpu_to_le32(THIN_METADATA_BLOCK_SIZE);
	disk_super->metadata_nr_blocks = cpu_to_le64(bdev_size >> SECTOR_TO_BLOCK_SHIFT);
	disk_super->data_block_size = cpu_to_le32(pmd->data_block_size);

	return dm_tm_commit(pmd->tm, sblock);
}