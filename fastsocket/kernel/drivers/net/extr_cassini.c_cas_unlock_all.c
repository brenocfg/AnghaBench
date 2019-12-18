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
struct cas {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cas_unlock_tx (struct cas*) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cas_unlock_all(struct cas *cp)
{
	cas_unlock_tx(cp);
	spin_unlock_irq(&cp->lock);
}