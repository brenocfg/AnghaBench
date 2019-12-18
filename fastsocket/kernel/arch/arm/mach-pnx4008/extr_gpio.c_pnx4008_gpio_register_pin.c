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
 int EBUSY ; 
 unsigned long GPIO_BIT (unsigned short) ; 
 size_t GPIO_INDEX ; 
 scalar_t__ GPIO_ISBID (unsigned short) ; 
 scalar_t__ GPIO_ISIN (unsigned short) ; 
 scalar_t__ GPIO_ISMUX (unsigned short) ; 
 scalar_t__ GPIO_ISOUT (unsigned short) ; 
 scalar_t__ GPIO_ISRAM (unsigned short) ; 
 size_t INP_INDEX ; 
 size_t MUX_INDEX ; 
 size_t OUTP_INDEX ; 
 unsigned long* access_map ; 
 int /*<<< orphan*/  gpio_lock () ; 
 int /*<<< orphan*/  gpio_unlock () ; 

int pnx4008_gpio_register_pin(unsigned short pin)
{
	unsigned long bit = GPIO_BIT(pin);
	int ret = -EBUSY;	/* Already in use */

	gpio_lock();

	if (GPIO_ISBID(pin)) {
		if (access_map[GPIO_INDEX] & bit)
			goto out;
		access_map[GPIO_INDEX] |= bit;

	} else if (GPIO_ISRAM(pin)) {
		if (access_map[GPIO_INDEX] & bit)
			goto out;
		access_map[GPIO_INDEX] |= bit;

	} else if (GPIO_ISMUX(pin)) {
		if (access_map[MUX_INDEX] & bit)
			goto out;
		access_map[MUX_INDEX] |= bit;

	} else if (GPIO_ISOUT(pin)) {
		if (access_map[OUTP_INDEX] & bit)
			goto out;
		access_map[OUTP_INDEX] |= bit;

	} else if (GPIO_ISIN(pin)) {
		if (access_map[INP_INDEX] & bit)
			goto out;
		access_map[INP_INDEX] |= bit;
	} else
		goto out;
	ret = 0;

out:
	gpio_unlock();
	return ret;
}