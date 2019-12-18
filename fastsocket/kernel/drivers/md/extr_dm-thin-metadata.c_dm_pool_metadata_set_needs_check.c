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
struct thin_disk_superblock {int /*<<< orphan*/  flags; } ;
struct dm_pool_metadata {int /*<<< orphan*/  root_lock; int /*<<< orphan*/  flags; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  THIN_METADATA_NEEDS_CHECK_FLAG ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct thin_disk_superblock* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_unlock (struct dm_block*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int superblock_lock (struct dm_pool_metadata*,struct dm_block**) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_pool_metadata_set_needs_check(struct dm_pool_metadata *pmd)
{
	int r;
	struct dm_block *sblock;
	struct thin_disk_superblock *disk_super;

	down_write(&pmd->root_lock);
	pmd->flags |= THIN_METADATA_NEEDS_CHECK_FLAG;

	r = superblock_lock(pmd, &sblock);
	if (r) {
		DMERR("couldn't read superblock");
		goto out;
	}

	disk_super = dm_block_data(sblock);
	disk_super->flags = cpu_to_le32(pmd->flags);

	dm_bm_unlock(sblock);
out:
	up_write(&pmd->root_lock);
	return r;
}