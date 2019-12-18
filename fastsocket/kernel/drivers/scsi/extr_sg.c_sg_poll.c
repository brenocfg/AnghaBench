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
struct file {scalar_t__ private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_8__ {TYPE_1__* disk; scalar_t__ detached; } ;
struct TYPE_7__ {int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  rq_list_lock; TYPE_2__* headrp; int /*<<< orphan*/  read_wait; scalar_t__ closed; TYPE_4__* parentdp; } ;
struct TYPE_6__ {int done; int /*<<< orphan*/  sg_io_owned; struct TYPE_6__* nextrp; } ;
struct TYPE_5__ {int /*<<< orphan*/  disk_name; } ;
typedef  TYPE_2__ Sg_request ;
typedef  TYPE_3__ Sg_fd ;
typedef  TYPE_4__ Sg_device ;

/* Variables and functions */
 unsigned int POLLERR ; 
 unsigned int POLLHUP ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int /*<<< orphan*/  SCSI_LOG_TIMEOUT (int,int /*<<< orphan*/ ) ; 
 int SG_MAX_QUEUE ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int
sg_poll(struct file *filp, poll_table * wait)
{
	unsigned int res = 0;
	Sg_device *sdp;
	Sg_fd *sfp;
	Sg_request *srp;
	int count = 0;
	unsigned long iflags;

	if ((!(sfp = (Sg_fd *) filp->private_data)) || (!(sdp = sfp->parentdp))
	    || sfp->closed)
		return POLLERR;
	poll_wait(filp, &sfp->read_wait, wait);
	read_lock_irqsave(&sfp->rq_list_lock, iflags);
	for (srp = sfp->headrp; srp; srp = srp->nextrp) {
		/* if any read waiting, flag it */
		if ((0 == res) && (1 == srp->done) && (!srp->sg_io_owned))
			res = POLLIN | POLLRDNORM;
		++count;
	}
	read_unlock_irqrestore(&sfp->rq_list_lock, iflags);

	if (sdp->detached)
		res |= POLLHUP;
	else if (!sfp->cmd_q) {
		if (0 == count)
			res |= POLLOUT | POLLWRNORM;
	} else if (count < SG_MAX_QUEUE)
		res |= POLLOUT | POLLWRNORM;
	SCSI_LOG_TIMEOUT(3, printk("sg_poll: %s, res=0x%x\n",
				   sdp->disk->disk_name, (int) res));
	return res;
}