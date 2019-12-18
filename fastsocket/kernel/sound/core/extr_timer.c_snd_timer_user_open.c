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
struct snd_timer_user {int ticks; int queue_size; int /*<<< orphan*/ * queue; int /*<<< orphan*/  tread_sem; int /*<<< orphan*/  qchange_sleep; int /*<<< orphan*/  qlock; } ;
struct snd_timer_read {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct snd_timer_user* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_timer_user*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_timer_user* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_timer_user_open(struct inode *inode, struct file *file)
{
	struct snd_timer_user *tu;
	int err;

	err = nonseekable_open(inode, file);
	if (err < 0)
		return err;

	tu = kzalloc(sizeof(*tu), GFP_KERNEL);
	if (tu == NULL)
		return -ENOMEM;
	spin_lock_init(&tu->qlock);
	init_waitqueue_head(&tu->qchange_sleep);
	mutex_init(&tu->tread_sem);
	tu->ticks = 1;
	tu->queue_size = 128;
	tu->queue = kmalloc(tu->queue_size * sizeof(struct snd_timer_read),
			    GFP_KERNEL);
	if (tu->queue == NULL) {
		kfree(tu);
		return -ENOMEM;
	}
	file->private_data = tu;
	return 0;
}