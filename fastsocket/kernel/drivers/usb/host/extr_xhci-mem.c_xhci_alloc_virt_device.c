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
struct xhci_virt_device {TYPE_2__* out_ctx; struct usb_device* udev; int /*<<< orphan*/  cmd_list; int /*<<< orphan*/  cmd_completion; scalar_t__ num_rings_cached; void* ring_cache; TYPE_4__* eps; TYPE_1__* in_ctx; } ;
struct xhci_ring {int dummy; } ;
struct xhci_hcd {TYPE_3__* dcbaa; struct xhci_virt_device** devs; } ;
struct usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_8__ {int /*<<< orphan*/  ring; int /*<<< orphan*/  bw_endpoint_list; int /*<<< orphan*/  cancelled_td_list; } ;
struct TYPE_7__ {int /*<<< orphan*/ * dev_context_ptrs; } ;
struct TYPE_6__ {scalar_t__ dma; } ;
struct TYPE_5__ {scalar_t__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_CTRL ; 
 int /*<<< orphan*/  XHCI_CTX_TYPE_DEVICE ; 
 int /*<<< orphan*/  XHCI_CTX_TYPE_INPUT ; 
 int XHCI_MAX_RINGS_CACHED ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 void* xhci_alloc_container_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int,unsigned long long,...) ; 
 int /*<<< orphan*/  xhci_free_virt_device (struct xhci_hcd*,int) ; 
 int /*<<< orphan*/  xhci_init_endpoint_timer (struct xhci_hcd*,TYPE_4__*) ; 
 int /*<<< orphan*/  xhci_ring_alloc (struct xhci_hcd*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,int) ; 

int xhci_alloc_virt_device(struct xhci_hcd *xhci, int slot_id,
		struct usb_device *udev, gfp_t flags)
{
	struct xhci_virt_device *dev;
	int i;

	/* Slot ID 0 is reserved */
	if (slot_id == 0 || xhci->devs[slot_id]) {
		xhci_warn(xhci, "Bad Slot ID %d\n", slot_id);
		return 0;
	}

	xhci->devs[slot_id] = kzalloc(sizeof(*xhci->devs[slot_id]), flags);
	if (!xhci->devs[slot_id])
		return 0;
	dev = xhci->devs[slot_id];

	/* Allocate the (output) device context that will be used in the HC. */
	dev->out_ctx = xhci_alloc_container_ctx(xhci, XHCI_CTX_TYPE_DEVICE, flags);
	if (!dev->out_ctx)
		goto fail;

	xhci_dbg(xhci, "Slot %d output ctx = 0x%llx (dma)\n", slot_id,
			(unsigned long long)dev->out_ctx->dma);

	/* Allocate the (input) device context for address device command */
	dev->in_ctx = xhci_alloc_container_ctx(xhci, XHCI_CTX_TYPE_INPUT, flags);
	if (!dev->in_ctx)
		goto fail;

	xhci_dbg(xhci, "Slot %d input ctx = 0x%llx (dma)\n", slot_id,
			(unsigned long long)dev->in_ctx->dma);

	/* Initialize the cancellation list and watchdog timers for each ep */
	for (i = 0; i < 31; i++) {
		xhci_init_endpoint_timer(xhci, &dev->eps[i]);
		INIT_LIST_HEAD(&dev->eps[i].cancelled_td_list);
		INIT_LIST_HEAD(&dev->eps[i].bw_endpoint_list);
	}

	/* Allocate endpoint 0 ring */
	dev->eps[0].ring = xhci_ring_alloc(xhci, 2, 1, TYPE_CTRL, flags);
	if (!dev->eps[0].ring)
		goto fail;

	/* Allocate pointers to the ring cache */
	dev->ring_cache = kzalloc(
			sizeof(struct xhci_ring *)*XHCI_MAX_RINGS_CACHED,
			flags);
	if (!dev->ring_cache)
		goto fail;
	dev->num_rings_cached = 0;

	init_completion(&dev->cmd_completion);
	INIT_LIST_HEAD(&dev->cmd_list);
	dev->udev = udev;

	/* Point to output device context in dcbaa. */
	xhci->dcbaa->dev_context_ptrs[slot_id] = cpu_to_le64(dev->out_ctx->dma);
	xhci_dbg(xhci, "Set slot id %d dcbaa entry %p to 0x%llx\n",
		 slot_id,
		 &xhci->dcbaa->dev_context_ptrs[slot_id],
		 le64_to_cpu(xhci->dcbaa->dev_context_ptrs[slot_id]));

	return 1;
fail:
	xhci_free_virt_device(xhci, slot_id);
	return 0;
}