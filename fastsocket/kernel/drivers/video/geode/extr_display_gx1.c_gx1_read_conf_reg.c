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

/* Variables and functions */
 int CONFIG_CCR3 ; 
 int CONFIG_CCR3_MAPEN ; 
 int /*<<< orphan*/  gx1_conf_reg_lock ; 
 int inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u8 gx1_read_conf_reg(u8 reg)
{
	u8 val, ccr3;
	unsigned long flags;

	spin_lock_irqsave(&gx1_conf_reg_lock, flags);

	outb(CONFIG_CCR3, 0x22);
	ccr3 = inb(0x23);
	outb(CONFIG_CCR3, 0x22);
	outb(ccr3 | CONFIG_CCR3_MAPEN, 0x23);
	outb(reg, 0x22);
	val = inb(0x23);
	outb(CONFIG_CCR3, 0x22);
	outb(ccr3, 0x23);

	spin_unlock_irqrestore(&gx1_conf_reg_lock, flags);

	return val;
}