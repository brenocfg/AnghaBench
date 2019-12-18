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
typedef  int u32 ;
struct r8180_priv {int txmapringdma; int* txmapring; int txbkpringdma; int* txbkpring; int txbepringdma; int* txbepring; int txvipringdma; int* txvipring; int txvopringdma; int* txvopring; int txhpringdma; int* txhpring; int txbeaconringdma; int* txbeaconring; int /*<<< orphan*/  txbeaconbufs; int /*<<< orphan*/  txhpbufs; int /*<<< orphan*/  txvopbufs; int /*<<< orphan*/  txvipbufs; int /*<<< orphan*/  txbepbufs; int /*<<< orphan*/  txbkpbufs; int /*<<< orphan*/  txmapbufs; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMESGE (char*) ; 
 short ENOMEM ; 
#define  TX_BEACON_RING_ADDR 134 
#define  TX_BEPRIORITY_RING_ADDR 133 
#define  TX_BKPRIORITY_RING_ADDR 132 
#define  TX_HIGHPRIORITY_RING_ADDR 131 
#define  TX_MANAGEPRIORITY_RING_ADDR 130 
#define  TX_VIPRIORITY_RING_ADDR 129 
#define  TX_VOPRIORITY_RING_ADDR 128 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int buffer_add (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 scalar_t__ pci_alloc_consistent (struct pci_dev*,int,int*) ; 

short alloc_tx_desc_ring(struct net_device *dev, int bufsize, int count,
			 int addr)
{
	int i;
	u32 *desc;
	u32 *tmp;
	dma_addr_t dma_desc, dma_tmp;
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	struct pci_dev *pdev = priv->pdev;
	void *buf;

	if((bufsize & 0xfff) != bufsize) {
		DMESGE ("TX buffer allocation too large");
		return 0;
	}
	desc = (u32*)pci_alloc_consistent(pdev,
					  sizeof(u32)*8*count+256, &dma_desc);
	if (desc == NULL)
		return -1;

	if (dma_desc & 0xff)
		/*
		 * descriptor's buffer must be 256 byte aligned
		 * we shouldn't be here, since we set DMA mask !
		 */
		WARN(1, "DMA buffer is not aligned\n");

	tmp = desc;

	for (i = 0; i < count; i++) {
		buf = (void *)pci_alloc_consistent(pdev, bufsize, &dma_tmp);
		if (buf == NULL)
			return -ENOMEM;

		switch(addr) {
		case TX_MANAGEPRIORITY_RING_ADDR:
			if(-1 == buffer_add(&(priv->txmapbufs),buf,dma_tmp,NULL)){
				DMESGE("Unable to allocate mem for buffer NP");
				return -ENOMEM;
			}
			break;
		case TX_BKPRIORITY_RING_ADDR:
			if(-1 == buffer_add(&(priv->txbkpbufs),buf,dma_tmp,NULL)){
				DMESGE("Unable to allocate mem for buffer LP");
				return -ENOMEM;
			}
			break;
		case TX_BEPRIORITY_RING_ADDR:
			if(-1 == buffer_add(&(priv->txbepbufs),buf,dma_tmp,NULL)){
				DMESGE("Unable to allocate mem for buffer NP");
				return -ENOMEM;
			}
			break;
		case TX_VIPRIORITY_RING_ADDR:
			if(-1 == buffer_add(&(priv->txvipbufs),buf,dma_tmp,NULL)){
				DMESGE("Unable to allocate mem for buffer LP");
				return -ENOMEM;
			}
			break;
		case TX_VOPRIORITY_RING_ADDR:
			if(-1 == buffer_add(&(priv->txvopbufs),buf,dma_tmp,NULL)){
				DMESGE("Unable to allocate mem for buffer NP");
				return -ENOMEM;
			}
			break;
		case TX_HIGHPRIORITY_RING_ADDR:
			if(-1 == buffer_add(&(priv->txhpbufs),buf,dma_tmp,NULL)){
				DMESGE("Unable to allocate mem for buffer HP");
				return -ENOMEM;
			}
			break;
		case TX_BEACON_RING_ADDR:
		        if(-1 == buffer_add(&(priv->txbeaconbufs),buf,dma_tmp,NULL)){
			DMESGE("Unable to allocate mem for buffer BP");
				return -ENOMEM;
			}
			break;
		}
		*tmp = *tmp &~ (1<<31); // descriptor empty, owned by the drv
		*(tmp+2) = (u32)dma_tmp;
		*(tmp+3) = bufsize;

		if(i+1<count)
			*(tmp+4) = (u32)dma_desc+((i+1)*8*4);
		else
			*(tmp+4) = (u32)dma_desc;

		tmp=tmp+8;
	}

	switch(addr) {
	case TX_MANAGEPRIORITY_RING_ADDR:
		priv->txmapringdma=dma_desc;
		priv->txmapring=desc;
		break;
	case TX_BKPRIORITY_RING_ADDR:
		priv->txbkpringdma=dma_desc;
		priv->txbkpring=desc;
		break;
	case TX_BEPRIORITY_RING_ADDR:
		priv->txbepringdma=dma_desc;
		priv->txbepring=desc;
		break;
	case TX_VIPRIORITY_RING_ADDR:
		priv->txvipringdma=dma_desc;
		priv->txvipring=desc;
		break;
	case TX_VOPRIORITY_RING_ADDR:
		priv->txvopringdma=dma_desc;
		priv->txvopring=desc;
		break;
	case TX_HIGHPRIORITY_RING_ADDR:
		priv->txhpringdma=dma_desc;
		priv->txhpring=desc;
		break;
	case TX_BEACON_RING_ADDR:
		priv->txbeaconringdma=dma_desc;
		priv->txbeaconring=desc;
		break;

	}

	return 0;
}