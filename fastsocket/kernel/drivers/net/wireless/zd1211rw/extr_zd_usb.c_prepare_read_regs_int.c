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
struct TYPE_2__ {unsigned int req_count; int /*<<< orphan*/  completion; struct usb_req_read_regs* req; } ;
struct zd_usb_interrupt {int /*<<< orphan*/  lock; TYPE_1__ read_regs; int /*<<< orphan*/  read_regs_enabled; } ;
struct zd_usb {struct zd_usb_interrupt intr; } ;
struct usb_req_read_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_COMPLETION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prepare_read_regs_int(struct zd_usb *usb,
				  struct usb_req_read_regs *req,
				  unsigned int count)
{
	struct zd_usb_interrupt *intr = &usb->intr;

	spin_lock_irq(&intr->lock);
	atomic_set(&intr->read_regs_enabled, 1);
	intr->read_regs.req = req;
	intr->read_regs.req_count = count;
	INIT_COMPLETION(intr->read_regs.completion);
	spin_unlock_irq(&intr->lock);
}