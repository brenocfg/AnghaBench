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
struct urfile {TYPE_1__* urd; } ;
struct inode {int dummy; } ;
struct file {struct urfile* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  open_lock; int /*<<< orphan*/  open_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  urdev_put (TYPE_1__*) ; 
 int /*<<< orphan*/  urfile_free (struct urfile*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ur_release(struct inode *inode, struct file *file)
{
	struct urfile *urf = file->private_data;

	TRACE("ur_release\n");
	spin_lock(&urf->urd->open_lock);
	urf->urd->open_flag--;
	spin_unlock(&urf->urd->open_lock);
	wake_up_interruptible(&urf->urd->wait);
	urdev_put(urf->urd);
	urfile_free(urf);
	return 0;
}