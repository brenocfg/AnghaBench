#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  reg_dram; int /*<<< orphan*/  reg_data8; int /*<<< orphan*/  reg_regsel; int /*<<< orphan*/  reg_data16; } ;
struct snd_gus_card {int /*<<< orphan*/  reg_lock; TYPE_1__ gf1; } ;

/* Variables and functions */
 unsigned char SNDRV_GF1_GB_DRAM_IO_HIGH ; 
 unsigned char SNDRV_GF1_GW_DRAM_IO_LOW ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_gf1_poke(struct snd_gus_card * gus, unsigned int addr, unsigned char data)
{
	unsigned long flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	outb(SNDRV_GF1_GW_DRAM_IO_LOW, gus->gf1.reg_regsel);
	mb();
	outw((unsigned short) addr, gus->gf1.reg_data16);
	mb();
	outb(SNDRV_GF1_GB_DRAM_IO_HIGH, gus->gf1.reg_regsel);
	mb();
	outb((unsigned char) (addr >> 16), gus->gf1.reg_data8);
	mb();
	outb(data, gus->gf1.reg_dram);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
}