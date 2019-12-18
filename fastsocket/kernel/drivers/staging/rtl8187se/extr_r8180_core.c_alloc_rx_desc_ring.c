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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct r8180_priv {int* rxring; int rxringdma; int /*<<< orphan*/  rxbufferhead; int /*<<< orphan*/  rxbuffer; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMESGE (char*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int buffer_add (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_alloc_consistent (struct pci_dev*,int,int*) ; 
 int pci_map_single (struct pci_dev*,void*,int,int /*<<< orphan*/ ) ; 

short alloc_rx_desc_ring(struct net_device *dev, u16 bufsize, int count)
{
	int i;
	u32 *desc;
	u32 *tmp;
	dma_addr_t dma_desc,dma_tmp;
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	struct pci_dev *pdev=priv->pdev;
	void *buf;
	u8 rx_desc_size;

	rx_desc_size = 8; // 4*8 = 32 bytes

	if((bufsize & 0xfff) != bufsize){
		DMESGE ("RX buffer allocation too large");
		return -1;
	}

	desc = (u32*)pci_alloc_consistent(pdev,sizeof(u32)*rx_desc_size*count+256,
					  &dma_desc);

	if (dma_desc & 0xff)
		/*
		 * descriptor's buffer must be 256 byte aligned
		 * should never happen since we specify the DMA mask
		 */
		WARN(1, "DMA buffer is not aligned\n");

	priv->rxring=desc;
	priv->rxringdma=dma_desc;
	tmp=desc;

	for (i = 0; i < count; i++) {
		if ((buf= kmalloc(bufsize * sizeof(u8),GFP_ATOMIC)) == NULL){
			DMESGE("Failed to kmalloc RX buffer");
			return -1;
		}

		dma_tmp = pci_map_single(pdev,buf,bufsize * sizeof(u8),
					 PCI_DMA_FROMDEVICE);

		if(-1 == buffer_add(&(priv->rxbuffer), buf,dma_tmp,
			   &(priv->rxbufferhead))){
			   DMESGE("Unable to allocate mem RX buf");
			   return -1;
		}
		*tmp = 0; //zero pads the header of the descriptor
		*tmp = *tmp |( bufsize&0xfff);
		*(tmp+2) = (u32)dma_tmp;
		*tmp = *tmp |(1<<31); // descriptor void, owned by the NIC

		tmp=tmp+rx_desc_size;
	}

	*(tmp-rx_desc_size) = *(tmp-rx_desc_size) | (1<<30); // this is the last descriptor

	return 0;
}