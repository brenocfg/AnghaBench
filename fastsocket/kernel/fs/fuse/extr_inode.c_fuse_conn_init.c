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
struct fuse_conn {int blocked; int attr_version; int /*<<< orphan*/  scramble_key; scalar_t__ reqctr; int /*<<< orphan*/  polled_files; scalar_t__ khctr; int /*<<< orphan*/  congestion_threshold; int /*<<< orphan*/  max_background; int /*<<< orphan*/  num_waiting; int /*<<< orphan*/  entry; int /*<<< orphan*/  bg_queue; int /*<<< orphan*/  interrupts; int /*<<< orphan*/  io; int /*<<< orphan*/  processing; int /*<<< orphan*/  pending; int /*<<< orphan*/  reserved_req_waitq; int /*<<< orphan*/  blocked_waitq; int /*<<< orphan*/  waitq; int /*<<< orphan*/  count; int /*<<< orphan*/  killsb; int /*<<< orphan*/  inst_mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_DEFAULT_CONGESTION_THRESHOLD ; 
 int /*<<< orphan*/  FUSE_DEFAULT_MAX_BACKGROUND ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fuse_conn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void fuse_conn_init(struct fuse_conn *fc)
{
	memset(fc, 0, sizeof(*fc));
	spin_lock_init(&fc->lock);
	mutex_init(&fc->inst_mutex);
	init_rwsem(&fc->killsb);
	atomic_set(&fc->count, 1);
	init_waitqueue_head(&fc->waitq);
	init_waitqueue_head(&fc->blocked_waitq);
	init_waitqueue_head(&fc->reserved_req_waitq);
	INIT_LIST_HEAD(&fc->pending);
	INIT_LIST_HEAD(&fc->processing);
	INIT_LIST_HEAD(&fc->io);
	INIT_LIST_HEAD(&fc->interrupts);
	INIT_LIST_HEAD(&fc->bg_queue);
	INIT_LIST_HEAD(&fc->entry);
	atomic_set(&fc->num_waiting, 0);
	fc->max_background = FUSE_DEFAULT_MAX_BACKGROUND;
	fc->congestion_threshold = FUSE_DEFAULT_CONGESTION_THRESHOLD;
	fc->khctr = 0;
	fc->polled_files = RB_ROOT;
	fc->reqctr = 0;
	fc->blocked = 1;
	fc->attr_version = 1;
	get_random_bytes(&fc->scramble_key, sizeof(fc->scramble_key));
}