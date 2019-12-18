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
 int /*<<< orphan*/  PBC_BCTRL1_CLEAR_REG ; 
 int /*<<< orphan*/  PBC_BCTRL1_LCDON ; 
 int /*<<< orphan*/  PBC_BCTRL1_SET_REG ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lcd_power(int on)
{
	if (on)
		__raw_writew(PBC_BCTRL1_LCDON, PBC_BCTRL1_SET_REG);
	else
		__raw_writew(PBC_BCTRL1_LCDON, PBC_BCTRL1_CLEAR_REG);
}