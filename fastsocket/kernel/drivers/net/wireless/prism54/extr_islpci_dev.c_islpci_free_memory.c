#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct islpci_membuf {int /*<<< orphan*/ * mem; scalar_t__ size; scalar_t__ pci_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  acl; int /*<<< orphan*/ ** data_low_rx; scalar_t__* pci_map_rx_address; int /*<<< orphan*/  pdev; struct islpci_membuf* mgmt_rx; int /*<<< orphan*/ * control_block; scalar_t__ device_psm_buffer; scalar_t__ device_host_address; int /*<<< orphan*/ * driver_mem_address; int /*<<< orphan*/ * device_base; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_MEM_BLOCK ; 
 int ISL38XX_CB_MGMT_QSIZE ; 
 int ISL38XX_CB_RX_QSIZE ; 
 scalar_t__ MAX_FRAGMENT_SIZE_RX ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgt_clean (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prism54_acl_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prism54_wpa_bss_ie_clean (TYPE_1__*) ; 

int
islpci_free_memory(islpci_private *priv)
{
	int counter;

	if (priv->device_base)
		iounmap(priv->device_base);
	priv->device_base = NULL;

	/* free consistent DMA area... */
	if (priv->driver_mem_address)
		pci_free_consistent(priv->pdev, HOST_MEM_BLOCK,
				    priv->driver_mem_address,
				    priv->device_host_address);

	/* clear some dangling pointers */
	priv->driver_mem_address = NULL;
	priv->device_host_address = 0;
	priv->device_psm_buffer = 0;
	priv->control_block = NULL;

        /* clean up mgmt rx buffers */
        for (counter = 0; counter < ISL38XX_CB_MGMT_QSIZE; counter++) {
		struct islpci_membuf *buf = &priv->mgmt_rx[counter];
		if (buf->pci_addr)
			pci_unmap_single(priv->pdev, buf->pci_addr,
					 buf->size, PCI_DMA_FROMDEVICE);
		buf->pci_addr = 0;
		kfree(buf->mem);
		buf->size = 0;
		buf->mem = NULL;
        }

	/* clean up data rx buffers */
	for (counter = 0; counter < ISL38XX_CB_RX_QSIZE; counter++) {
		if (priv->pci_map_rx_address[counter])
			pci_unmap_single(priv->pdev,
					 priv->pci_map_rx_address[counter],
					 MAX_FRAGMENT_SIZE_RX + 2,
					 PCI_DMA_FROMDEVICE);
		priv->pci_map_rx_address[counter] = 0;

		if (priv->data_low_rx[counter])
			dev_kfree_skb(priv->data_low_rx[counter]);
		priv->data_low_rx[counter] = NULL;
	}

	/* Free the acces control list and the WPA list */
	prism54_acl_clean(&priv->acl);
	prism54_wpa_bss_ie_clean(priv);
	mgt_clean(priv);

	return 0;
}