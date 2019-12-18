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
struct w100fb_par {TYPE_1__* mode; } ;
struct TYPE_2__ {int xres; } ;

/* Variables and functions */
 int /*<<< orphan*/  W100_GPIO_PORT_A ; 
 unsigned long w100fb_gpio_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w100fb_gpio_write (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void e800_tg_change(struct w100fb_par *par)
{
	unsigned long tmp;

	tmp = w100fb_gpio_read(W100_GPIO_PORT_A);
	if (par->mode->xres == 480)
		tmp |= 0x100;
	else
		tmp &= ~0x100;
	w100fb_gpio_write(W100_GPIO_PORT_A, tmp);
}