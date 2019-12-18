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
struct ipath_devdata {int ipath_flags; TYPE_1__* pcidev; int /*<<< orphan*/  ipath_kregbase; } ;
struct inode {int dummy; } ;
struct file {struct ipath_devdata* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int IPATH_DIAG_MINOR_BASE ; 
 int IPATH_PRESENT ; 
 scalar_t__ diag_set_link ; 
 int iminor (struct inode*) ; 
 int ipath_diag_inuse ; 
 int /*<<< orphan*/  ipath_expose_reset (int /*<<< orphan*/ *) ; 
 struct ipath_devdata* ipath_lookup (int) ; 
 int /*<<< orphan*/  ipath_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipath_diag_open(struct inode *in, struct file *fp)
{
	int unit = iminor(in) - IPATH_DIAG_MINOR_BASE;
	struct ipath_devdata *dd;
	int ret;

	mutex_lock(&ipath_mutex);

	if (ipath_diag_inuse) {
		ret = -EBUSY;
		goto bail;
	}

	dd = ipath_lookup(unit);

	if (dd == NULL || !(dd->ipath_flags & IPATH_PRESENT) ||
	    !dd->ipath_kregbase) {
		ret = -ENODEV;
		goto bail;
	}

	fp->private_data = dd;
	ipath_diag_inuse = -2;
	diag_set_link = 0;
	ret = 0;

	/* Only expose a way to reset the device if we
	   make it into diag mode. */
	ipath_expose_reset(&dd->pcidev->dev);

bail:
	mutex_unlock(&ipath_mutex);

	return ret;
}