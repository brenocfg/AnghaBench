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
struct sscape_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODIE_ADDR ; 
 int /*<<< orphan*/  ODIE_DATA ; 
 int /*<<< orphan*/  PORT (int /*<<< orphan*/ ) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned char sscape_read(struct sscape_info *devc, int reg)
{
	unsigned long flags;
	unsigned char val;

	spin_lock_irqsave(&devc->lock,flags);
	outb(reg, PORT(ODIE_ADDR));
	val = inb(PORT(ODIE_DATA));
	spin_unlock_irqrestore(&devc->lock,flags);
	return val;
}