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
struct dst_state {int need_exit; int /*<<< orphan*/  thread_wait; } ;
struct dst_node {struct dst_state* state; scalar_t__ bdev; TYPE_1__* disk; scalar_t__ queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  first_minor; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  blk_cleanup_queue (scalar_t__) ; 
 int /*<<< orphan*/  blkdev_put (scalar_t__,int) ; 
 int /*<<< orphan*/  dst_hash_lock ; 
 int /*<<< orphan*/  dst_index_idr ; 
 int /*<<< orphan*/  dst_state_exit_connected (struct dst_state*) ; 
 int /*<<< orphan*/  dst_state_lock (struct dst_state*) ; 
 int /*<<< orphan*/  dst_state_put (struct dst_state*) ; 
 int /*<<< orphan*/  dst_state_unlock (struct dst_state*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 
 int /*<<< orphan*/  sync_blockdev (scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dst_node_cleanup(struct dst_node *n)
{
	struct dst_state *st = n->state;

	if (!st)
		return;

	if (n->queue) {
		blk_cleanup_queue(n->queue);

		mutex_lock(&dst_hash_lock);
		idr_remove(&dst_index_idr, n->disk->first_minor);
		mutex_unlock(&dst_hash_lock);

		put_disk(n->disk);
	}

	if (n->bdev) {
		sync_blockdev(n->bdev);
		blkdev_put(n->bdev, FMODE_READ|FMODE_WRITE);
	}

	dst_state_lock(st);
	st->need_exit = 1;
	dst_state_exit_connected(st);
	dst_state_unlock(st);

	wake_up(&st->thread_wait);

	dst_state_put(st);
	n->state = NULL;
}