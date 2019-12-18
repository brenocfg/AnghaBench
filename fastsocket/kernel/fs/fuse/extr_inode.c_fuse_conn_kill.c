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
struct fuse_conn {int /*<<< orphan*/  entry; int /*<<< orphan*/  reserved_req_waitq; int /*<<< orphan*/  blocked_waitq; int /*<<< orphan*/  waitq; int /*<<< orphan*/  fasync; int /*<<< orphan*/  lock; scalar_t__ blocked; scalar_t__ connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  fuse_bdi_destroy (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_ctl_remove_conn (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_mutex ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void fuse_conn_kill(struct fuse_conn *fc)
{
	spin_lock(&fc->lock);
	fc->connected = 0;
	fc->blocked = 0;
	spin_unlock(&fc->lock);
	/* Flush all readers on this fs */
	kill_fasync(&fc->fasync, SIGIO, POLL_IN);
	wake_up_all(&fc->waitq);
	wake_up_all(&fc->blocked_waitq);
	wake_up_all(&fc->reserved_req_waitq);
	mutex_lock(&fuse_mutex);
	list_del(&fc->entry);
	fuse_ctl_remove_conn(fc);
	mutex_unlock(&fuse_mutex);
	fuse_bdi_destroy(fc);
}