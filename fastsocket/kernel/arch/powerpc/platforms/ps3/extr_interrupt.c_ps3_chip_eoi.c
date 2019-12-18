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
struct ps3_private {int /*<<< orphan*/  thread_id; int /*<<< orphan*/  ppe_id; } ;

/* Variables and functions */
 struct ps3_private* get_irq_chip_data (unsigned int) ; 
 int /*<<< orphan*/  lv1_end_of_interrupt_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ps3_chip_eoi(unsigned int virq)
{
	const struct ps3_private *pd = get_irq_chip_data(virq);
	lv1_end_of_interrupt_ext(pd->ppe_id, pd->thread_id, virq);
}