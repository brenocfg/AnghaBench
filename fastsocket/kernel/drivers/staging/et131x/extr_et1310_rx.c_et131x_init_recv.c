#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct et131x_adapter {TYPE_1__* pdev; int /*<<< orphan*/  RxRing; } ;
struct TYPE_9__ {int /*<<< orphan*/  list_node; } ;
struct TYPE_8__ {scalar_t__ NumRfd; int /*<<< orphan*/  RecvLookaside; int /*<<< orphan*/  nReadyRecv; int /*<<< orphan*/  RecvList; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ RX_RING_t ;
typedef  TYPE_3__* PMP_RFD ;
typedef  TYPE_3__ MP_RFD ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 scalar_t__ NIC_MIN_NUM_RFD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int et131x_rfd_resources_alloc (struct et131x_adapter*,TYPE_3__*) ; 
 scalar_t__ kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int et131x_init_recv(struct et131x_adapter *adapter)
{
	int status = -ENOMEM;
	PMP_RFD pMpRfd = NULL;
	uint32_t RfdCount;
	uint32_t TotalNumRfd = 0;
	RX_RING_t *rx_ring = NULL;

	/* Setup some convenience pointers */
	rx_ring = (RX_RING_t *) &adapter->RxRing;

	/* Setup each RFD */
	for (RfdCount = 0; RfdCount < rx_ring->NumRfd; RfdCount++) {
		pMpRfd = (MP_RFD *) kmem_cache_alloc(rx_ring->RecvLookaside,
						     GFP_ATOMIC | GFP_DMA);

		if (!pMpRfd) {
			dev_err(&adapter->pdev->dev,
				  "Couldn't alloc RFD out of kmem_cache\n");
			status = -ENOMEM;
			continue;
		}

		status = et131x_rfd_resources_alloc(adapter, pMpRfd);
		if (status != 0) {
			dev_err(&adapter->pdev->dev,
				  "Couldn't alloc packet for RFD\n");
			kmem_cache_free(rx_ring->RecvLookaside, pMpRfd);
			continue;
		}

		/* Add this RFD to the RecvList */
		list_add_tail(&pMpRfd->list_node, &rx_ring->RecvList);

		/* Increment both the available RFD's, and the total RFD's. */
		rx_ring->nReadyRecv++;
		TotalNumRfd++;
	}

	if (TotalNumRfd > NIC_MIN_NUM_RFD)
		status = 0;

	rx_ring->NumRfd = TotalNumRfd;

	if (status != 0) {
		kmem_cache_free(rx_ring->RecvLookaside, pMpRfd);
		dev_err(&adapter->pdev->dev,
			  "Allocation problems in et131x_init_recv\n");
	}
	return status;
}