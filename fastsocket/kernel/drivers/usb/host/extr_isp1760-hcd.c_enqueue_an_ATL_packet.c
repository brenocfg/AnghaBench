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
struct usb_hcd {scalar_t__ regs; } ;
struct ptd {int dummy; } ;
struct isp1760_qtd {int /*<<< orphan*/  urb; int /*<<< orphan*/  length; } ;
struct isp1760_qh {int dummy; } ;
struct isp1760_hcd {int dummy; } ;

/* Variables and functions */
 int ATL_BUFFER ; 
 int ATL_REGS_OFFSET ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ HC_ATL_IRQ_MASK_OR_REG ; 
 scalar_t__ HC_ATL_PTD_SKIPMAP_REG ; 
 scalar_t__ HC_BUFFER_STATUS_REG ; 
 int __ffs (int) ; 
 int alloc_mem (struct isp1760_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enqueue_one_atl_qtd (int,int,struct isp1760_hcd*,struct isp1760_qh*,int /*<<< orphan*/ ,int,struct isp1760_qtd*) ; 
 struct isp1760_hcd* hcd_to_priv (struct usb_hcd*) ; 
 int isp1760_readl (scalar_t__) ; 
 int /*<<< orphan*/  isp1760_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  ndelay (int) ; 

__attribute__((used)) static void enqueue_an_ATL_packet(struct usb_hcd *hcd, struct isp1760_qh *qh,
				  struct isp1760_qtd *qtd)
{
	struct isp1760_hcd *priv = hcd_to_priv(hcd);
	u32 skip_map, or_map;
	u32 queue_entry;
	u32 slot;
	u32 atl_regs, payload;
	u32 buffstatus;

	/*
	 * When this function is called from the interrupt handler to enqueue
	 * a follow-up packet, the SKIP register gets written and read back
	 * almost immediately. With ISP1761, this register requires a delay of
	 * 195ns between a write and subsequent read (see section 15.1.1.3).
	 */
	ndelay(195);
	skip_map = isp1760_readl(hcd->regs + HC_ATL_PTD_SKIPMAP_REG);

	BUG_ON(!skip_map);
	slot = __ffs(skip_map);
	queue_entry = 1 << slot;

	atl_regs = ATL_REGS_OFFSET + slot * sizeof(struct ptd);

	payload = alloc_mem(priv, qtd->length);

	enqueue_one_atl_qtd(atl_regs, payload, priv, qh, qtd->urb, slot, qtd);

	or_map = isp1760_readl(hcd->regs + HC_ATL_IRQ_MASK_OR_REG);
	or_map |= queue_entry;
	isp1760_writel(or_map, hcd->regs + HC_ATL_IRQ_MASK_OR_REG);

	skip_map &= ~queue_entry;
	isp1760_writel(skip_map, hcd->regs + HC_ATL_PTD_SKIPMAP_REG);

	buffstatus = isp1760_readl(hcd->regs + HC_BUFFER_STATUS_REG);
	buffstatus |= ATL_BUFFER;
	isp1760_writel(buffstatus, hcd->regs + HC_BUFFER_STATUS_REG);
}