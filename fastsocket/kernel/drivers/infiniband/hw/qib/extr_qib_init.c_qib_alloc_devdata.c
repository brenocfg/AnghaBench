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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ibdev; } ;
struct qib_devdata {TYPE_1__ verbs_dev; int /*<<< orphan*/  list; int /*<<< orphan*/  unit; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BITS_TO_LONGS (scalar_t__) ; 
 int ENOMEM ; 
 struct qib_devdata* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ib_alloc_device (int) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int idr_get_new (int /*<<< orphan*/ *,struct qib_devdata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ num_online_cpus () ; 
 scalar_t__ qib_cpulist ; 
 scalar_t__ qib_cpulist_count ; 
 int /*<<< orphan*/  qib_dev_list ; 
 int /*<<< orphan*/  qib_devs_lock ; 
 int /*<<< orphan*/  qib_early_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  qib_unit_table ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct qib_devdata *qib_alloc_devdata(struct pci_dev *pdev, size_t extra)
{
	unsigned long flags;
	struct qib_devdata *dd;
	int ret;

	if (!idr_pre_get(&qib_unit_table, GFP_KERNEL)) {
		dd = ERR_PTR(-ENOMEM);
		goto bail;
	}

	dd = (struct qib_devdata *) ib_alloc_device(sizeof(*dd) + extra);
	if (!dd) {
		dd = ERR_PTR(-ENOMEM);
		goto bail;
	}

	spin_lock_irqsave(&qib_devs_lock, flags);
	ret = idr_get_new(&qib_unit_table, dd, &dd->unit);
	if (ret >= 0)
		list_add(&dd->list, &qib_dev_list);
	spin_unlock_irqrestore(&qib_devs_lock, flags);

	if (ret < 0) {
		qib_early_err(&pdev->dev,
			      "Could not allocate unit ID: error %d\n", -ret);
		ib_dealloc_device(&dd->verbs_dev.ibdev);
		dd = ERR_PTR(ret);
		goto bail;
	}

	if (!qib_cpulist_count) {
		u32 count = num_online_cpus();
		qib_cpulist = kzalloc(BITS_TO_LONGS(count) *
				      sizeof(long), GFP_KERNEL);
		if (qib_cpulist)
			qib_cpulist_count = count;
		else
			qib_early_err(&pdev->dev,
				"Could not alloc cpulist info, cpu affinity might be wrong\n");
	}

bail:
	return dd;
}