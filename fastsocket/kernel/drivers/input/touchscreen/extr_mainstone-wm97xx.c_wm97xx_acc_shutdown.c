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
struct wm97xx {scalar_t__ pen_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 scalar_t__ irq ; 
 scalar_t__ pen_int ; 

__attribute__((used)) static void wm97xx_acc_shutdown(struct wm97xx *wm)
{
	/* codec specific deconfig */
	if (pen_int) {
		if (irq)
			gpio_free(irq);
		wm->pen_irq = 0;
	}
}