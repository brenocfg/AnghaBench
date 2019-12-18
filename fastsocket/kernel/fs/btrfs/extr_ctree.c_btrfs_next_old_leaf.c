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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int leave_spinning; int keep_locks; int* slots; int* locks; int /*<<< orphan*/  skip_locking; struct extent_buffer** nodes; } ;
struct btrfs_key {int dummy; } ;

/* Variables and functions */
 int BTRFS_MAX_LEVEL ; 
 int BTRFS_READ_LOCK ; 
 int EAGAIN ; 
 int /*<<< orphan*/  btrfs_clear_path_blocking (struct btrfs_path*,struct extent_buffer*,int) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_old_slot (struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,scalar_t__) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_path_blocking (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_tree_read_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_unlock_rw (struct extent_buffer*,int) ; 
 int btrfs_try_tree_read_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 int read_block_for_search (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_path*,struct extent_buffer**,int,int,struct btrfs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_up (struct btrfs_path*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_next_old_leaf(struct btrfs_root *root, struct btrfs_path *path,
			u64 time_seq)
{
	int slot;
	int level;
	struct extent_buffer *c;
	struct extent_buffer *next;
	struct btrfs_key key;
	u32 nritems;
	int ret;
	int old_spinning = path->leave_spinning;
	int next_rw_lock = 0;

	nritems = btrfs_header_nritems(path->nodes[0]);
	if (nritems == 0)
		return 1;

	btrfs_item_key_to_cpu(path->nodes[0], &key, nritems - 1);
again:
	level = 1;
	next = NULL;
	next_rw_lock = 0;
	btrfs_release_path(path);

	path->keep_locks = 1;
	path->leave_spinning = 1;

	if (time_seq)
		ret = btrfs_search_old_slot(root, &key, path, time_seq);
	else
		ret = btrfs_search_slot(NULL, root, &key, path, 0, 0);
	path->keep_locks = 0;

	if (ret < 0)
		return ret;

	nritems = btrfs_header_nritems(path->nodes[0]);
	/*
	 * by releasing the path above we dropped all our locks.  A balance
	 * could have added more items next to the key that used to be
	 * at the very end of the block.  So, check again here and
	 * advance the path if there are now more items available.
	 */
	if (nritems > 0 && path->slots[0] < nritems - 1) {
		if (ret == 0)
			path->slots[0]++;
		ret = 0;
		goto done;
	}

	while (level < BTRFS_MAX_LEVEL) {
		if (!path->nodes[level]) {
			ret = 1;
			goto done;
		}

		slot = path->slots[level] + 1;
		c = path->nodes[level];
		if (slot >= btrfs_header_nritems(c)) {
			level++;
			if (level == BTRFS_MAX_LEVEL) {
				ret = 1;
				goto done;
			}
			continue;
		}

		if (next) {
			btrfs_tree_unlock_rw(next, next_rw_lock);
			free_extent_buffer(next);
		}

		next = c;
		next_rw_lock = path->locks[level];
		ret = read_block_for_search(NULL, root, path, &next, level,
					    slot, &key, 0);
		if (ret == -EAGAIN)
			goto again;

		if (ret < 0) {
			btrfs_release_path(path);
			goto done;
		}

		if (!path->skip_locking) {
			ret = btrfs_try_tree_read_lock(next);
			if (!ret && time_seq) {
				/*
				 * If we don't get the lock, we may be racing
				 * with push_leaf_left, holding that lock while
				 * itself waiting for the leaf we've currently
				 * locked. To solve this situation, we give up
				 * on our lock and cycle.
				 */
				btrfs_release_path(path);
				cond_resched();
				goto again;
			}
			if (!ret) {
				btrfs_set_path_blocking(path);
				btrfs_tree_read_lock(next);
				btrfs_clear_path_blocking(path, next,
							  BTRFS_READ_LOCK);
			}
			next_rw_lock = BTRFS_READ_LOCK;
		}
		break;
	}
	path->slots[level] = slot;
	while (1) {
		level--;
		c = path->nodes[level];
		if (path->locks[level])
			btrfs_tree_unlock_rw(c, path->locks[level]);

		free_extent_buffer(c);
		path->nodes[level] = next;
		path->slots[level] = 0;
		if (!path->skip_locking)
			path->locks[level] = next_rw_lock;
		if (!level)
			break;

		ret = read_block_for_search(NULL, root, path, &next, level,
					    0, &key, 0);
		if (ret == -EAGAIN)
			goto again;

		if (ret < 0) {
			btrfs_release_path(path);
			goto done;
		}

		if (!path->skip_locking) {
			ret = btrfs_try_tree_read_lock(next);
			if (!ret) {
				btrfs_set_path_blocking(path);
				btrfs_tree_read_lock(next);
				btrfs_clear_path_blocking(path, next,
							  BTRFS_READ_LOCK);
			}
			next_rw_lock = BTRFS_READ_LOCK;
		}
	}
	ret = 0;
done:
	unlock_up(path, 0, 1, 0, NULL);
	path->leave_spinning = old_spinning;
	if (!old_spinning)
		btrfs_set_path_blocking(path);

	return ret;
}