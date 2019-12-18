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
typedef  int u32 ;
struct urb {int /*<<< orphan*/  pipe; TYPE_1__* dev; int /*<<< orphan*/  unlinked; int /*<<< orphan*/  actual_length; } ;
struct ehci_hcd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  devpath; } ;

/* Variables and functions */
 int ECOMM ; 
 int EINPROGRESS ; 
 int ENOSR ; 
 int EOVERFLOW ; 
 int EPIPE ; 
 int EPROTO ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  IS_SHORT_READ (int) ; 
 scalar_t__ QTD_CERR (int) ; 
 size_t QTD_LENGTH (int) ; 
 int QTD_PID (int) ; 
 int QTD_STS_BABBLE ; 
 int QTD_STS_DBE ; 
 int QTD_STS_HALT ; 
 int QTD_STS_MMF ; 
 int QTD_STS_XACT ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ehci_vdbg (struct ehci_hcd*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipedevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qtd_copy_status (
	struct ehci_hcd *ehci,
	struct urb *urb,
	size_t length,
	u32 token
)
{
	int	status = -EINPROGRESS;

	/* count IN/OUT bytes, not SETUP (even short packets) */
	if (likely (QTD_PID (token) != 2))
		urb->actual_length += length - QTD_LENGTH (token);

	/* don't modify error codes */
	if (unlikely(urb->unlinked))
		return status;

	/* force cleanup after short read; not always an error */
	if (unlikely (IS_SHORT_READ (token)))
		status = -EREMOTEIO;

	/* serious "can't proceed" faults reported by the hardware */
	if (token & QTD_STS_HALT) {
		if (token & QTD_STS_BABBLE) {
			/* FIXME "must" disable babbling device's port too */
			status = -EOVERFLOW;
		/* CERR nonzero + halt --> stall */
		} else if (QTD_CERR(token)) {
			status = -EPIPE;

		/* In theory, more than one of the following bits can be set
		 * since they are sticky and the transaction is retried.
		 * Which to test first is rather arbitrary.
		 */
		} else if (token & QTD_STS_MMF) {
			/* fs/ls interrupt xfer missed the complete-split */
			status = -EPROTO;
		} else if (token & QTD_STS_DBE) {
			status = (QTD_PID (token) == 1) /* IN ? */
				? -ENOSR  /* hc couldn't read data */
				: -ECOMM; /* hc couldn't write data */
		} else if (token & QTD_STS_XACT) {
			/* timeout, bad CRC, wrong PID, etc */
			ehci_dbg(ehci, "devpath %s ep%d%s 3strikes\n",
				urb->dev->devpath,
				usb_pipeendpoint(urb->pipe),
				usb_pipein(urb->pipe) ? "in" : "out");
			status = -EPROTO;
		} else {	/* unknown */
			status = -EPROTO;
		}

		ehci_vdbg (ehci,
			"dev%d ep%d%s qtd token %08x --> status %d\n",
			usb_pipedevice (urb->pipe),
			usb_pipeendpoint (urb->pipe),
			usb_pipein (urb->pipe) ? "in" : "out",
			token, status);
	}

	return status;
}