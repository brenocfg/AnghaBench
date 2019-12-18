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
struct page {int dummy; } ;
struct ipath_portdata {int port_port; struct ipath_devdata* port_dd; } ;
struct ipath_devdata {int ipath_rcvtidcnt; int /*<<< orphan*/ * ipath_physshadow; int /*<<< orphan*/  pcidev; struct page** ipath_pageshadow; } ;
struct TYPE_2__ {scalar_t__ sps_pageunlocks; scalar_t__ sps_pagelocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  ipath_release_user_pages_on_close (struct page**,int) ; 
 TYPE_1__ ipath_stats ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unlock_expected_tids(struct ipath_portdata *pd)
{
	struct ipath_devdata *dd = pd->port_dd;
	int port_tidbase = pd->port_port * dd->ipath_rcvtidcnt;
	int i, cnt = 0, maxtid = port_tidbase + dd->ipath_rcvtidcnt;

	ipath_cdbg(VERBOSE, "Port %u unlocking any locked expTID pages\n",
		   pd->port_port);
	for (i = port_tidbase; i < maxtid; i++) {
		struct page *ps = dd->ipath_pageshadow[i];

		if (!ps)
			continue;

		dd->ipath_pageshadow[i] = NULL;
		pci_unmap_page(dd->pcidev, dd->ipath_physshadow[i],
			PAGE_SIZE, PCI_DMA_FROMDEVICE);
		ipath_release_user_pages_on_close(&ps, 1);
		cnt++;
		ipath_stats.sps_pageunlocks++;
	}
	if (cnt)
		ipath_cdbg(VERBOSE, "Port %u locked %u expTID entries\n",
			   pd->port_port, cnt);

	if (ipath_stats.sps_pagelocks || ipath_stats.sps_pageunlocks)
		ipath_cdbg(VERBOSE, "%llu pages locked, %llu unlocked\n",
			   (unsigned long long) ipath_stats.sps_pagelocks,
			   (unsigned long long)
			   ipath_stats.sps_pageunlocks);
}