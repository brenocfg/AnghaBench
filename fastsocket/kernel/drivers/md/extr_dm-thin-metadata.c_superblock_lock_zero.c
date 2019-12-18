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
struct dm_pool_metadata {int /*<<< orphan*/  bm; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIN_SUPERBLOCK_LOCATION ; 
 int dm_bm_write_lock_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**) ; 
 int /*<<< orphan*/  sb_validator ; 

__attribute__((used)) static int superblock_lock_zero(struct dm_pool_metadata *pmd,
				struct dm_block **sblock)
{
	return dm_bm_write_lock_zero(pmd->bm, THIN_SUPERBLOCK_LOCATION,
				     &sb_validator, sblock);
}