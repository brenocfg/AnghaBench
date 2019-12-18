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
struct TYPE_10__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct oxu_hcd {int i_thresh; int next_uframe; int command; TYPE_4__* async; scalar_t__ reclaim_ready; int /*<<< orphan*/ * reclaim; TYPE_1__* caps; int /*<<< orphan*/  periodic_size; TYPE_5__ watchdog; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/ * qh; } ;
struct TYPE_9__ {TYPE_3__* dummy; int /*<<< orphan*/  hw_alt_next; int /*<<< orphan*/  qh_state; int /*<<< orphan*/  hw_qtd_next; void* hw_token; void* hw_info1; int /*<<< orphan*/  qh_dma; int /*<<< orphan*/  hw_next; TYPE_2__ qh_next; } ;
struct TYPE_8__ {int /*<<< orphan*/  qtd_dma; } ;
struct TYPE_6__ {int /*<<< orphan*/  hcc_params; } ;

/* Variables and functions */
 int CMD_PARK ; 
 int /*<<< orphan*/  DEFAULT_I_TDPS ; 
 int /*<<< orphan*/  EHCI_LIST_END ; 
 int EHCI_TUNE_FLS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HCC_CANPARK (int) ; 
 scalar_t__ HCC_ISOC_CACHE (int) ; 
 int HCC_ISOC_THRES (int) ; 
 scalar_t__ HCC_PGM_FRAMELISTLEN (int) ; 
 int /*<<< orphan*/  QH_HEAD ; 
 int /*<<< orphan*/  QH_NEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QH_STATE_LINKED ; 
 int /*<<< orphan*/  QTD_NEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QTD_STS_HALT ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int ehci_mem_init (struct oxu_hcd*,int /*<<< orphan*/ ) ; 
 struct oxu_hcd* hcd_to_oxu (struct usb_hcd*) ; 
 int /*<<< orphan*/  init_timer (TYPE_5__*) ; 
 int log2_irq_thresh ; 
 int min (int,unsigned int) ; 
 int /*<<< orphan*/  oxu_dbg (struct oxu_hcd*,char*,int) ; 
 int /*<<< orphan*/  oxu_watchdog ; 
 int park ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oxu_hcd_init(struct usb_hcd *hcd)
{
	struct oxu_hcd *oxu = hcd_to_oxu(hcd);
	u32 temp;
	int retval;
	u32 hcc_params;

	spin_lock_init(&oxu->lock);

	init_timer(&oxu->watchdog);
	oxu->watchdog.function = oxu_watchdog;
	oxu->watchdog.data = (unsigned long) oxu;

	/*
	 * hw default: 1K periodic list heads, one per frame.
	 * periodic_size can shrink by USBCMD update if hcc_params allows.
	 */
	oxu->periodic_size = DEFAULT_I_TDPS;
	retval = ehci_mem_init(oxu, GFP_KERNEL);
	if (retval < 0)
		return retval;

	/* controllers may cache some of the periodic schedule ... */
	hcc_params = readl(&oxu->caps->hcc_params);
	if (HCC_ISOC_CACHE(hcc_params))		/* full frame cache */
		oxu->i_thresh = 8;
	else					/* N microframes cached */
		oxu->i_thresh = 2 + HCC_ISOC_THRES(hcc_params);

	oxu->reclaim = NULL;
	oxu->reclaim_ready = 0;
	oxu->next_uframe = -1;

	/*
	 * dedicate a qh for the async ring head, since we couldn't unlink
	 * a 'real' qh without stopping the async schedule [4.8].  use it
	 * as the 'reclamation list head' too.
	 * its dummy is used in hw_alt_next of many tds, to prevent the qh
	 * from automatically advancing to the next td after short reads.
	 */
	oxu->async->qh_next.qh = NULL;
	oxu->async->hw_next = QH_NEXT(oxu->async->qh_dma);
	oxu->async->hw_info1 = cpu_to_le32(QH_HEAD);
	oxu->async->hw_token = cpu_to_le32(QTD_STS_HALT);
	oxu->async->hw_qtd_next = EHCI_LIST_END;
	oxu->async->qh_state = QH_STATE_LINKED;
	oxu->async->hw_alt_next = QTD_NEXT(oxu->async->dummy->qtd_dma);

	/* clear interrupt enables, set irq latency */
	if (log2_irq_thresh < 0 || log2_irq_thresh > 6)
		log2_irq_thresh = 0;
	temp = 1 << (16 + log2_irq_thresh);
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
		oxu_dbg(oxu, "park %d\n", park);
	}
	if (HCC_PGM_FRAMELISTLEN(hcc_params)) {
		/* periodic schedule size can be smaller than default */
		temp &= ~(3 << 2);
		temp |= (EHCI_TUNE_FLS << 2);
	}
	oxu->command = temp;

	return 0;
}