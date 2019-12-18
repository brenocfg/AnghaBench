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

/* Variables and functions */
#define  IRQ_PCI_PERR 129 
#define  IRQ_PCI_SERR 128 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_irq (unsigned long) ; 
 int /*<<< orphan*/  perr_timer ; 
 int /*<<< orphan*/  serr_timer ; 

__attribute__((used)) static void dc21285_enable_error(unsigned long __data)
{
	switch (__data) {
	case IRQ_PCI_SERR:
		del_timer(&serr_timer);
		break;

	case IRQ_PCI_PERR:
		del_timer(&perr_timer);
		break;
	}

	enable_irq(__data);
}