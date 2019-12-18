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
struct thin_disk_superblock {int /*<<< orphan*/  held_root; } ;
struct dm_pool_metadata {int /*<<< orphan*/  bm; } ;
struct dm_block {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  THIN_SUPERBLOCK_LOCATION ; 
 struct thin_disk_superblock* dm_block_data (struct dm_block*) ; 
 int dm_bm_read_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**) ; 
 int dm_bm_unlock (struct dm_block*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_validator ; 

__attribute__((used)) static int __get_metadata_snap(struct dm_pool_metadata *pmd,
			       dm_block_t *result)
{
	int r;
	struct thin_disk_superblock *disk_super;
	struct dm_block *sblock;

	r = dm_bm_read_lock(pmd->bm, THIN_SUPERBLOCK_LOCATION,
			    &sb_validator, &sblock);
	if (r)
		return r;

	disk_super = dm_block_data(sblock);
	*result = le64_to_cpu(disk_super->held_root);

	return dm_bm_unlock(sblock);
}