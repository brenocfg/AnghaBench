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
 int /*<<< orphan*/  TICKCMP_IRQ_BIT ; 
 int /*<<< orphan*/  __hbird_write_compare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hbtick_disable_irq(void)
{
	__hbird_write_compare(TICKCMP_IRQ_BIT);
}