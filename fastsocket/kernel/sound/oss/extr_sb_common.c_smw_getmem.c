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
typedef  int /*<<< orphan*/  sb_devc ;

/* Variables and functions */
 unsigned char inb (int) ; 
 int /*<<< orphan*/  jazz16_lock ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned char smw_getmem(sb_devc * devc, int base, int addr)
{
	unsigned long flags;
	unsigned char val;

	spin_lock_irqsave(&jazz16_lock, flags);  /* NOT the SB card? */

	outb((addr & 0xff), base + 1);	/* Low address bits */
	outb((addr >> 8), base + 2);	/* High address bits */
	val = inb(base);	/* Data */

	spin_unlock_irqrestore(&jazz16_lock, flags);
	return val;
}