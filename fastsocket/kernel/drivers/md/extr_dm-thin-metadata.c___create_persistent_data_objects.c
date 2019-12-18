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
struct dm_pool_metadata {int /*<<< orphan*/  bm; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  THIN_MAX_CONCURRENT_LOCKS ; 
 int THIN_METADATA_BLOCK_SIZE ; 
 int /*<<< orphan*/  THIN_METADATA_CACHE_SIZE ; 
 int __open_or_format_metadata (struct dm_pool_metadata*,int) ; 
 int /*<<< orphan*/  dm_block_manager_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_block_manager_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __create_persistent_data_objects(struct dm_pool_metadata *pmd, bool format_device)
{
	int r;

	pmd->bm = dm_block_manager_create(pmd->bdev, THIN_METADATA_BLOCK_SIZE << SECTOR_SHIFT,
					  THIN_METADATA_CACHE_SIZE,
					  THIN_MAX_CONCURRENT_LOCKS);
	if (IS_ERR(pmd->bm)) {
		DMERR("could not create block manager");
		return PTR_ERR(pmd->bm);
	}

	r = __open_or_format_metadata(pmd, format_device);
	if (r)
		dm_block_manager_destroy(pmd->bm);

	return r;
}