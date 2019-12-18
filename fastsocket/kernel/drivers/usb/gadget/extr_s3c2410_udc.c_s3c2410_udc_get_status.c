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
typedef  int u8 ;
typedef  int u16 ;
struct usb_ctrlrequest {int wIndex; int bRequestType; int wLength; } ;
struct s3c2410_udc {int devstatus; } ;

/* Variables and functions */
 int S3C2410_UDC_EP0_CSR_SENDSTL ; 
 int /*<<< orphan*/  S3C2410_UDC_EP0_FIFO_REG ; 
 int S3C2410_UDC_ICSR1_SENDSTL ; 
 int /*<<< orphan*/  S3C2410_UDC_INDEX_REG ; 
 int /*<<< orphan*/  S3C2410_UDC_IN_CSR1_REG ; 
 int S3C2410_UDC_OCSR1_SENDSTL ; 
 int /*<<< orphan*/  S3C2410_UDC_OUT_CSR1_REG ; 
 int USB_DIR_IN ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int /*<<< orphan*/  base_addr ; 
 int /*<<< orphan*/  s3c2410_udc_set_ep0_de_in (int /*<<< orphan*/ ) ; 
 int udc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int s3c2410_udc_get_status(struct s3c2410_udc *dev,
		struct usb_ctrlrequest *crq)
{
	u16 status = 0;
	u8 ep_num = crq->wIndex & 0x7F;
	u8 is_in = crq->wIndex & USB_DIR_IN;

	switch (crq->bRequestType & USB_RECIP_MASK) {
	case USB_RECIP_INTERFACE:
		break;

	case USB_RECIP_DEVICE:
		status = dev->devstatus;
		break;

	case USB_RECIP_ENDPOINT:
		if (ep_num > 4 || crq->wLength > 2)
			return 1;

		if (ep_num == 0) {
			udc_write(0, S3C2410_UDC_INDEX_REG);
			status = udc_read(S3C2410_UDC_IN_CSR1_REG);
			status = status & S3C2410_UDC_EP0_CSR_SENDSTL;
		} else {
			udc_write(ep_num, S3C2410_UDC_INDEX_REG);
			if (is_in) {
				status = udc_read(S3C2410_UDC_IN_CSR1_REG);
				status = status & S3C2410_UDC_ICSR1_SENDSTL;
			} else {
				status = udc_read(S3C2410_UDC_OUT_CSR1_REG);
				status = status & S3C2410_UDC_OCSR1_SENDSTL;
			}
		}

		status = status ? 1 : 0;
		break;

	default:
		return 1;
	}

	/* Seems to be needed to get it working. ouch :( */
	udelay(5);
	udc_write(status & 0xFF, S3C2410_UDC_EP0_FIFO_REG);
	udc_write(status >> 8, S3C2410_UDC_EP0_FIFO_REG);
	s3c2410_udc_set_ep0_de_in(base_addr);

	return 0;
}