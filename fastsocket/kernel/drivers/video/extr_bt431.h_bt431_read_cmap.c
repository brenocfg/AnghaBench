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
struct bt431_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt431_read_cmap_inc (struct bt431_regs*) ; 
 int /*<<< orphan*/  bt431_select_reg (struct bt431_regs*,int) ; 

__attribute__((used)) static inline u16 bt431_read_cmap(struct bt431_regs *regs, int cr)
{
	bt431_select_reg(regs, cr);
	return bt431_read_cmap_inc(regs);
}