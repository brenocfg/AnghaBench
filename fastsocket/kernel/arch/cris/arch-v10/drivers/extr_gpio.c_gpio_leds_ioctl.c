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
 int /*<<< orphan*/  CRIS_LED_ACTIVE_SET_G (unsigned char) ; 
 int /*<<< orphan*/  CRIS_LED_ACTIVE_SET_R (unsigned char) ; 
 int /*<<< orphan*/  CRIS_LED_BIT_CLR (unsigned long) ; 
 int /*<<< orphan*/  CRIS_LED_BIT_SET (unsigned long) ; 
 int EINVAL ; 
#define  IO_LEDACTIVE_SET 130 
#define  IO_LED_CLRBIT 129 
#define  IO_LED_SETBIT 128 
 int _IOC_NR (unsigned int) ; 

__attribute__((used)) static int
gpio_leds_ioctl(unsigned int cmd, unsigned long arg)
{
	unsigned char green;
	unsigned char red;

	switch (_IOC_NR(cmd)) {
	case IO_LEDACTIVE_SET:
		green = ((unsigned char)arg) & 1;
		red   = (((unsigned char)arg) >> 1) & 1;
		CRIS_LED_ACTIVE_SET_G(green);
		CRIS_LED_ACTIVE_SET_R(red);
		break;

	case IO_LED_SETBIT:
		CRIS_LED_BIT_SET(arg);
		break;

	case IO_LED_CLRBIT:
		CRIS_LED_BIT_CLR(arg);
		break;

	default:
		return -EINVAL;
	} /* switch */

	return 0;
}