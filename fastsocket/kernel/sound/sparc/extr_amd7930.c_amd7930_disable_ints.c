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
struct snd_amd7930 {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ AMD7930_CR ; 
 scalar_t__ AMD7930_DR ; 
 int AMR_INIT ; 
 int AM_INIT_ACTIVE ; 
 int AM_INIT_DISABLE_INTS ; 
 int /*<<< orphan*/  sbus_writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __inline__ void amd7930_disable_ints(struct snd_amd7930 *amd)
{
	unsigned long flags;

	spin_lock_irqsave(&amd->lock, flags);
	sbus_writeb(AMR_INIT, amd->regs + AMD7930_CR);
	sbus_writeb(AM_INIT_ACTIVE | AM_INIT_DISABLE_INTS, amd->regs + AMD7930_DR);
	spin_unlock_irqrestore(&amd->lock, flags);
}