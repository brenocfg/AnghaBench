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
struct subch_data_s {int /*<<< orphan*/  sd_rlock; int /*<<< orphan*/  sd_wlock; int /*<<< orphan*/  sd_subch; int /*<<< orphan*/  sd_nasid; int /*<<< orphan*/  sd_wq; int /*<<< orphan*/  sd_rq; } ;
struct poll_table_struct {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int SAL_IROUTER_INTR_RECV ; 
 int SAL_IROUTER_INTR_XMIT ; 
 int ia64_sn_irtr_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int
scdrv_poll(struct file *file, struct poll_table_struct *wait)
{
	unsigned int mask = 0;
	int status = 0;
	struct subch_data_s *sd = (struct subch_data_s *) file->private_data;
	unsigned long flags;

	poll_wait(file, &sd->sd_rq, wait);
	poll_wait(file, &sd->sd_wq, wait);

	spin_lock_irqsave(&sd->sd_rlock, flags);
	spin_lock(&sd->sd_wlock);
	status = ia64_sn_irtr_intr(sd->sd_nasid, sd->sd_subch);
	spin_unlock(&sd->sd_wlock);
	spin_unlock_irqrestore(&sd->sd_rlock, flags);

	if (status > 0) {
		if (status & SAL_IROUTER_INTR_RECV) {
			mask |= POLLIN | POLLRDNORM;
		}
		if (status & SAL_IROUTER_INTR_XMIT) {
			mask |= POLLOUT | POLLWRNORM;
		}
	}

	return mask;
}