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
struct ipath_devdata {int /*<<< orphan*/  diag_dev; int /*<<< orphan*/  diag_cdev; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diagpkt_cdev ; 
 int /*<<< orphan*/  diagpkt_count ; 
 int /*<<< orphan*/  diagpkt_dev ; 
 int /*<<< orphan*/  ipath_cdev_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ipath_diag_remove(struct ipath_devdata *dd)
{
	if (atomic_dec_and_test(&diagpkt_count))
		ipath_cdev_cleanup(&diagpkt_cdev, &diagpkt_dev);

	ipath_cdev_cleanup(&dd->diag_cdev, &dd->diag_dev);
}