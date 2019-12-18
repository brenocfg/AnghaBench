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
struct inode {int /*<<< orphan*/  inotify_mutex; } ;
struct audit_tree {int /*<<< orphan*/  same_root; struct audit_chunk* root; int /*<<< orphan*/  chunks; scalar_t__ goner; } ;
struct audit_chunk {int dead; int /*<<< orphan*/  trees; TYPE_1__* owners; int /*<<< orphan*/  watch; } ;
struct TYPE_2__ {unsigned int index; int /*<<< orphan*/  list; struct audit_tree* owner; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int IN_DELETE_SELF ; 
 int IN_IGNORED ; 
 struct audit_chunk* alloc_chunk (int) ; 
 int /*<<< orphan*/  free_chunk (struct audit_chunk*) ; 
 int /*<<< orphan*/  get_tree (struct audit_tree*) ; 
 int /*<<< orphan*/  hash_lock ; 
 scalar_t__ inotify_add_watch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct inode*,int) ; 
 int /*<<< orphan*/  inotify_evict_watch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_hash (struct audit_chunk*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_inotify_watch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtree_ih ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_chunk(struct inode *inode, struct audit_tree *tree)
{
	struct audit_chunk *chunk = alloc_chunk(1);
	if (!chunk)
		return -ENOMEM;

	if (inotify_add_watch(rtree_ih, &chunk->watch, inode, IN_IGNORED | IN_DELETE_SELF) < 0) {
		free_chunk(chunk);
		return -ENOSPC;
	}

	mutex_lock(&inode->inotify_mutex);
	spin_lock(&hash_lock);
	if (tree->goner) {
		spin_unlock(&hash_lock);
		chunk->dead = 1;
		inotify_evict_watch(&chunk->watch);
		mutex_unlock(&inode->inotify_mutex);
		put_inotify_watch(&chunk->watch);
		return 0;
	}
	chunk->owners[0].index = (1U << 31);
	chunk->owners[0].owner = tree;
	get_tree(tree);
	list_add(&chunk->owners[0].list, &tree->chunks);
	if (!tree->root) {
		tree->root = chunk;
		list_add(&tree->same_root, &chunk->trees);
	}
	insert_hash(chunk);
	spin_unlock(&hash_lock);
	mutex_unlock(&inode->inotify_mutex);
	return 0;
}