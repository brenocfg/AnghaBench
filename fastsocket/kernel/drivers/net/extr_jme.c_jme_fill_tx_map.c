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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {void* bufaddrl; void* bufaddrh; int /*<<< orphan*/  datalen; int /*<<< orphan*/  flags; } ;
struct txdesc {TYPE_1__ desc2; scalar_t__* dw; } ;
struct pci_dev {int dummy; } ;
struct page {int dummy; } ;
struct jme_buffer_info {int /*<<< orphan*/  len; scalar_t__ mapping; } ;
typedef  scalar_t__ dma_addr_t ;
typedef  int __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  TXFLAG_64BIT ; 
 int /*<<< orphan*/  TXFLAG_OWN ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_map_page (struct pci_dev*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
jme_fill_tx_map(struct pci_dev *pdev,
		struct txdesc *txdesc,
		struct jme_buffer_info *txbi,
		struct page *page,
		u32 page_offset,
		u32 len,
		u8 hidma)
{
	dma_addr_t dmaaddr;

	dmaaddr = pci_map_page(pdev,
				page,
				page_offset,
				len,
				PCI_DMA_TODEVICE);

	pci_dma_sync_single_for_device(pdev,
				       dmaaddr,
				       len,
				       PCI_DMA_TODEVICE);

	txdesc->dw[0] = 0;
	txdesc->dw[1] = 0;
	txdesc->desc2.flags	= TXFLAG_OWN;
	txdesc->desc2.flags	|= (hidma) ? TXFLAG_64BIT : 0;
	txdesc->desc2.datalen	= cpu_to_le16(len);
	txdesc->desc2.bufaddrh	= cpu_to_le32((__u64)dmaaddr >> 32);
	txdesc->desc2.bufaddrl	= cpu_to_le32(
					(__u64)dmaaddr & 0xFFFFFFFFUL);

	txbi->mapping = dmaaddr;
	txbi->len = len;
}