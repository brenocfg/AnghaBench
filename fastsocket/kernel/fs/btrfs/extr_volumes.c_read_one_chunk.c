#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct map_lookup {int num_stripes; TYPE_2__* stripes; int /*<<< orphan*/  sub_stripes; int /*<<< orphan*/  type; int /*<<< orphan*/  stripe_len; int /*<<< orphan*/  sector_size; int /*<<< orphan*/  io_align; int /*<<< orphan*/  io_width; } ;
struct extent_map {scalar_t__ start; scalar_t__ len; scalar_t__ block_len; scalar_t__ block_start; struct block_device* bdev; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
struct btrfs_mapping_tree {TYPE_3__ map_tree; } ;
struct btrfs_key {scalar_t__ offset; } ;
struct btrfs_chunk {int dummy; } ;
struct block_device {int dummy; } ;
struct TYPE_10__ {int in_fs_metadata; } ;
struct TYPE_8__ {TYPE_4__* dev; int /*<<< orphan*/  physical; } ;
struct TYPE_7__ {struct btrfs_mapping_tree mapping_tree; } ;

/* Variables and functions */
 int BTRFS_UUID_SIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEGRADED ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int add_extent_mapping (TYPE_3__*,struct extent_map*) ; 
 TYPE_4__* add_missing_dev (struct btrfs_root*,scalar_t__,int /*<<< orphan*/ *) ; 
 struct extent_map* alloc_extent_map () ; 
 int /*<<< orphan*/  btrfs_chunk_io_align (struct extent_buffer*,struct btrfs_chunk*) ; 
 int /*<<< orphan*/  btrfs_chunk_io_width (struct extent_buffer*,struct btrfs_chunk*) ; 
 scalar_t__ btrfs_chunk_length (struct extent_buffer*,struct btrfs_chunk*) ; 
 int btrfs_chunk_num_stripes (struct extent_buffer*,struct btrfs_chunk*) ; 
 int /*<<< orphan*/  btrfs_chunk_sector_size (struct extent_buffer*,struct btrfs_chunk*) ; 
 int /*<<< orphan*/  btrfs_chunk_stripe_len (struct extent_buffer*,struct btrfs_chunk*) ; 
 int /*<<< orphan*/  btrfs_chunk_sub_stripes (struct extent_buffer*,struct btrfs_chunk*) ; 
 int /*<<< orphan*/  btrfs_chunk_type (struct extent_buffer*,struct btrfs_chunk*) ; 
 TYPE_4__* btrfs_find_device (struct btrfs_root*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_stripe_dev_uuid_nr (struct btrfs_chunk*,int) ; 
 scalar_t__ btrfs_stripe_devid_nr (struct extent_buffer*,struct btrfs_chunk*,int) ; 
 int /*<<< orphan*/  btrfs_stripe_offset_nr (struct extent_buffer*,struct btrfs_chunk*,int) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 int /*<<< orphan*/  kfree (struct map_lookup*) ; 
 struct map_lookup* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct extent_map* lookup_extent_mapping (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  map_lookup_size (int) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ *,unsigned long,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_one_chunk(struct btrfs_root *root, struct btrfs_key *key,
			  struct extent_buffer *leaf,
			  struct btrfs_chunk *chunk)
{
	struct btrfs_mapping_tree *map_tree = &root->fs_info->mapping_tree;
	struct map_lookup *map;
	struct extent_map *em;
	u64 logical;
	u64 length;
	u64 devid;
	u8 uuid[BTRFS_UUID_SIZE];
	int num_stripes;
	int ret;
	int i;

	logical = key->offset;
	length = btrfs_chunk_length(leaf, chunk);

	read_lock(&map_tree->map_tree.lock);
	em = lookup_extent_mapping(&map_tree->map_tree, logical, 1);
	read_unlock(&map_tree->map_tree.lock);

	/* already mapped? */
	if (em && em->start <= logical && em->start + em->len > logical) {
		free_extent_map(em);
		return 0;
	} else if (em) {
		free_extent_map(em);
	}

	em = alloc_extent_map();
	if (!em)
		return -ENOMEM;
	num_stripes = btrfs_chunk_num_stripes(leaf, chunk);
	map = kmalloc(map_lookup_size(num_stripes), GFP_NOFS);
	if (!map) {
		free_extent_map(em);
		return -ENOMEM;
	}

	em->bdev = (struct block_device *)map;
	em->start = logical;
	em->len = length;
	em->block_start = 0;
	em->block_len = em->len;

	map->num_stripes = num_stripes;
	map->io_width = btrfs_chunk_io_width(leaf, chunk);
	map->io_align = btrfs_chunk_io_align(leaf, chunk);
	map->sector_size = btrfs_chunk_sector_size(leaf, chunk);
	map->stripe_len = btrfs_chunk_stripe_len(leaf, chunk);
	map->type = btrfs_chunk_type(leaf, chunk);
	map->sub_stripes = btrfs_chunk_sub_stripes(leaf, chunk);
	for (i = 0; i < num_stripes; i++) {
		map->stripes[i].physical =
			btrfs_stripe_offset_nr(leaf, chunk, i);
		devid = btrfs_stripe_devid_nr(leaf, chunk, i);
		read_extent_buffer(leaf, uuid, (unsigned long)
				   btrfs_stripe_dev_uuid_nr(chunk, i),
				   BTRFS_UUID_SIZE);
		map->stripes[i].dev = btrfs_find_device(root, devid, uuid,
							NULL);
		if (!map->stripes[i].dev && !btrfs_test_opt(root, DEGRADED)) {
			kfree(map);
			free_extent_map(em);
			return -EIO;
		}
		if (!map->stripes[i].dev) {
			map->stripes[i].dev =
				add_missing_dev(root, devid, uuid);
			if (!map->stripes[i].dev) {
				kfree(map);
				free_extent_map(em);
				return -EIO;
			}
		}
		map->stripes[i].dev->in_fs_metadata = 1;
	}

	write_lock(&map_tree->map_tree.lock);
	ret = add_extent_mapping(&map_tree->map_tree, em);
	write_unlock(&map_tree->map_tree.lock);
	BUG_ON(ret); /* Tree corruption */
	free_extent_map(em);

	return 0;
}