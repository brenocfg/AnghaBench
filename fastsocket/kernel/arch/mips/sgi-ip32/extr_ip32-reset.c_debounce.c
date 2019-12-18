#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;

/* Variables and functions */
 unsigned char CMOS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMOS_WRITE (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DS_B1_XCTRL4A ; 
 unsigned char DS_REGA_DV0 ; 
 unsigned char DS_XCTRL4A_IFS ; 
 int /*<<< orphan*/  MACEISA_RTC_IRQ ; 
 int /*<<< orphan*/  RTC_INTR_FLAGS ; 
 unsigned char RTC_IRQF ; 
 int /*<<< orphan*/  RTC_REG_A ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 TYPE_1__ debounce_timer ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ has_panicked ; 
 int /*<<< orphan*/  ip32_machine_restart (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  wbflush () ; 

__attribute__((used)) static void debounce(unsigned long data)
{
	unsigned char reg_a, reg_c, xctrl_a;

	reg_c = CMOS_READ(RTC_INTR_FLAGS);
	reg_a = CMOS_READ(RTC_REG_A);
	CMOS_WRITE(reg_a | DS_REGA_DV0, RTC_REG_A);
	wbflush();
	xctrl_a = CMOS_READ(DS_B1_XCTRL4A);
	if ((xctrl_a & DS_XCTRL4A_IFS) || (reg_c & RTC_IRQF )) {
		/* Interrupt still being sent. */
		debounce_timer.expires = jiffies + 50;
		add_timer(&debounce_timer);

		/* clear interrupt source */
		CMOS_WRITE(xctrl_a & ~DS_XCTRL4A_IFS, DS_B1_XCTRL4A);
		CMOS_WRITE(reg_a & ~DS_REGA_DV0, RTC_REG_A);
		return;
	}
	CMOS_WRITE(reg_a & ~DS_REGA_DV0, RTC_REG_A);

	if (has_panicked)
		ip32_machine_restart(NULL);

	enable_irq(MACEISA_RTC_IRQ);
}