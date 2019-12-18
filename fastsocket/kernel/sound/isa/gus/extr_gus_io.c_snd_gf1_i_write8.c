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
struct snd_gus_card {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __snd_gf1_write8 (struct snd_gus_card*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_gf1_i_write8(struct snd_gus_card * gus,
		      unsigned char reg,
                      unsigned char data)
{
	unsigned long flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	__snd_gf1_write8(gus, reg, data);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
}