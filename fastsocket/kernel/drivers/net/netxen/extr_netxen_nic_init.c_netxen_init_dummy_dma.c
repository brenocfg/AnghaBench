#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ phys_addr; int /*<<< orphan*/ * addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {TYPE_1__ dummy_dma; TYPE_3__* pdev; TYPE_2__ ahw; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_HOST_DUMMY_BUF_ADDR_HI ; 
 int /*<<< orphan*/  CRB_HOST_DUMMY_BUF_ADDR_LO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NETXEN_HOST_DUMMY_DMA_SIZE ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*) ; 

int netxen_init_dummy_dma(struct netxen_adapter *adapter)
{
	u64 addr;
	u32 hi, lo;

	if (!NX_IS_REVISION_P2(adapter->ahw.revision_id))
		return 0;

	adapter->dummy_dma.addr = pci_alloc_consistent(adapter->pdev,
				 NETXEN_HOST_DUMMY_DMA_SIZE,
				 &adapter->dummy_dma.phys_addr);
	if (adapter->dummy_dma.addr == NULL) {
		dev_err(&adapter->pdev->dev,
			"ERROR: Could not allocate dummy DMA memory\n");
		return -ENOMEM;
	}

	addr = (uint64_t) adapter->dummy_dma.phys_addr;
	hi = (addr >> 32) & 0xffffffff;
	lo = addr & 0xffffffff;

	NXWR32(adapter, CRB_HOST_DUMMY_BUF_ADDR_HI, hi);
	NXWR32(adapter, CRB_HOST_DUMMY_BUF_ADDR_LO, lo);

	return 0;
}