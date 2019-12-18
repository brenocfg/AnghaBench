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
struct wm97xx {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void atmel_wm97xx_irq_enable(struct wm97xx *wm, int enable)
{
	/* Intentionally left empty. */
}