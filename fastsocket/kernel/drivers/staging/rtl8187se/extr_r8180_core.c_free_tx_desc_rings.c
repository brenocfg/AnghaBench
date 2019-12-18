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
struct r8180_priv {int txringcount; int txbeaconcount; int /*<<< orphan*/  txbuffsize; int /*<<< orphan*/  txbeaconbufs; int /*<<< orphan*/  txbeaconringdma; int /*<<< orphan*/  txbeaconring; int /*<<< orphan*/  txhpbufs; int /*<<< orphan*/  txhpringdma; int /*<<< orphan*/  txhpring; int /*<<< orphan*/  txvopbufs; int /*<<< orphan*/  txvopringdma; int /*<<< orphan*/  txvopring; int /*<<< orphan*/  txvipbufs; int /*<<< orphan*/  txvipringdma; int /*<<< orphan*/  txvipring; int /*<<< orphan*/  txbepbufs; int /*<<< orphan*/  txbepringdma; int /*<<< orphan*/  txbepring; int /*<<< orphan*/  txbkpbufs; int /*<<< orphan*/  txbkpringdma; int /*<<< orphan*/  txbkpring; int /*<<< orphan*/  txmapbufs; int /*<<< orphan*/  txmapringdma; int /*<<< orphan*/  txmapring; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_free (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void free_tx_desc_rings(struct net_device *dev)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	struct pci_dev *pdev=priv->pdev;
	int count = priv->txringcount;

	pci_free_consistent(pdev, sizeof(u32)*8*count+256,
			    priv->txmapring, priv->txmapringdma);
	buffer_free(dev,&(priv->txmapbufs),priv->txbuffsize,1);

	pci_free_consistent(pdev, sizeof(u32)*8*count+256,
			    priv->txbkpring, priv->txbkpringdma);
	buffer_free(dev,&(priv->txbkpbufs),priv->txbuffsize,1);

	pci_free_consistent(pdev, sizeof(u32)*8*count+256,
			    priv->txbepring, priv->txbepringdma);
	buffer_free(dev,&(priv->txbepbufs),priv->txbuffsize,1);

	pci_free_consistent(pdev, sizeof(u32)*8*count+256,
			    priv->txvipring, priv->txvipringdma);
	buffer_free(dev,&(priv->txvipbufs),priv->txbuffsize,1);

	pci_free_consistent(pdev, sizeof(u32)*8*count+256,
			    priv->txvopring, priv->txvopringdma);
	buffer_free(dev,&(priv->txvopbufs),priv->txbuffsize,1);

	pci_free_consistent(pdev, sizeof(u32)*8*count+256,
			    priv->txhpring, priv->txhpringdma);
	buffer_free(dev,&(priv->txhpbufs),priv->txbuffsize,1);

	count = priv->txbeaconcount;
	pci_free_consistent(pdev, sizeof(u32)*8*count+256,
			    priv->txbeaconring, priv->txbeaconringdma);
	buffer_free(dev,&(priv->txbeaconbufs),priv->txbuffsize,1);
}