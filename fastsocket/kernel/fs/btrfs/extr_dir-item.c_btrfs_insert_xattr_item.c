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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  transid; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {struct extent_buffer** nodes; } ;
struct btrfs_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  objectid; } ;
struct btrfs_disk_key {int dummy; } ;
struct btrfs_dir_item {int dummy; } ;
typedef  int /*<<< orphan*/  location ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FT_XATTR ; 
 scalar_t__ BTRFS_MAX_XATTR_SIZE (struct btrfs_root*) ; 
 int /*<<< orphan*/  BTRFS_XATTR_ITEM_KEY ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct btrfs_dir_item*) ; 
 int PTR_ERR (struct btrfs_dir_item*) ; 
 int /*<<< orphan*/  btrfs_cpu_key_to_disk (struct btrfs_disk_key*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_name_hash (char const*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_set_dir_data_len (struct extent_buffer*,struct btrfs_dir_item*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_set_dir_item_key (struct extent_buffer*,struct btrfs_dir_item*,struct btrfs_disk_key*) ; 
 int /*<<< orphan*/  btrfs_set_dir_name_len (struct extent_buffer*,struct btrfs_dir_item*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_set_dir_transid (struct extent_buffer*,struct btrfs_dir_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_dir_type (struct extent_buffer*,struct btrfs_dir_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_key_type (struct btrfs_key*,int /*<<< orphan*/ ) ; 
 struct btrfs_dir_item* insert_with_overflow (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,scalar_t__,char const*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct btrfs_key*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_extent_buffer (struct extent_buffer*,void const*,unsigned long,scalar_t__) ; 

int btrfs_insert_xattr_item(struct btrfs_trans_handle *trans,
			    struct btrfs_root *root,
			    struct btrfs_path *path, u64 objectid,
			    const char *name, u16 name_len,
			    const void *data, u16 data_len)
{
	int ret = 0;
	struct btrfs_dir_item *dir_item;
	unsigned long name_ptr, data_ptr;
	struct btrfs_key key, location;
	struct btrfs_disk_key disk_key;
	struct extent_buffer *leaf;
	u32 data_size;

	BUG_ON(name_len + data_len > BTRFS_MAX_XATTR_SIZE(root));

	key.objectid = objectid;
	btrfs_set_key_type(&key, BTRFS_XATTR_ITEM_KEY);
	key.offset = btrfs_name_hash(name, name_len);

	data_size = sizeof(*dir_item) + name_len + data_len;
	dir_item = insert_with_overflow(trans, root, path, &key, data_size,
					name, name_len);
	if (IS_ERR(dir_item))
		return PTR_ERR(dir_item);
	memset(&location, 0, sizeof(location));

	leaf = path->nodes[0];
	btrfs_cpu_key_to_disk(&disk_key, &location);
	btrfs_set_dir_item_key(leaf, dir_item, &disk_key);
	btrfs_set_dir_type(leaf, dir_item, BTRFS_FT_XATTR);
	btrfs_set_dir_name_len(leaf, dir_item, name_len);
	btrfs_set_dir_transid(leaf, dir_item, trans->transid);
	btrfs_set_dir_data_len(leaf, dir_item, data_len);
	name_ptr = (unsigned long)(dir_item + 1);
	data_ptr = (unsigned long)((char *)name_ptr + name_len);

	write_extent_buffer(leaf, name, name_ptr, name_len);
	write_extent_buffer(leaf, data, data_ptr, data_len);
	btrfs_mark_buffer_dirty(path->nodes[0]);

	return ret;
}