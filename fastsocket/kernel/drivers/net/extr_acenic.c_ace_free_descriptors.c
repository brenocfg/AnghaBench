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
typedef  int /*<<< orphan*/  u32 ;
struct tx_desc {int dummy; } ;
struct rx_desc {int dummy; } ;
struct net_device {int dummy; } ;
struct event {int dummy; } ;
struct ace_private {void* rx_std_ring; void* evt_ring; void* tx_ring; int /*<<< orphan*/ * tx_csm; int /*<<< orphan*/  tx_csm_dma; int /*<<< orphan*/  pdev; int /*<<< orphan*/ * rx_ret_prd; int /*<<< orphan*/  rx_ret_prd_dma; int /*<<< orphan*/ * evt_prd; int /*<<< orphan*/  evt_prd_dma; int /*<<< orphan*/  tx_ring_dma; int /*<<< orphan*/  evt_ring_dma; int /*<<< orphan*/ * rx_return_ring; int /*<<< orphan*/ * rx_mini_ring; int /*<<< orphan*/ * rx_jumbo_ring; int /*<<< orphan*/  rx_ring_base_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_IS_TIGON_I (struct ace_private*) ; 
 int EVT_RING_ENTRIES ; 
 int MAX_TX_RING_ENTRIES ; 
 int RX_JUMBO_RING_ENTRIES ; 
 int RX_MINI_RING_ENTRIES ; 
 int RX_RETURN_RING_ENTRIES ; 
 int RX_STD_RING_ENTRIES ; 
 struct ace_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ace_free_descriptors(struct net_device *dev)
{
	struct ace_private *ap = netdev_priv(dev);
	int size;

	if (ap->rx_std_ring != NULL) {
		size = (sizeof(struct rx_desc) *
			(RX_STD_RING_ENTRIES +
			 RX_JUMBO_RING_ENTRIES +
			 RX_MINI_RING_ENTRIES +
			 RX_RETURN_RING_ENTRIES));
		pci_free_consistent(ap->pdev, size, ap->rx_std_ring,
				    ap->rx_ring_base_dma);
		ap->rx_std_ring = NULL;
		ap->rx_jumbo_ring = NULL;
		ap->rx_mini_ring = NULL;
		ap->rx_return_ring = NULL;
	}
	if (ap->evt_ring != NULL) {
		size = (sizeof(struct event) * EVT_RING_ENTRIES);
		pci_free_consistent(ap->pdev, size, ap->evt_ring,
				    ap->evt_ring_dma);
		ap->evt_ring = NULL;
	}
	if (ap->tx_ring != NULL && !ACE_IS_TIGON_I(ap)) {
		size = (sizeof(struct tx_desc) * MAX_TX_RING_ENTRIES);
		pci_free_consistent(ap->pdev, size, ap->tx_ring,
				    ap->tx_ring_dma);
	}
	ap->tx_ring = NULL;

	if (ap->evt_prd != NULL) {
		pci_free_consistent(ap->pdev, sizeof(u32),
				    (void *)ap->evt_prd, ap->evt_prd_dma);
		ap->evt_prd = NULL;
	}
	if (ap->rx_ret_prd != NULL) {
		pci_free_consistent(ap->pdev, sizeof(u32),
				    (void *)ap->rx_ret_prd,
				    ap->rx_ret_prd_dma);
		ap->rx_ret_prd = NULL;
	}
	if (ap->tx_csm != NULL) {
		pci_free_consistent(ap->pdev, sizeof(u32),
				    (void *)ap->tx_csm, ap->tx_csm_dma);
		ap->tx_csm = NULL;
	}
}