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
struct thin_disk_superblock {int /*<<< orphan*/  data_space_map_root; int /*<<< orphan*/  metadata_space_map_root; } ;
struct dm_pool_metadata {int /*<<< orphan*/  metadata_sm; int /*<<< orphan*/  tm; int /*<<< orphan*/  data_sm; int /*<<< orphan*/  nb_tm; int /*<<< orphan*/  bm; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIN_SUPERBLOCK_LOCATION ; 
 int __check_incompat_features (struct thin_disk_superblock*,struct dm_pool_metadata*) ; 
 int /*<<< orphan*/  __setup_btree_details (struct dm_pool_metadata*) ; 
 struct thin_disk_superblock* dm_block_data (struct dm_block*) ; 
 int dm_bm_read_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**) ; 
 int dm_bm_unlock (struct dm_block*) ; 
 int /*<<< orphan*/  dm_sm_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_sm_disk_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dm_tm_create_non_blocking_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_destroy (int /*<<< orphan*/ ) ; 
 int dm_tm_open_with_sm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_validator ; 

__attribute__((used)) static int __open_metadata(struct dm_pool_metadata *pmd)
{
	int r;
	struct dm_block *sblock;
	struct thin_disk_superblock *disk_super;

	r = dm_bm_read_lock(pmd->bm, THIN_SUPERBLOCK_LOCATION,
			    &sb_validator, &sblock);
	if (r < 0) {
		DMERR("couldn't read superblock");
		return r;
	}

	disk_super = dm_block_data(sblock);

	r = __check_incompat_features(disk_super, pmd);
	if (r < 0)
		goto bad_unlock_sblock;

	r = dm_tm_open_with_sm(pmd->bm, THIN_SUPERBLOCK_LOCATION,
			       disk_super->metadata_space_map_root,
			       sizeof(disk_super->metadata_space_map_root),
			       &pmd->tm, &pmd->metadata_sm);
	if (r < 0) {
		DMERR("tm_open_with_sm failed");
		goto bad_unlock_sblock;
	}

	pmd->data_sm = dm_sm_disk_open(pmd->tm, disk_super->data_space_map_root,
				       sizeof(disk_super->data_space_map_root));
	if (IS_ERR(pmd->data_sm)) {
		DMERR("sm_disk_open failed");
		r = PTR_ERR(pmd->data_sm);
		goto bad_cleanup_tm;
	}

	pmd->nb_tm = dm_tm_create_non_blocking_clone(pmd->tm);
	if (!pmd->nb_tm) {
		DMERR("could not create non-blocking clone tm");
		r = -ENOMEM;
		goto bad_cleanup_data_sm;
	}

	__setup_btree_details(pmd);
	return dm_bm_unlock(sblock);

bad_cleanup_data_sm:
	dm_sm_destroy(pmd->data_sm);
bad_cleanup_tm:
	dm_tm_destroy(pmd->tm);
	dm_sm_destroy(pmd->metadata_sm);
bad_unlock_sblock:
	dm_bm_unlock(sblock);

	return r;
}