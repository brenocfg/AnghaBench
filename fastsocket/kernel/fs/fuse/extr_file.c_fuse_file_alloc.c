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
struct fuse_file {scalar_t__ kh; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  polled_node; int /*<<< orphan*/  count; int /*<<< orphan*/  write_entry; int /*<<< orphan*/  reserved_req; struct fuse_conn* fc; } ;
struct fuse_conn {int /*<<< orphan*/  lock; scalar_t__ khctr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_request_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fuse_file*) ; 
 struct fuse_file* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

struct fuse_file *fuse_file_alloc(struct fuse_conn *fc)
{
	struct fuse_file *ff;

	ff = kmalloc(sizeof(struct fuse_file), GFP_KERNEL);
	if (unlikely(!ff))
		return NULL;

	ff->fc = fc;
	ff->reserved_req = fuse_request_alloc(0);
	if (unlikely(!ff->reserved_req)) {
		kfree(ff);
		return NULL;
	}

	INIT_LIST_HEAD(&ff->write_entry);
	atomic_set(&ff->count, 0);
	RB_CLEAR_NODE(&ff->polled_node);
	init_waitqueue_head(&ff->poll_wait);

	spin_lock(&fc->lock);
	ff->kh = ++fc->khctr;
	spin_unlock(&fc->lock);

	return ff;
}