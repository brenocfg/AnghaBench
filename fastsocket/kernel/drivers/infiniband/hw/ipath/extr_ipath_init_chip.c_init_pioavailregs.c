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
typedef  int /*<<< orphan*/  u64 ;
struct ipath_devdata {int ipath_pioavregs; char* ipath_freezemsg; int ipath_freezelen; int /*<<< orphan*/ * ipath_statusp; int /*<<< orphan*/  _ipath_status; scalar_t__ ipath_pioavailregs_dma; int /*<<< orphan*/  ipath_pioavailregs_phys; TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int L1_CACHE_BYTES ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*) ; 

__attribute__((used)) static int init_pioavailregs(struct ipath_devdata *dd)
{
	int ret;

	dd->ipath_pioavailregs_dma = dma_alloc_coherent(
		&dd->pcidev->dev, PAGE_SIZE, &dd->ipath_pioavailregs_phys,
		GFP_KERNEL);
	if (!dd->ipath_pioavailregs_dma) {
		ipath_dev_err(dd, "failed to allocate PIOavail reg area "
			      "in memory\n");
		ret = -ENOMEM;
		goto done;
	}

	/*
	 * we really want L2 cache aligned, but for current CPUs of
	 * interest, they are the same.
	 */
	dd->ipath_statusp = (u64 *)
		((char *)dd->ipath_pioavailregs_dma +
		 ((2 * L1_CACHE_BYTES +
		   dd->ipath_pioavregs * sizeof(u64)) & ~L1_CACHE_BYTES));
	/* copy the current value now that it's really allocated */
	*dd->ipath_statusp = dd->_ipath_status;
	/*
	 * setup buffer to hold freeze msg, accessible to apps,
	 * following statusp
	 */
	dd->ipath_freezemsg = (char *)&dd->ipath_statusp[1];
	/* and its length */
	dd->ipath_freezelen = L1_CACHE_BYTES - sizeof(dd->ipath_statusp[0]);

	ret = 0;

done:
	return ret;
}