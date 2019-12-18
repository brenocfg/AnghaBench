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
struct tg3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_irq_quiesce (struct tg3*) ; 

__attribute__((used)) static inline void tg3_full_lock(struct tg3 *tp, int irq_sync)
{
	spin_lock_bh(&tp->lock);
	if (irq_sync)
		tg3_irq_quiesce(tp);
}