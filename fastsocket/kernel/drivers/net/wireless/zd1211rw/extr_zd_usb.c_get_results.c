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
typedef  int /*<<< orphan*/  u16 ;
struct read_regs_int {scalar_t__ buffer; } ;
struct zd_usb_interrupt {int /*<<< orphan*/  lock; int /*<<< orphan*/  read_regs_int_overridden; struct read_regs_int read_regs; } ;
struct zd_usb {struct zd_usb_interrupt intr; } ;
struct usb_req_read_regs {int dummy; } ;
struct usb_int_regs {struct reg_data* regs; } ;
struct reg_data {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  check_read_regs (struct zd_usb*,struct usb_req_read_regs*,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 

__attribute__((used)) static int get_results(struct zd_usb *usb, u16 *values,
		       struct usb_req_read_regs *req, unsigned int count,
		       bool *retry)
{
	int r;
	int i;
	struct zd_usb_interrupt *intr = &usb->intr;
	struct read_regs_int *rr = &intr->read_regs;
	struct usb_int_regs *regs = (struct usb_int_regs *)rr->buffer;

	spin_lock_irq(&intr->lock);

	r = -EIO;

	/* Read failed because firmware bug? */
	*retry = !!intr->read_regs_int_overridden;
	if (*retry)
		goto error_unlock;

	if (!check_read_regs(usb, req, count)) {
		dev_dbg_f(zd_usb_dev(usb), "error: invalid read regs\n");
		goto error_unlock;
	}

	for (i = 0; i < count; i++) {
		struct reg_data *rd = &regs->regs[i];
		values[i] = le16_to_cpu(rd->value);
	}

	r = 0;
error_unlock:
	spin_unlock_irq(&intr->lock);
	return r;
}