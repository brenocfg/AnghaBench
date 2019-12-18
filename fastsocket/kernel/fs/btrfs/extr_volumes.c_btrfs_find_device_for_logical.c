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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_root {TYPE_2__* fs_info; } ;
struct btrfs_mapping_tree {int dummy; } ;
struct btrfs_device {int dummy; } ;
struct btrfs_bio {int mirror_num; TYPE_1__* stripes; } ;
struct TYPE_4__ {struct btrfs_mapping_tree mapping_tree; } ;
struct TYPE_3__ {struct btrfs_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WRITE ; 
 int btrfs_map_block (struct btrfs_mapping_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct btrfs_bio**,int) ; 
 int /*<<< orphan*/  kfree (struct btrfs_bio*) ; 

struct btrfs_device *btrfs_find_device_for_logical(struct btrfs_root *root,
						   u64 logical, int mirror_num)
{
	struct btrfs_mapping_tree *map_tree = &root->fs_info->mapping_tree;
	int ret;
	u64 map_length = 0;
	struct btrfs_bio *bbio = NULL;
	struct btrfs_device *device;

	BUG_ON(mirror_num == 0);
	ret = btrfs_map_block(map_tree, WRITE, logical, &map_length, &bbio,
			      mirror_num);
	if (ret) {
		BUG_ON(bbio != NULL);
		return NULL;
	}
	BUG_ON(mirror_num != bbio->mirror_num);
	device = bbio->stripes[mirror_num - 1].dev;
	kfree(bbio);
	return device;
}