#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct file {scalar_t__ private_data; TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_8__ {TYPE_3__** drv; int /*<<< orphan*/  info_waitq; } ;
struct TYPE_7__ {scalar_t__ stavail; int /*<<< orphan*/  st_waitq; } ;
struct TYPE_5__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 unsigned int ISDN_MINOR_CTRL ; 
 unsigned int ISDN_MINOR_CTRLMAX ; 
 unsigned int ISDN_MINOR_PPPMAX ; 
 unsigned int ISDN_MINOR_STATUS ; 
 unsigned int POLLERR ; 
 unsigned int POLLHUP ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 TYPE_4__* dev ; 
 unsigned int iminor (int /*<<< orphan*/ ) ; 
 int isdn_minor2drv (unsigned int) ; 
 unsigned int isdn_ppp_poll (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static unsigned int
isdn_poll(struct file *file, poll_table * wait)
{
	unsigned int mask = 0;
	unsigned int minor = iminor(file->f_path.dentry->d_inode);
	int drvidx = isdn_minor2drv(minor - ISDN_MINOR_CTRL);

	lock_kernel();
	if (minor == ISDN_MINOR_STATUS) {
		poll_wait(file, &(dev->info_waitq), wait);
		/* mask = POLLOUT | POLLWRNORM; */
		if (file->private_data) {
			mask |= POLLIN | POLLRDNORM;
		}
		goto out;
	}
	if (minor >= ISDN_MINOR_CTRL && minor <= ISDN_MINOR_CTRLMAX) {
		if (drvidx < 0) {
			/* driver deregistered while file open */
			mask = POLLHUP;
			goto out;
		}
		poll_wait(file, &(dev->drv[drvidx]->st_waitq), wait);
		mask = POLLOUT | POLLWRNORM;
		if (dev->drv[drvidx]->stavail) {
			mask |= POLLIN | POLLRDNORM;
		}
		goto out;
	}
#ifdef CONFIG_ISDN_PPP
	if (minor <= ISDN_MINOR_PPPMAX) {
		mask = isdn_ppp_poll(file, wait);
		goto out;
	}
#endif
	mask = POLLERR;
 out:
	unlock_kernel();
	return mask;
}