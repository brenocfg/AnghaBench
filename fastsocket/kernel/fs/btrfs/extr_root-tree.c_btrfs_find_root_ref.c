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
typedef  void* u64 ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_key {void* offset; int /*<<< orphan*/  type; void* objectid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ROOT_REF_KEY ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_find_root_ref(struct btrfs_root *tree_root,
		   struct btrfs_path *path,
		   u64 root_id, u64 ref_id)
{
	struct btrfs_key key;
	int ret;

	key.objectid = root_id;
	key.type = BTRFS_ROOT_REF_KEY;
	key.offset = ref_id;

	ret = btrfs_search_slot(NULL, tree_root, &key, path, 0, 0);
	return ret;
}