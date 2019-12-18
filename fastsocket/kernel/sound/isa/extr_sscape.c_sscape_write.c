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
struct soundscape {int /*<<< orphan*/  lock; int /*<<< orphan*/  io_base; } ;
typedef  enum GA_REG { ____Placeholder_GA_REG } GA_REG ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sscape_write_unsafe (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void sscape_write(struct soundscape *s, enum GA_REG reg, unsigned char val)
{
	unsigned long flags;

	spin_lock_irqsave(&s->lock, flags);
	sscape_write_unsafe(s->io_base, reg, val);
	spin_unlock_irqrestore(&s->lock, flags);
}