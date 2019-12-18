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
struct r8180_priv {struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct buffer {struct buffer* buf; int /*<<< orphan*/  dma; struct buffer* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct buffer*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,struct buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void buffer_free(struct net_device *dev,struct buffer **buffer,int len,short
consistent)
{

	struct buffer *tmp,*next;
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	struct pci_dev *pdev=priv->pdev;

	if (!*buffer)
		return;

	tmp = *buffer;

	do{
		next=tmp->next;
		if(consistent){
			pci_free_consistent(pdev,len,
				    tmp->buf,tmp->dma);
		}else{
			pci_unmap_single(pdev, tmp->dma,
			len,PCI_DMA_FROMDEVICE);
			kfree(tmp->buf);
		}
		kfree(tmp);
		tmp = next;
	}
	while(next != *buffer);

	*buffer=NULL;
}