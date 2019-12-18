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
struct TYPE_2__ {int /*<<< orphan*/  completion; } ;
struct zd_usb_interrupt {int read_regs_int_overridden; int /*<<< orphan*/  lock; TYPE_1__ read_regs; int /*<<< orphan*/  read_regs_enabled; } ;
struct zd_usb {struct zd_usb_interrupt intr; } ;
struct urb {struct zd_usb* context; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void handle_regs_int_override(struct urb *urb)
{
	struct zd_usb *usb = urb->context;
	struct zd_usb_interrupt *intr = &usb->intr;

	spin_lock(&intr->lock);
	if (atomic_read(&intr->read_regs_enabled)) {
		atomic_set(&intr->read_regs_enabled, 0);
		intr->read_regs_int_overridden = 1;
		complete(&intr->read_regs.completion);
	}
	spin_unlock(&intr->lock);
}