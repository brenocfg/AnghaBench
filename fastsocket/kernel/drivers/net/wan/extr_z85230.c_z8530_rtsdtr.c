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
struct z8530_channel {int* regs; } ;

/* Variables and functions */
 int DTR ; 
 int /*<<< orphan*/  R5 ; 
 int RTS ; 
 int /*<<< orphan*/  write_zsreg (struct z8530_channel*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void z8530_rtsdtr(struct z8530_channel *c, int set)
{
	if (set)
		c->regs[5] |= (RTS | DTR);
	else
		c->regs[5] &= ~(RTS | DTR);
	write_zsreg(c, R5, c->regs[5]);
}