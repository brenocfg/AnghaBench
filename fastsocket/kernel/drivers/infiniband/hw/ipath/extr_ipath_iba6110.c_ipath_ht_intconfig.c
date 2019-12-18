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
struct ipath_devdata {scalar_t__ ipath_intconfig; TYPE_1__* ipath_kregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_interruptconfig; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ipath_ht_intconfig(struct ipath_devdata *dd)
{
	int ret;

	if (dd->ipath_intconfig) {
		ipath_write_kreg(dd, dd->ipath_kregs->kr_interruptconfig,
				 dd->ipath_intconfig);	/* interrupt address */
		ret = 0;
	} else {
		ipath_dev_err(dd, "No interrupts enabled, couldn't setup "
			      "interrupt address\n");
		ret = -EINVAL;
	}

	return ret;
}