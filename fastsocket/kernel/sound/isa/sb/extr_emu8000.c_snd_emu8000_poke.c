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
struct snd_emu8000 {unsigned int last_reg; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 unsigned int EMU8000_PTR (struct snd_emu8000*) ; 
 int /*<<< orphan*/  outw (unsigned short,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_emu8000_poke(struct snd_emu8000 *emu, unsigned int port, unsigned int reg, unsigned int val)
{
	unsigned long flags;
	spin_lock_irqsave(&emu->reg_lock, flags);
	if (reg != emu->last_reg) {
		outw((unsigned short)reg, EMU8000_PTR(emu)); /* Set register */
		emu->last_reg = reg;
	}
	outw((unsigned short)val, port); /* Send data */
	spin_unlock_irqrestore(&emu->reg_lock, flags);
}