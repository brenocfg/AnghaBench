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
struct vmlogrdr_priv_t {int dev_in_use; int buffer_free; int /*<<< orphan*/ * path; int /*<<< orphan*/  autopurge; scalar_t__ autorecording; scalar_t__ iucv_path_severed; scalar_t__ connection_established; int /*<<< orphan*/  system_service; int /*<<< orphan*/  priv_lock; int /*<<< orphan*/  receive_ready; } ;
struct inode {int dummy; } ;
struct file {int f_flags; int /*<<< orphan*/ * f_op; struct vmlogrdr_priv_t* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAXMINOR ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_wait_queue ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/ * iucv_path_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iucv_path_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct vmlogrdr_priv_t*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct vmlogrdr_priv_t* sys_ser ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  vmlogrdr_fops ; 
 int /*<<< orphan*/  vmlogrdr_iucv_handler ; 
 int vmlogrdr_recording (struct vmlogrdr_priv_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vmlogrdr_open (struct inode *inode, struct file *filp)
{
	int dev_num = 0;
	struct vmlogrdr_priv_t * logptr = NULL;
	int connect_rc = 0;
	int ret;

	dev_num = iminor(inode);
	if (dev_num > MAXMINOR)
		return -ENODEV;
	logptr = &sys_ser[dev_num];

	/*
	 * only allow for blocking reads to be open
	 */
	if (filp->f_flags & O_NONBLOCK)
		return -ENOSYS;

	/* Besure this device hasn't already been opened */
	lock_kernel();
	spin_lock_bh(&logptr->priv_lock);
	if (logptr->dev_in_use)	{
		spin_unlock_bh(&logptr->priv_lock);
		unlock_kernel();
		return -EBUSY;
	}
	logptr->dev_in_use = 1;
	logptr->connection_established = 0;
	logptr->iucv_path_severed = 0;
	atomic_set(&logptr->receive_ready, 0);
	logptr->buffer_free = 1;
	spin_unlock_bh(&logptr->priv_lock);

	/* set the file options */
	filp->private_data = logptr;
	filp->f_op = &vmlogrdr_fops;

	/* start recording for this service*/
	if (logptr->autorecording) {
		ret = vmlogrdr_recording(logptr,1,logptr->autopurge);
		if (ret)
			pr_warning("vmlogrdr: failed to start "
				   "recording automatically\n");
	}

	/* create connection to the system service */
	logptr->path = iucv_path_alloc(10, 0, GFP_KERNEL);
	if (!logptr->path)
		goto out_dev;
	connect_rc = iucv_path_connect(logptr->path, &vmlogrdr_iucv_handler,
				       logptr->system_service, NULL, NULL,
				       logptr);
	if (connect_rc) {
		pr_err("vmlogrdr: iucv connection to %s "
		       "failed with rc %i \n",
		       logptr->system_service, connect_rc);
		goto out_path;
	}

	/* We've issued the connect and now we must wait for a
	 * ConnectionComplete or ConnectinSevered Interrupt
	 * before we can continue to process.
	 */
	wait_event(conn_wait_queue, (logptr->connection_established)
		   || (logptr->iucv_path_severed));
	if (logptr->iucv_path_severed)
		goto out_record;
 	ret = nonseekable_open(inode, filp);
	unlock_kernel();
	return ret;

out_record:
	if (logptr->autorecording)
		vmlogrdr_recording(logptr,0,logptr->autopurge);
out_path:
	kfree(logptr->path);	/* kfree(NULL) is ok. */
	logptr->path = NULL;
out_dev:
	logptr->dev_in_use = 0;
	unlock_kernel();
	return -EIO;
}