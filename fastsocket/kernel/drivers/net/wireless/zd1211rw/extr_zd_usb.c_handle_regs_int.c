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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int length; int /*<<< orphan*/  completion; int /*<<< orphan*/  req_count; int /*<<< orphan*/  req; int /*<<< orphan*/ * buffer; } ;
struct zd_usb_interrupt {int /*<<< orphan*/  read_regs_enabled; int /*<<< orphan*/  lock; TYPE_1__ read_regs; scalar_t__ read_regs_int_overridden; } ;
struct zd_usb {struct zd_usb_interrupt intr; } ;
struct zd_mac {int /*<<< orphan*/  process_intr; int /*<<< orphan*/  lock; int /*<<< orphan*/  intr_buffer; } ;
struct urb {int actual_length; int /*<<< orphan*/  transfer_buffer; struct zd_usb* context; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ CR_INTERRUPT ; 
 int USB_MAX_EP_INT_BUFFER ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_read_regs (struct zd_usb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_regs_int_override (struct urb*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct zd_mac* zd_hw_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_usb_to_hw (struct zd_usb*) ; 

__attribute__((used)) static inline void handle_regs_int(struct urb *urb)
{
	struct zd_usb *usb = urb->context;
	struct zd_usb_interrupt *intr = &usb->intr;
	int len;
	u16 int_num;

	ZD_ASSERT(in_interrupt());
	spin_lock(&intr->lock);

	int_num = le16_to_cpu(*(__le16 *)(urb->transfer_buffer+2));
	if (int_num == CR_INTERRUPT) {
		struct zd_mac *mac = zd_hw_mac(zd_usb_to_hw(urb->context));
		spin_lock(&mac->lock);
		memcpy(&mac->intr_buffer, urb->transfer_buffer,
				USB_MAX_EP_INT_BUFFER);
		spin_unlock(&mac->lock);
		schedule_work(&mac->process_intr);
	} else if (atomic_read(&intr->read_regs_enabled)) {
		len = urb->actual_length;
		intr->read_regs.length = urb->actual_length;
		if (len > sizeof(intr->read_regs.buffer))
			len = sizeof(intr->read_regs.buffer);

		memcpy(intr->read_regs.buffer, urb->transfer_buffer, len);

		/* Sometimes USB_INT_ID_REGS is not overridden, but comes after
		 * USB_INT_ID_RETRY_FAILED. Read-reg retry then gets this
		 * delayed USB_INT_ID_REGS, but leaves USB_INT_ID_REGS of
		 * retry unhandled. Next read-reg command then might catch
		 * this wrong USB_INT_ID_REGS. Fix by ignoring wrong reads.
		 */
		if (!check_read_regs(usb, intr->read_regs.req,
						intr->read_regs.req_count))
			goto out;

		atomic_set(&intr->read_regs_enabled, 0);
		intr->read_regs_int_overridden = 0;
		complete(&intr->read_regs.completion);

		goto out;
	}

out:
	spin_unlock(&intr->lock);

	/* CR_INTERRUPT might override read_reg too. */
	if (int_num == CR_INTERRUPT && atomic_read(&intr->read_regs_enabled))
		handle_regs_int_override(urb);
}