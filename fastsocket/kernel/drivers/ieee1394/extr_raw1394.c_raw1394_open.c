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
typedef  scalar_t__ u8 ;
struct inode {int dummy; } ;
struct file_info {int /*<<< orphan*/  addr_list; int /*<<< orphan*/  wait_complete; int /*<<< orphan*/  reqlists_lock; int /*<<< orphan*/  req_complete; int /*<<< orphan*/  req_pending; int /*<<< orphan*/  state; int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  list; scalar_t__ notification; } ;
struct file {struct file_info* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ RAW1394_NOTIFY_ON ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct file_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opened ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raw1394_open(struct inode *inode, struct file *file)
{
	struct file_info *fi;

	fi = kzalloc(sizeof(*fi), GFP_KERNEL);
	if (!fi)
		return -ENOMEM;

	fi->notification = (u8) RAW1394_NOTIFY_ON;	/* busreset notification */

	INIT_LIST_HEAD(&fi->list);
	mutex_init(&fi->state_mutex);
	fi->state = opened;
	INIT_LIST_HEAD(&fi->req_pending);
	INIT_LIST_HEAD(&fi->req_complete);
	spin_lock_init(&fi->reqlists_lock);
	init_waitqueue_head(&fi->wait_complete);
	INIT_LIST_HEAD(&fi->addr_list);

	file->private_data = fi;

	return 0;
}