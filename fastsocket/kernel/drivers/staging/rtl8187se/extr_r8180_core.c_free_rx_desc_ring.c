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
struct r8180_priv {int rxringcount; int /*<<< orphan*/  rxbuffersize; int /*<<< orphan*/  rxbuffer; int /*<<< orphan*/  rxringdma; int /*<<< orphan*/  rxring; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_free (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void free_rx_desc_ring(struct net_device *dev)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	struct pci_dev *pdev = priv->pdev;
	int count = priv->rxringcount;

	pci_free_consistent(pdev, sizeof(u32)*8*count+256,
			    priv->rxring, priv->rxringdma);

	buffer_free(dev,&(priv->rxbuffer),priv->rxbuffersize,0);
}