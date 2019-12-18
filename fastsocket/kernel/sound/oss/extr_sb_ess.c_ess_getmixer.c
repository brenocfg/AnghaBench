#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int /*<<< orphan*/  MIXER_ADDR ; 
 int /*<<< orphan*/  MIXER_DATA ; 
 unsigned int ess_read (TYPE_1__*,unsigned int) ; 
 unsigned int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

unsigned int ess_getmixer (sb_devc * devc, unsigned int port)
{
	unsigned int val;
	unsigned long flags;

	spin_lock_irqsave(&devc->lock, flags);

	if (port >= 0xa0) {
		val = ess_read (devc, port);
	} else {
		outb(((unsigned char) (port & 0xff)), MIXER_ADDR);

		udelay(20);
		val = inb(MIXER_DATA);
		udelay(20);
	}
	spin_unlock_irqrestore(&devc->lock, flags);

	return val;
}