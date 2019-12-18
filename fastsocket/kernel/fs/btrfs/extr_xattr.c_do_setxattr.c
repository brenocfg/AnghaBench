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
struct inode {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_dir_item {int dummy; } ;
struct TYPE_2__ {struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 size_t BTRFS_MAX_XATTR_SIZE (struct btrfs_root*) ; 
 int EEXIST ; 
 int ENODATA ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EOVERFLOW ; 
 scalar_t__ IS_ERR (struct btrfs_dir_item*) ; 
 int PTR_ERR (struct btrfs_dir_item*) ; 
 int XATTR_CREATE ; 
 int XATTR_REPLACE ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_delete_one_dir_name (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_dir_item*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_ino (struct inode*) ; 
 int btrfs_insert_xattr_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ,char const*,size_t,void const*,size_t) ; 
 struct btrfs_dir_item* btrfs_lookup_xattr (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ,char const*,size_t,int) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int do_setxattr(struct btrfs_trans_handle *trans,
		       struct inode *inode, const char *name,
		       const void *value, size_t size, int flags)
{
	struct btrfs_dir_item *di;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_path *path;
	size_t name_len = strlen(name);
	int ret = 0;

	if (name_len + size > BTRFS_MAX_XATTR_SIZE(root))
		return -ENOSPC;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	if (flags & XATTR_REPLACE) {
		di = btrfs_lookup_xattr(trans, root, path, btrfs_ino(inode), name,
					name_len, -1);
		if (IS_ERR(di)) {
			ret = PTR_ERR(di);
			goto out;
		} else if (!di) {
			ret = -ENODATA;
			goto out;
		}
		ret = btrfs_delete_one_dir_name(trans, root, path, di);
		if (ret)
			goto out;
		btrfs_release_path(path);

		/*
		 * remove the attribute
		 */
		if (!value)
			goto out;
	}

again:
	ret = btrfs_insert_xattr_item(trans, root, path, btrfs_ino(inode),
				      name, name_len, value, size);
	/*
	 * If we're setting an xattr to a new value but the new value is say
	 * exactly BTRFS_MAX_XATTR_SIZE, we could end up with EOVERFLOW getting
	 * back from split_leaf.  This is because it thinks we'll be extending
	 * the existing item size, but we're asking for enough space to add the
	 * item itself.  So if we get EOVERFLOW just set ret to EEXIST and let
	 * the rest of the function figure it out.
	 */
	if (ret == -EOVERFLOW)
		ret = -EEXIST;

	if (ret == -EEXIST) {
		if (flags & XATTR_CREATE)
			goto out;
		/*
		 * We can't use the path we already have since we won't have the
		 * proper locking for a delete, so release the path and
		 * re-lookup to delete the thing.
		 */
		btrfs_release_path(path);
		di = btrfs_lookup_xattr(trans, root, path, btrfs_ino(inode),
					name, name_len, -1);
		if (IS_ERR(di)) {
			ret = PTR_ERR(di);
			goto out;
		} else if (!di) {
			/* Shouldn't happen but just in case... */
			btrfs_release_path(path);
			goto again;
		}

		ret = btrfs_delete_one_dir_name(trans, root, path, di);
		if (ret)
			goto out;

		/*
		 * We have a value to set, so go back and try to insert it now.
		 */
		if (value) {
			btrfs_release_path(path);
			goto again;
		}
	}
out:
	btrfs_free_path(path);
	return ret;
}