#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct map_lookup {int num_stripes; int type; int /*<<< orphan*/  sub_stripes; int /*<<< orphan*/  stripe_len; TYPE_2__* stripes; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_stripe {int /*<<< orphan*/  dev_uuid; } ;
struct TYPE_6__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {int /*<<< orphan*/  sectorsize; TYPE_3__ root_key; TYPE_1__* fs_info; } ;
struct btrfs_key {int offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct btrfs_device {int bytes_used; int /*<<< orphan*/  uuid; int /*<<< orphan*/  devid; } ;
struct btrfs_chunk {struct btrfs_stripe stripe; } ;
struct TYPE_5__ {int physical; struct btrfs_device* dev; } ;
struct TYPE_4__ {int free_chunk_space; int /*<<< orphan*/  free_chunk_lock; struct btrfs_root* chunk_root; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_SYSTEM ; 
 int /*<<< orphan*/  BTRFS_CHUNK_ITEM_KEY ; 
 int /*<<< orphan*/  BTRFS_FIRST_CHUNK_TREE_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_UUID_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int btrfs_add_system_chunk (struct btrfs_root*,struct btrfs_key*,struct btrfs_chunk*,size_t) ; 
 size_t btrfs_chunk_item_size (int) ; 
 int btrfs_insert_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_chunk*,size_t) ; 
 int /*<<< orphan*/  btrfs_set_stack_chunk_io_align (struct btrfs_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_chunk_io_width (struct btrfs_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_chunk_length (struct btrfs_chunk*,int) ; 
 int /*<<< orphan*/  btrfs_set_stack_chunk_num_stripes (struct btrfs_chunk*,int) ; 
 int /*<<< orphan*/  btrfs_set_stack_chunk_owner (struct btrfs_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_chunk_sector_size (struct btrfs_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_chunk_stripe_len (struct btrfs_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_chunk_sub_stripes (struct btrfs_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_chunk_type (struct btrfs_chunk*,int) ; 
 int /*<<< orphan*/  btrfs_set_stack_stripe_devid (struct btrfs_stripe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_stripe_offset (struct btrfs_stripe*,int) ; 
 int btrfs_update_device (struct btrfs_trans_handle*,struct btrfs_device*) ; 
 int /*<<< orphan*/  kfree (struct btrfs_chunk*) ; 
 struct btrfs_chunk* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __finish_chunk_alloc(struct btrfs_trans_handle *trans,
				struct btrfs_root *extent_root,
				struct map_lookup *map, u64 chunk_offset,
				u64 chunk_size, u64 stripe_size)
{
	u64 dev_offset;
	struct btrfs_key key;
	struct btrfs_root *chunk_root = extent_root->fs_info->chunk_root;
	struct btrfs_device *device;
	struct btrfs_chunk *chunk;
	struct btrfs_stripe *stripe;
	size_t item_size = btrfs_chunk_item_size(map->num_stripes);
	int index = 0;
	int ret;

	chunk = kzalloc(item_size, GFP_NOFS);
	if (!chunk)
		return -ENOMEM;

	index = 0;
	while (index < map->num_stripes) {
		device = map->stripes[index].dev;
		device->bytes_used += stripe_size;
		ret = btrfs_update_device(trans, device);
		if (ret)
			goto out_free;
		index++;
	}

	spin_lock(&extent_root->fs_info->free_chunk_lock);
	extent_root->fs_info->free_chunk_space -= (stripe_size *
						   map->num_stripes);
	spin_unlock(&extent_root->fs_info->free_chunk_lock);

	index = 0;
	stripe = &chunk->stripe;
	while (index < map->num_stripes) {
		device = map->stripes[index].dev;
		dev_offset = map->stripes[index].physical;

		btrfs_set_stack_stripe_devid(stripe, device->devid);
		btrfs_set_stack_stripe_offset(stripe, dev_offset);
		memcpy(stripe->dev_uuid, device->uuid, BTRFS_UUID_SIZE);
		stripe++;
		index++;
	}

	btrfs_set_stack_chunk_length(chunk, chunk_size);
	btrfs_set_stack_chunk_owner(chunk, extent_root->root_key.objectid);
	btrfs_set_stack_chunk_stripe_len(chunk, map->stripe_len);
	btrfs_set_stack_chunk_type(chunk, map->type);
	btrfs_set_stack_chunk_num_stripes(chunk, map->num_stripes);
	btrfs_set_stack_chunk_io_align(chunk, map->stripe_len);
	btrfs_set_stack_chunk_io_width(chunk, map->stripe_len);
	btrfs_set_stack_chunk_sector_size(chunk, extent_root->sectorsize);
	btrfs_set_stack_chunk_sub_stripes(chunk, map->sub_stripes);

	key.objectid = BTRFS_FIRST_CHUNK_TREE_OBJECTID;
	key.type = BTRFS_CHUNK_ITEM_KEY;
	key.offset = chunk_offset;

	ret = btrfs_insert_item(trans, chunk_root, &key, chunk, item_size);

	if (ret == 0 && map->type & BTRFS_BLOCK_GROUP_SYSTEM) {
		/*
		 * TODO: Cleanup of inserted chunk root in case of
		 * failure.
		 */
		ret = btrfs_add_system_chunk(chunk_root, &key, chunk,
					     item_size);
	}

out_free:
	kfree(chunk);
	return ret;
}