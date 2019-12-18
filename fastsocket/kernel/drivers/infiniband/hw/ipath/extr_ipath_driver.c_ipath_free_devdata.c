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
struct pci_dev {int dummy; } ;
struct ipath_devdata {int ipath_unit; int /*<<< orphan*/  ipath_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ipath_devs_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unit_table ; 
 int /*<<< orphan*/  vfree (struct ipath_devdata*) ; 

__attribute__((used)) static void ipath_free_devdata(struct pci_dev *pdev,
			       struct ipath_devdata *dd)
{
	unsigned long flags;

	pci_set_drvdata(pdev, NULL);

	if (dd->ipath_unit != -1) {
		spin_lock_irqsave(&ipath_devs_lock, flags);
		idr_remove(&unit_table, dd->ipath_unit);
		list_del(&dd->ipath_list);
		spin_unlock_irqrestore(&ipath_devs_lock, flags);
	}
	vfree(dd);
}