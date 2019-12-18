#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int uses_new_polling; int /*<<< orphan*/  state; TYPE_2__ self; } ;
struct ehci_hcd {int periodic_dma; int command; int sbrn; TYPE_4__* regs; TYPE_3__* caps; int /*<<< orphan*/  last_periodic_enable; TYPE_1__* async; } ;
struct TYPE_8__ {int /*<<< orphan*/  intr_enable; int /*<<< orphan*/  command; int /*<<< orphan*/  configured_flag; int /*<<< orphan*/  segment; int /*<<< orphan*/  async_next; int /*<<< orphan*/  frame_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  hc_capbase; int /*<<< orphan*/  hcc_params; } ;
struct TYPE_5__ {scalar_t__ qh_dma; } ;

/* Variables and functions */
 int CMD_ASE ; 
 int CMD_IAAD ; 
 int CMD_LRESET ; 
 int CMD_PSE ; 
 int CMD_RESET ; 
 int CMD_RUN ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int FLAG_CF ; 
 scalar_t__ HCC_64BIT_ADDR (int) ; 
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 int HC_VERSION (int) ; 
 int INTR_MASK ; 
 int /*<<< orphan*/  create_companion_file (struct ehci_hcd*) ; 
 int /*<<< orphan*/  create_debug_files (struct ehci_hcd*) ; 
 int /*<<< orphan*/  dbg_cmd (struct ehci_hcd*,char*,int) ; 
 int /*<<< orphan*/  dma_set_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_cf_port_reset_rwsem ; 
 int /*<<< orphan*/  ehci_info (struct ehci_hcd*,char*,...) ; 
 int /*<<< orphan*/  ehci_mem_cleanup (struct ehci_hcd*) ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int ehci_reset (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int,int /*<<< orphan*/ *) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 scalar_t__ ignore_oc ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehci_run (struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	int			retval;
	u32			temp;
	u32			hcc_params;

	hcd->uses_new_polling = 1;

	/* EHCI spec section 4.1 */
	if ((retval = ehci_reset(ehci)) != 0) {
		ehci_mem_cleanup(ehci);
		return retval;
	}
	ehci_writel(ehci, ehci->periodic_dma, &ehci->regs->frame_list);
	ehci_writel(ehci, (u32)ehci->async->qh_dma, &ehci->regs->async_next);

	/*
	 * hcc_params controls whether ehci->regs->segment must (!!!)
	 * be used; it constrains QH/ITD/SITD and QTD locations.
	 * pci_pool consistent memory always uses segment zero.
	 * streaming mappings for I/O buffers, like pci_map_single(),
	 * can return segments above 4GB, if the device allows.
	 *
	 * NOTE:  the dma mask is visible through dma_supported(), so
	 * drivers can pass this info along ... like NETIF_F_HIGHDMA,
	 * Scsi_Host.highmem_io, and so forth.  It's readonly to all
	 * host side drivers though.
	 */
	hcc_params = ehci_readl(ehci, &ehci->caps->hcc_params);
	if (HCC_64BIT_ADDR(hcc_params)) {
		ehci_writel(ehci, 0, &ehci->regs->segment);
#if 0
// this is deeply broken on almost all architectures
		if (!dma_set_mask(hcd->self.controller, DMA_BIT_MASK(64)))
			ehci_info(ehci, "enabled 64bit DMA\n");
#endif
	}


	// Philips, Intel, and maybe others need CMD_RUN before the
	// root hub will detect new devices (why?); NEC doesn't
	ehci->command &= ~(CMD_LRESET|CMD_IAAD|CMD_PSE|CMD_ASE|CMD_RESET);
	ehci->command |= CMD_RUN;
	ehci_writel(ehci, ehci->command, &ehci->regs->command);
	dbg_cmd (ehci, "init", ehci->command);

	/*
	 * Start, enabling full USB 2.0 functionality ... usb 1.1 devices
	 * are explicitly handed to companion controller(s), so no TT is
	 * involved with the root hub.  (Except where one is integrated,
	 * and there's no companion controller unless maybe for USB OTG.)
	 *
	 * Turning on the CF flag will transfer ownership of all ports
	 * from the companions to the EHCI controller.  If any of the
	 * companions are in the middle of a port reset at the time, it
	 * could cause trouble.  Write-locking ehci_cf_port_reset_rwsem
	 * guarantees that no resets are in progress.  After we set CF,
	 * a short delay lets the hardware catch up; new resets shouldn't
	 * be started before the port switching actions could complete.
	 */
	down_write(&ehci_cf_port_reset_rwsem);
	hcd->state = HC_STATE_RUNNING;
	ehci_writel(ehci, FLAG_CF, &ehci->regs->configured_flag);
	ehci_readl(ehci, &ehci->regs->command);	/* unblock posted writes */
	msleep(5);
	up_write(&ehci_cf_port_reset_rwsem);
	ehci->last_periodic_enable = ktime_get_real();

	temp = HC_VERSION(ehci_readl(ehci, &ehci->caps->hc_capbase));
	ehci_info (ehci,
		"USB %x.%x started, EHCI %x.%02x%s\n",
		((ehci->sbrn & 0xf0)>>4), (ehci->sbrn & 0x0f),
		temp >> 8, temp & 0xff,
		ignore_oc ? ", overcurrent ignored" : "");

	ehci_writel(ehci, INTR_MASK,
		    &ehci->regs->intr_enable); /* Turn On Interrupts */

	/* GRR this is run-once init(), being done every time the HC starts.
	 * So long as they're part of class devices, we can't do it init()
	 * since the class device isn't created that early.
	 */
	create_debug_files(ehci);
	create_companion_file(ehci);

	return 0;
}