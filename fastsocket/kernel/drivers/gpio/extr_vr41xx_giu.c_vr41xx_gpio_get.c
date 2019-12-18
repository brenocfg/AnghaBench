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
typedef  int u16 ;
struct gpio_chip {unsigned int ngpio; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GIUPIODH ; 
 int /*<<< orphan*/  GIUPIODL ; 
 int /*<<< orphan*/  GIUPODATH ; 
 int /*<<< orphan*/  GIUPODATL ; 
 int giu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vr41xx_gpio_get(struct gpio_chip *chip, unsigned pin)
{
	u16 reg, mask;

	if (pin >= chip->ngpio)
		return -EINVAL;

	if (pin < 16) {
		reg = giu_read(GIUPIODL);
		mask = 1 << pin;
	} else if (pin < 32) {
		reg = giu_read(GIUPIODH);
		mask = 1 << (pin - 16);
	} else if (pin < 48) {
		reg = giu_read(GIUPODATL);
		mask = 1 << (pin - 32);
	} else {
		reg = giu_read(GIUPODATH);
		mask = 1 << (pin - 48);
	}

	if (reg & mask)
		return 1;

	return 0;
}