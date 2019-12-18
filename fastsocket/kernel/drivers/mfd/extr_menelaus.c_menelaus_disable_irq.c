#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mask2; int mask1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENELAUS_INT_MASK1 ; 
 int /*<<< orphan*/  MENELAUS_INT_MASK2 ; 
 int menelaus_write_reg (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* the_menelaus ; 

__attribute__((used)) static int menelaus_disable_irq(int irq)
{
	if (irq > 7) {
		irq -= 8;
		the_menelaus->mask2 |= (1 << irq);
		return menelaus_write_reg(MENELAUS_INT_MASK2,
				the_menelaus->mask2);
	} else {
		the_menelaus->mask1 |= (1 << irq);
		return menelaus_write_reg(MENELAUS_INT_MASK1,
				the_menelaus->mask1);
	}
}