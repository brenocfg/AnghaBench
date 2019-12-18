#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct usb_hcd {int dummy; } ;
struct ehci_qh_hw {int /*<<< orphan*/  hw_alt_next; int /*<<< orphan*/  hw_qtd_next; void* hw_token; void* hw_info1; int /*<<< orphan*/  hw_next; } ;
struct TYPE_10__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct ehci_hcd {int need_io_watchdog; int periodic_size; int i_thresh; int next_uframe; int clock_frame; int has_ppcd; int has_lpm; int command; TYPE_4__* async; int /*<<< orphan*/ * reclaim; TYPE_1__* caps; int /*<<< orphan*/  cached_sitd_list; int /*<<< orphan*/  cached_itd_list; TYPE_5__ iaa_watchdog; TYPE_5__ watchdog; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/ * qh; } ;
struct TYPE_9__ {TYPE_3__* dummy; int /*<<< orphan*/  qh_state; int /*<<< orphan*/  qh_dma; struct ehci_qh_hw* hw; TYPE_2__ qh_next; } ;
struct TYPE_8__ {int /*<<< orphan*/  qtd_dma; } ;
struct TYPE_6__ {int /*<<< orphan*/  hcc_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int CMD_PARK ; 
 int CMD_PPCEE ; 
 int DEFAULT_I_TDPS ; 
 int /*<<< orphan*/  EHCI_LIST_END (struct ehci_hcd*) ; 
 int EHCI_TUNE_FLS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HCC_CANPARK (int) ; 
 scalar_t__ HCC_ISOC_CACHE (int) ; 
 int HCC_ISOC_THRES (int) ; 
 scalar_t__ HCC_LPM (int) ; 
 scalar_t__ HCC_PER_PORT_CHANGE_EVENT (int) ; 
 scalar_t__ HCC_PGM_FRAMELISTLEN (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QH_HEAD ; 
 int /*<<< orphan*/  QH_NEXT (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QH_STATE_LINKED ; 
 int /*<<< orphan*/  QTD_NEXT (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QTD_STS_HALT ; 
 void* cpu_to_hc32 (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*,...) ; 
 int /*<<< orphan*/  ehci_iaa_watchdog ; 
 int ehci_mem_init (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_watchdog ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int hird ; 
 int /*<<< orphan*/  init_timer (TYPE_5__*) ; 
 int log2_irq_thresh ; 
 int min (int,unsigned int) ; 
 int park ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehci_init(struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	u32			temp;
	int			retval;
	u32			hcc_params;
	struct ehci_qh_hw	*hw;

	spin_lock_init(&ehci->lock);

	/*
	 * keep io watchdog by default, those good HCDs could turn off it later
	 */
	ehci->need_io_watchdog = 1;
	init_timer(&ehci->watchdog);
	ehci->watchdog.function = ehci_watchdog;
	ehci->watchdog.data = (unsigned long) ehci;

	init_timer(&ehci->iaa_watchdog);
	ehci->iaa_watchdog.function = ehci_iaa_watchdog;
	ehci->iaa_watchdog.data = (unsigned long) ehci;

	/*
	 * hw default: 1K periodic list heads, one per frame.
	 * periodic_size can shrink by USBCMD update if hcc_params allows.
	 */
	ehci->periodic_size = DEFAULT_I_TDPS;
	INIT_LIST_HEAD(&ehci->cached_itd_list);
	INIT_LIST_HEAD(&ehci->cached_sitd_list);
	if ((retval = ehci_mem_init(ehci, GFP_KERNEL)) < 0)
		return retval;

	/* controllers may cache some of the periodic schedule ... */
	hcc_params = ehci_readl(ehci, &ehci->caps->hcc_params);
	if (HCC_ISOC_CACHE(hcc_params))		// full frame cache
		ehci->i_thresh = 8;
	else					// N microframes cached
		ehci->i_thresh = 2 + HCC_ISOC_THRES(hcc_params);

	ehci->reclaim = NULL;
	ehci->next_uframe = -1;
	ehci->clock_frame = -1;

	/*
	 * dedicate a qh for the async ring head, since we couldn't unlink
	 * a 'real' qh without stopping the async schedule [4.8].  use it
	 * as the 'reclamation list head' too.
	 * its dummy is used in hw_alt_next of many tds, to prevent the qh
	 * from automatically advancing to the next td after short reads.
	 */
	ehci->async->qh_next.qh = NULL;
	hw = ehci->async->hw;
	hw->hw_next = QH_NEXT(ehci, ehci->async->qh_dma);
	hw->hw_info1 = cpu_to_hc32(ehci, QH_HEAD);
	hw->hw_token = cpu_to_hc32(ehci, QTD_STS_HALT);
	hw->hw_qtd_next = EHCI_LIST_END(ehci);
	ehci->async->qh_state = QH_STATE_LINKED;
	hw->hw_alt_next = QTD_NEXT(ehci, ehci->async->dummy->qtd_dma);

	/* clear interrupt enables, set irq latency */
	if (log2_irq_thresh < 0 || log2_irq_thresh > 6)
		log2_irq_thresh = 0;
	temp = 1 << (16 + log2_irq_thresh);
	if (HCC_PER_PORT_CHANGE_EVENT(hcc_params)) {
		ehci->has_ppcd = 1;
		ehci_dbg(ehci, "enable per-port change event\n");
		temp |= CMD_PPCEE;
	}
	if (HCC_CANPARK(hcc_params)) {
		/* HW default park == 3, on hardware that supports it (like
		 * NVidia and ALI silicon), maximizes throughput on the async
		 * schedule by avoiding QH fetches between transfers.
		 *
		 * With fast usb storage devices and NForce2, "park" seems to
		 * make problems:  throughput reduction (!), data errors...
		 */
		if (park) {
			park = min(park, (unsigned) 3);
			temp |= CMD_PARK;
			temp |= park << 8;
		}
		ehci_dbg(ehci, "park %d\n", park);
	}
	if (HCC_PGM_FRAMELISTLEN(hcc_params)) {
		/* periodic schedule size can be smaller than default */
		temp &= ~(3 << 2);
		temp |= (EHCI_TUNE_FLS << 2);
		switch (EHCI_TUNE_FLS) {
		case 0: ehci->periodic_size = 1024; break;
		case 1: ehci->periodic_size = 512; break;
		case 2: ehci->periodic_size = 256; break;
		default:	BUG();
		}
	}
	if (HCC_LPM(hcc_params)) {
		/* support link power management EHCI 1.1 addendum */
		ehci_dbg(ehci, "support lpm\n");
		ehci->has_lpm = 1;
		if (hird > 0xf) {
			ehci_dbg(ehci, "hird %d invalid, use default 0",
			hird);
			hird = 0;
		}
		temp |= hird << 24;
	}
	ehci->command = temp;

	return 0;
}