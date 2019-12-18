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
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int am300_init_gpio_regs (struct broadsheetfb_par*) ; 

__attribute__((used)) static int am300_init_board(struct broadsheetfb_par *par)
{
	return am300_init_gpio_regs(par);
}