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
struct venus_comm {scalar_t__ vc_seq; int /*<<< orphan*/ * vc_sb; int /*<<< orphan*/  vc_waitq; int /*<<< orphan*/  vc_processing; int /*<<< orphan*/  vc_pending; int /*<<< orphan*/  vc_inuse; } ;
struct inode {int dummy; } ;
struct file {struct venus_comm* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_CODADEVS ; 
 struct venus_comm* coda_comms ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int coda_psdev_open(struct inode * inode, struct file * file)
{
	struct venus_comm *vcp;
	int idx, err;

	idx = iminor(inode);
	if (idx < 0 || idx >= MAX_CODADEVS)
		return -ENODEV;

	lock_kernel();

	err = -EBUSY;
	vcp = &coda_comms[idx];
	if (!vcp->vc_inuse) {
		vcp->vc_inuse++;

		INIT_LIST_HEAD(&vcp->vc_pending);
		INIT_LIST_HEAD(&vcp->vc_processing);
		init_waitqueue_head(&vcp->vc_waitq);
		vcp->vc_sb = NULL;
		vcp->vc_seq = 0;

		file->private_data = vcp;
		err = 0;
	}

	unlock_kernel();
	return err;
}