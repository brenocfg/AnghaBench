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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int dsp_minor; int mixer_minor; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__ dev ; 
 int dsp_release (struct file*) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int dev_release(struct inode *inode, struct file *file)
{
	int minor = iminor(inode);
	int err = 0;

	lock_kernel();
	if (minor == dev.dsp_minor)
		err = dsp_release(file);
	else if (minor == dev.mixer_minor) {
		/* nothing */
	} else
		err = -EINVAL;
	unlock_kernel();
	return err;
}