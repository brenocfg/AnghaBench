#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_4__ {scalar_t__ objectid; } ;
struct btrfs_block_group_cache {int bytes_super; TYPE_2__ key; } ;
struct TYPE_3__ {int /*<<< orphan*/  mapping_tree; } ;

/* Variables and functions */
 scalar_t__ BTRFS_SUPER_INFO_OFFSET ; 
 int BTRFS_SUPER_MIRROR_MAX ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int add_excluded_extent (struct btrfs_root*,scalar_t__,int) ; 
 int btrfs_rmap_block (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__**,int*,int*) ; 
 scalar_t__ btrfs_sb_offset (int) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 

__attribute__((used)) static int exclude_super_stripes(struct btrfs_root *root,
				 struct btrfs_block_group_cache *cache)
{
	u64 bytenr;
	u64 *logical;
	int stripe_len;
	int i, nr, ret;

	if (cache->key.objectid < BTRFS_SUPER_INFO_OFFSET) {
		stripe_len = BTRFS_SUPER_INFO_OFFSET - cache->key.objectid;
		cache->bytes_super += stripe_len;
		ret = add_excluded_extent(root, cache->key.objectid,
					  stripe_len);
		BUG_ON(ret); /* -ENOMEM */
	}

	for (i = 0; i < BTRFS_SUPER_MIRROR_MAX; i++) {
		bytenr = btrfs_sb_offset(i);
		ret = btrfs_rmap_block(&root->fs_info->mapping_tree,
				       cache->key.objectid, bytenr,
				       0, &logical, &nr, &stripe_len);
		BUG_ON(ret); /* -ENOMEM */

		while (nr--) {
			cache->bytes_super += stripe_len;
			ret = add_excluded_extent(root, logical[nr],
						  stripe_len);
			BUG_ON(ret); /* -ENOMEM */
		}

		kfree(logical);
	}
	return 0;
}