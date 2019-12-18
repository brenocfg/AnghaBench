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
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  zero; int /*<<< orphan*/  length; int /*<<< orphan*/  actual; } ;
struct s3c2410_request {TYPE_2__ req; } ;
struct TYPE_4__ {unsigned int maxpacket; } ;
struct s3c2410_ep {int bEndpointAddress; TYPE_3__* dev; TYPE_1__ ep; } ;
struct TYPE_6__ {int /*<<< orphan*/  ep0state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_NORMAL ; 
 int /*<<< orphan*/  EP0_IDLE ; 
 int S3C2410_UDC_EP0_FIFO_REG ; 
 int S3C2410_UDC_EP1_FIFO_REG ; 
 int S3C2410_UDC_EP2_FIFO_REG ; 
 int S3C2410_UDC_EP3_FIFO_REG ; 
 int S3C2410_UDC_EP4_FIFO_REG ; 
 int S3C2410_UDC_ICSR1_PKTRDY ; 
 int /*<<< orphan*/  S3C2410_UDC_INDEX_REG ; 
 int /*<<< orphan*/  S3C2410_UDC_IN_CSR1_REG ; 
 int S3C2410_UDC_USBINT_RESET ; 
 int /*<<< orphan*/  S3C2410_UDC_USB_INT_REG ; 
 int /*<<< orphan*/  base_addr ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_udc_done (struct s3c2410_ep*,struct s3c2410_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_udc_set_ep0_de_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_udc_set_ep0_ipr (int /*<<< orphan*/ ) ; 
 unsigned int s3c2410_udc_write_packet (int,struct s3c2410_request*,unsigned int) ; 
 int udc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c2410_udc_write_fifo(struct s3c2410_ep *ep,
		struct s3c2410_request *req)
{
	unsigned	count;
	int		is_last;
	u32		idx;
	int		fifo_reg;
	u32		ep_csr;

	idx = ep->bEndpointAddress & 0x7F;
	switch (idx) {
	default:
		idx = 0;
	case 0:
		fifo_reg = S3C2410_UDC_EP0_FIFO_REG;
		break;
	case 1:
		fifo_reg = S3C2410_UDC_EP1_FIFO_REG;
		break;
	case 2:
		fifo_reg = S3C2410_UDC_EP2_FIFO_REG;
		break;
	case 3:
		fifo_reg = S3C2410_UDC_EP3_FIFO_REG;
		break;
	case 4:
		fifo_reg = S3C2410_UDC_EP4_FIFO_REG;
		break;
	}

	count = s3c2410_udc_write_packet(fifo_reg, req, ep->ep.maxpacket);

	/* last packet is often short (sometimes a zlp) */
	if (count != ep->ep.maxpacket)
		is_last = 1;
	else if (req->req.length != req->req.actual || req->req.zero)
		is_last = 0;
	else
		is_last = 2;

	/* Only ep0 debug messages are interesting */
	if (idx == 0)
		dprintk(DEBUG_NORMAL,
			"Written ep%d %d.%d of %d b [last %d,z %d]\n",
			idx, count, req->req.actual, req->req.length,
			is_last, req->req.zero);

	if (is_last) {
		/* The order is important. It prevents sending 2 packets
		 * at the same time */

		if (idx == 0) {
			/* Reset signal => no need to say 'data sent' */
			if (! (udc_read(S3C2410_UDC_USB_INT_REG)
					& S3C2410_UDC_USBINT_RESET))
				s3c2410_udc_set_ep0_de_in(base_addr);
			ep->dev->ep0state=EP0_IDLE;
		} else {
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			ep_csr = udc_read(S3C2410_UDC_IN_CSR1_REG);
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			udc_write(ep_csr | S3C2410_UDC_ICSR1_PKTRDY,
					S3C2410_UDC_IN_CSR1_REG);
		}

		s3c2410_udc_done(ep, req, 0);
		is_last = 1;
	} else {
		if (idx == 0) {
			/* Reset signal => no need to say 'data sent' */
			if (! (udc_read(S3C2410_UDC_USB_INT_REG)
					& S3C2410_UDC_USBINT_RESET))
				s3c2410_udc_set_ep0_ipr(base_addr);
		} else {
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			ep_csr = udc_read(S3C2410_UDC_IN_CSR1_REG);
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			udc_write(ep_csr | S3C2410_UDC_ICSR1_PKTRDY,
					S3C2410_UDC_IN_CSR1_REG);
		}
	}

	return is_last;
}