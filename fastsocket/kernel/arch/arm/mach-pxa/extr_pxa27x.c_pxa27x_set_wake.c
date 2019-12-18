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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_KEYPAD ; 
#define  IRQ_RTCAlrm 129 
 int IRQ_TO_GPIO (unsigned int) ; 
#define  IRQ_USB 128 
 unsigned int PWER ; 
 unsigned int PWER_RTC ; 
 int gpio_set_wake (int,unsigned int) ; 
 int keypad_set_wake (unsigned int) ; 

__attribute__((used)) static int pxa27x_set_wake(unsigned int irq, unsigned int on)
{
	int gpio = IRQ_TO_GPIO(irq);
	uint32_t mask;

	if (gpio >= 0 && gpio < 128)
		return gpio_set_wake(gpio, on);

	if (irq == IRQ_KEYPAD)
		return keypad_set_wake(on);

	switch (irq) {
	case IRQ_RTCAlrm:
		mask = PWER_RTC;
		break;
	case IRQ_USB:
		mask = 1u << 26;
		break;
	default:
		return -EINVAL;
	}

	if (on)
		PWER |= mask;
	else
		PWER &=~mask;

	return 0;
}