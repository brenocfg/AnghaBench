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
typedef  int /*<<< orphan*/  u16 ;
struct bt431_regs {int /*<<< orphan*/  addr_hi; int /*<<< orphan*/  addr_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt431_set_value (int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void bt431_select_reg(struct bt431_regs *regs, int ir)
{
	/*
	 * The compiler splits the write in two bytes without these
	 * helper variables.
	 */
	volatile u16 *lo = &(regs->addr_lo);
	volatile u16 *hi = &(regs->addr_hi);

	mb();
	*lo = bt431_set_value(ir & 0xff);
	wmb();
	*hi = bt431_set_value((ir >> 8) & 0xff);
}