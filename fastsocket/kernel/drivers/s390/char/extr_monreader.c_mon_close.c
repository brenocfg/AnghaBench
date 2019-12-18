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
struct mon_private {struct mon_private** msg_array; scalar_t__ read_index; scalar_t__ write_index; int /*<<< orphan*/  msglim_count; int /*<<< orphan*/  read_ready; int /*<<< orphan*/  iucv_connected; int /*<<< orphan*/  iucv_severed; scalar_t__ path; } ;
struct inode {int dummy; } ;
struct file {struct mon_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MON_IN_USE ; 
 int MON_MSGLIM ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iucv_path_free (scalar_t__) ; 
 int iucv_path_sever (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mon_private*) ; 
 int /*<<< orphan*/  mon_in_use ; 
 int /*<<< orphan*/  monreader_device ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 int /*<<< orphan*/  user_data_sever ; 

__attribute__((used)) static int mon_close(struct inode *inode, struct file *filp)
{
	int rc, i;
	struct mon_private *monpriv = filp->private_data;

	/*
	 * Close IUCV connection and unregister
	 */
	if (monpriv->path) {
		rc = iucv_path_sever(monpriv->path, user_data_sever);
		if (rc)
			pr_warning("Disconnecting the z/VM *MONITOR system "
				   "service failed with rc=%i\n", rc);
		iucv_path_free(monpriv->path);
	}

	atomic_set(&monpriv->iucv_severed, 0);
	atomic_set(&monpriv->iucv_connected, 0);
	atomic_set(&monpriv->read_ready, 0);
	atomic_set(&monpriv->msglim_count, 0);
	monpriv->write_index  = 0;
	monpriv->read_index   = 0;
	dev_set_drvdata(monreader_device, NULL);

	for (i = 0; i < MON_MSGLIM; i++)
		kfree(monpriv->msg_array[i]);
	kfree(monpriv);
	clear_bit(MON_IN_USE, &mon_in_use);
	return 0;
}