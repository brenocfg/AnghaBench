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
struct tea5764_regs {int tnctrl; int /*<<< orphan*/  testreg; } ;
struct tea5764_device {struct tea5764_regs regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEA5764_TESTREG_TRIGFR ; 
 int TEA5764_TNCTRL_AFM ; 
 int TEA5764_TNCTRL_HLSI ; 
 int TEA5764_TNCTRL_MU ; 
 int TEA5764_TNCTRL_PUPD0 ; 
 int /*<<< orphan*/  tea5764_i2c_write (struct tea5764_device*) ; 
 int /*<<< orphan*/  use_xtal ; 

__attribute__((used)) static void tea5764_power_up(struct tea5764_device *radio)
{
	struct tea5764_regs *r = &radio->regs;

	if (!(r->tnctrl & TEA5764_TNCTRL_PUPD0)) {
		r->tnctrl &= ~(TEA5764_TNCTRL_AFM | TEA5764_TNCTRL_MU |
			       TEA5764_TNCTRL_HLSI);
		if (!use_xtal)
			r->testreg |= TEA5764_TESTREG_TRIGFR;
		else
			r->testreg &= ~TEA5764_TESTREG_TRIGFR;

		r->tnctrl |= TEA5764_TNCTRL_PUPD0;
		tea5764_i2c_write(radio);
	}
}