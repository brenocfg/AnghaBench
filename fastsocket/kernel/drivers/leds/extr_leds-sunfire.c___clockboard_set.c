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
typedef  int u8 ;
struct sunfire_led {int /*<<< orphan*/  reg; } ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
#define  CLOCK_CTRL_LLED 128 
 struct sunfire_led* to_sunfire_led (struct led_classdev*) ; 
 int upa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upa_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __clockboard_set(struct led_classdev *led_cdev,
			     enum led_brightness led_val, u8 bit)
{
	struct sunfire_led *p = to_sunfire_led(led_cdev);
	u8 reg = upa_readb(p->reg);

	switch (bit) {
	case CLOCK_CTRL_LLED:
		if (led_val)
			reg &= ~bit;
		else
			reg |= bit;
		break;

	default:
		if (led_val)
			reg |= bit;
		else
			reg &= ~bit;
		break;
	}
	upa_writeb(reg, p->reg);
}