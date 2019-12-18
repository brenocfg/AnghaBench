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
struct mon_private {int /*<<< orphan*/ * path; scalar_t__ read_index; scalar_t__ write_index; int /*<<< orphan*/  msglim_count; int /*<<< orphan*/  read_ready; int /*<<< orphan*/  iucv_connected; int /*<<< orphan*/  iucv_severed; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mon_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iucv_path_free (int /*<<< orphan*/ *) ; 
 int iucv_path_sever (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 int /*<<< orphan*/  user_data_sever ; 

__attribute__((used)) static int monreader_freeze(struct device *dev)
{
	struct mon_private *monpriv = dev_get_drvdata(dev);
	int rc;

	if (!monpriv)
		return 0;
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
	monpriv->path = NULL;
	return 0;
}