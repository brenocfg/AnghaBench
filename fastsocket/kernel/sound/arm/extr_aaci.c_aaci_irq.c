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
typedef  int u32 ;
struct aaci {int /*<<< orphan*/  lock; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ AACI_ALLINTS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  aaci_fifo_irq (struct aaci*,int,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t aaci_irq(int irq, void *devid)
{
	struct aaci *aaci = devid;
	u32 mask;
	int i;

	spin_lock(&aaci->lock);
	mask = readl(aaci->base + AACI_ALLINTS);
	if (mask) {
		u32 m = mask;
		for (i = 0; i < 4; i++, m >>= 7) {
			if (m & 0x7f) {
				aaci_fifo_irq(aaci, i, m);
			}
		}
	}
	spin_unlock(&aaci->lock);

	return mask ? IRQ_HANDLED : IRQ_NONE;
}