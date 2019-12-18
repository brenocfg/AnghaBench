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

/* Variables and functions */
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  mn10300_cpu_pic_level ; 
 int /*<<< orphan*/  set_irq_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void set_intr_postackable(int irq)
{
	set_irq_chip_and_handler(irq, &mn10300_cpu_pic_level,
				 handle_level_irq);
}