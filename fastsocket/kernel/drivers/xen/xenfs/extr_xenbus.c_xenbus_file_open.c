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
struct xenbus_file_priv {int /*<<< orphan*/  msgbuffer_mutex; int /*<<< orphan*/  reply_mutex; int /*<<< orphan*/  read_waitq; int /*<<< orphan*/  read_buffers; int /*<<< orphan*/  watches; int /*<<< orphan*/  transactions; } ;
struct inode {int dummy; } ;
struct file {struct xenbus_file_priv* private_data; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct xenbus_file_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ xen_store_evtchn ; 

__attribute__((used)) static int xenbus_file_open(struct inode *inode, struct file *filp)
{
	struct xenbus_file_priv *u;

	if (xen_store_evtchn == 0)
		return -ENOENT;

	nonseekable_open(inode, filp);

	u = kzalloc(sizeof(*u), GFP_KERNEL);
	if (u == NULL)
		return -ENOMEM;

	INIT_LIST_HEAD(&u->transactions);
	INIT_LIST_HEAD(&u->watches);
	INIT_LIST_HEAD(&u->read_buffers);
	init_waitqueue_head(&u->read_waitq);

	mutex_init(&u->reply_mutex);
	mutex_init(&u->msgbuffer_mutex);

	filp->private_data = u;

	return 0;
}