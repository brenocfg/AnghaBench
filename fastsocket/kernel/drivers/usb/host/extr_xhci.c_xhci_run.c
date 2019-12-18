#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_7__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct xhci_hcd {int quirks; TYPE_2__* ir_set; TYPE_1__* op_regs; int /*<<< orphan*/  event_ring; int /*<<< orphan*/  erst; int /*<<< orphan*/  cmd_ring; TYPE_3__ event_ring_timer; scalar_t__ zombie; } ;
struct usb_hcd {int uses_new_polling; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq_pending; int /*<<< orphan*/  irq_control; int /*<<< orphan*/  erst_dequeue; } ;
struct TYPE_5__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 scalar_t__ CMD_EIE ; 
 scalar_t__ ERST_PTR_MASK ; 
 scalar_t__ ER_IRQ_ENABLE (scalar_t__) ; 
 scalar_t__ ER_IRQ_INTERVAL_MASK ; 
 int HZ ; 
 int POLL_TIMEOUT ; 
 int /*<<< orphan*/  TRB_NEC_GET_FW ; 
 int /*<<< orphan*/  TRB_TYPE (int /*<<< orphan*/ ) ; 
 int XHCI_NEC_HOST ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  init_timer (TYPE_3__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  usb_hcd_is_primary_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,...) ; 
 int /*<<< orphan*/  xhci_dbg_cmd_ptrs (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_dbg_erst (struct xhci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_dbg_ring_ptrs (struct xhci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_debug_ring (struct xhci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_event_ring_work ; 
 int /*<<< orphan*/  xhci_print_ir_set (struct xhci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_queue_vendor_command (struct xhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xhci_read_64 (struct xhci_hcd*,int /*<<< orphan*/ *) ; 
 scalar_t__ xhci_readl (struct xhci_hcd*,int /*<<< orphan*/ *) ; 
 int xhci_run_finished (struct xhci_hcd*) ; 
 int xhci_try_enable_msi (struct usb_hcd*) ; 
 int /*<<< orphan*/  xhci_writel (struct xhci_hcd*,scalar_t__,int /*<<< orphan*/ *) ; 

int xhci_run(struct usb_hcd *hcd)
{
	u32 temp;
	u64 temp_64;
	int ret;
	struct xhci_hcd *xhci = hcd_to_xhci(hcd);

	/* Start the xHCI host controller running only after the USB 2.0 roothub
	 * is setup.
	 */

	hcd->uses_new_polling = 1;
	if (!usb_hcd_is_primary_hcd(hcd))
		return xhci_run_finished(xhci);

	xhci_dbg(xhci, "xhci_run\n");

	ret = xhci_try_enable_msi(hcd);
	if (ret)
		return ret;

#ifdef CONFIG_USB_XHCI_HCD_DEBUGGING
	init_timer(&xhci->event_ring_timer);
	xhci->event_ring_timer.data = (unsigned long) xhci;
	xhci->event_ring_timer.function = xhci_event_ring_work;
	/* Poll the event ring */
	xhci->event_ring_timer.expires = jiffies + POLL_TIMEOUT * HZ;
	xhci->zombie = 0;
	xhci_dbg(xhci, "Setting event ring polling timer\n");
	add_timer(&xhci->event_ring_timer);
#endif

	xhci_dbg(xhci, "Command ring memory map follows:\n");
	xhci_debug_ring(xhci, xhci->cmd_ring);
	xhci_dbg_ring_ptrs(xhci, xhci->cmd_ring);
	xhci_dbg_cmd_ptrs(xhci);

	xhci_dbg(xhci, "ERST memory map follows:\n");
	xhci_dbg_erst(xhci, &xhci->erst);
	xhci_dbg(xhci, "Event ring:\n");
	xhci_debug_ring(xhci, xhci->event_ring);
	xhci_dbg_ring_ptrs(xhci, xhci->event_ring);
	temp_64 = xhci_read_64(xhci, &xhci->ir_set->erst_dequeue);
	temp_64 &= ~ERST_PTR_MASK;
	xhci_dbg(xhci, "ERST deq = 64'h%0lx\n", (long unsigned int) temp_64);

	xhci_dbg(xhci, "// Set the interrupt modulation register\n");
	temp = xhci_readl(xhci, &xhci->ir_set->irq_control);
	temp &= ~ER_IRQ_INTERVAL_MASK;
	temp |= (u32) 160;
	xhci_writel(xhci, temp, &xhci->ir_set->irq_control);

	/* Set the HCD state before we enable the irqs */
	temp = xhci_readl(xhci, &xhci->op_regs->command);
	temp |= (CMD_EIE);
	xhci_dbg(xhci, "// Enable interrupts, cmd = 0x%x.\n",
			temp);
	xhci_writel(xhci, temp, &xhci->op_regs->command);

	temp = xhci_readl(xhci, &xhci->ir_set->irq_pending);
	xhci_dbg(xhci, "// Enabling event ring interrupter %p by writing 0x%x to irq_pending\n",
			xhci->ir_set, (unsigned int) ER_IRQ_ENABLE(temp));
	xhci_writel(xhci, ER_IRQ_ENABLE(temp),
			&xhci->ir_set->irq_pending);
	xhci_print_ir_set(xhci, 0);

	if (xhci->quirks & XHCI_NEC_HOST)
		xhci_queue_vendor_command(xhci, 0, 0, 0,
				TRB_TYPE(TRB_NEC_GET_FW));

	xhci_dbg(xhci, "Finished xhci_run for USB2 roothub\n");
	return 0;
}