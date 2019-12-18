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
struct read_regs_int {int length; scalar_t__ buffer; } ;
struct zd_usb_interrupt {struct read_regs_int read_regs; } ;
struct zd_usb {struct zd_usb_interrupt intr; } ;
struct usb_req_read_regs {scalar_t__* addr; } ;
struct usb_int_regs {struct reg_data* regs; } ;
struct reg_data {scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int usb_int_regs_length (unsigned int) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 

__attribute__((used)) static bool check_read_regs(struct zd_usb *usb, struct usb_req_read_regs *req,
			    unsigned int count)
{
	int i;
	struct zd_usb_interrupt *intr = &usb->intr;
	struct read_regs_int *rr = &intr->read_regs;
	struct usb_int_regs *regs = (struct usb_int_regs *)rr->buffer;

	/* The created block size seems to be larger than expected.
	 * However results appear to be correct.
	 */
	if (rr->length < usb_int_regs_length(count)) {
		dev_dbg_f(zd_usb_dev(usb),
			 "error: actual length %d less than expected %d\n",
			 rr->length, usb_int_regs_length(count));
		return false;
	}

	if (rr->length > sizeof(rr->buffer)) {
		dev_dbg_f(zd_usb_dev(usb),
			 "error: actual length %d exceeds buffer size %zu\n",
			 rr->length, sizeof(rr->buffer));
		return false;
	}

	for (i = 0; i < count; i++) {
		struct reg_data *rd = &regs->regs[i];
		if (rd->addr != req->addr[i]) {
			dev_dbg_f(zd_usb_dev(usb),
				 "rd[%d] addr %#06hx expected %#06hx\n", i,
				 le16_to_cpu(rd->addr),
				 le16_to_cpu(req->addr[i]));
			return false;
		}
	}

	return true;
}