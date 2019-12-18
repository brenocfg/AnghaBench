#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wa_xfer_hdr {size_t dwTransferLength; size_t bTransferSegment; } ;
struct wa_xfer {size_t segs; size_t seg_size; TYPE_3__** seg; TYPE_2__* wa; } ;
struct urb {size_t transfer_buffer_length; } ;
struct device {int dummy; } ;
typedef  enum wa_xfer_type { ____Placeholder_wa_xfer_type } wa_xfer_type ;
struct TYPE_6__ {int /*<<< orphan*/  status; struct wa_xfer_hdr xfer_hdr; } ;
struct TYPE_5__ {TYPE_1__* usb_iface; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WA_SEG_READY ; 
 int /*<<< orphan*/  __wa_xfer_setup_hdr0 (struct wa_xfer*,struct wa_xfer_hdr*,int,size_t) ; 
 int __wa_xfer_setup_segs (struct wa_xfer*,size_t) ; 
 int __wa_xfer_setup_sizes (struct wa_xfer*,int*) ; 
 size_t cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,struct wa_xfer*,size_t,int) ; 
 int /*<<< orphan*/  memcpy (struct wa_xfer_hdr*,struct wa_xfer_hdr*,size_t) ; 
 int /*<<< orphan*/  wa_xfer_id_init (struct wa_xfer*) ; 

__attribute__((used)) static int __wa_xfer_setup(struct wa_xfer *xfer, struct urb *urb)
{
	int result;
	struct device *dev = &xfer->wa->usb_iface->dev;
	enum wa_xfer_type xfer_type = 0; /* shut up GCC */
	size_t xfer_hdr_size, cnt, transfer_size;
	struct wa_xfer_hdr *xfer_hdr0, *xfer_hdr;

	result = __wa_xfer_setup_sizes(xfer, &xfer_type);
	if (result < 0)
		goto error_setup_sizes;
	xfer_hdr_size = result;
	result = __wa_xfer_setup_segs(xfer, xfer_hdr_size);
	if (result < 0) {
		dev_err(dev, "xfer %p: Failed to allocate %d segments: %d\n",
			xfer, xfer->segs, result);
		goto error_setup_segs;
	}
	/* Fill the first header */
	xfer_hdr0 = &xfer->seg[0]->xfer_hdr;
	wa_xfer_id_init(xfer);
	__wa_xfer_setup_hdr0(xfer, xfer_hdr0, xfer_type, xfer_hdr_size);

	/* Fill remainig headers */
	xfer_hdr = xfer_hdr0;
	transfer_size = urb->transfer_buffer_length;
	xfer_hdr0->dwTransferLength = transfer_size > xfer->seg_size ?
		xfer->seg_size : transfer_size;
	transfer_size -=  xfer->seg_size;
	for (cnt = 1; cnt < xfer->segs; cnt++) {
		xfer_hdr = &xfer->seg[cnt]->xfer_hdr;
		memcpy(xfer_hdr, xfer_hdr0, xfer_hdr_size);
		xfer_hdr->bTransferSegment = cnt;
		xfer_hdr->dwTransferLength = transfer_size > xfer->seg_size ?
			cpu_to_le32(xfer->seg_size)
			: cpu_to_le32(transfer_size);
		xfer->seg[cnt]->status = WA_SEG_READY;
		transfer_size -=  xfer->seg_size;
	}
	xfer_hdr->bTransferSegment |= 0x80;	/* this is the last segment */
	result = 0;
error_setup_segs:
error_setup_sizes:
	return result;
}