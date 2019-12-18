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
struct sonicvibes {unsigned char format; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  INDEX ; 
 int SV_IREG_DMA_DATA_FMT ; 
 int SV_MCE ; 
 int /*<<< orphan*/  SV_REG (struct sonicvibes*,int /*<<< orphan*/ ) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_sonicvibes_setfmt(struct sonicvibes * sonic,
                                  unsigned char mask,
                                  unsigned char value)
{
	unsigned long flags;

	spin_lock_irqsave(&sonic->reg_lock, flags);
	outb(SV_MCE | SV_IREG_DMA_DATA_FMT, SV_REG(sonic, INDEX));
	if (mask) {
		sonic->format = inb(SV_REG(sonic, DATA));
		udelay(10);
	}
	sonic->format = (sonic->format & mask) | value;
	outb(sonic->format, SV_REG(sonic, DATA));
	udelay(10);
	outb(0, SV_REG(sonic, INDEX));
	udelay(10);
	spin_unlock_irqrestore(&sonic->reg_lock, flags);
}