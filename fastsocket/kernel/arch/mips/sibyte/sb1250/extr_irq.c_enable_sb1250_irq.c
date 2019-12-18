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
 int /*<<< orphan*/ * sb1250_irq_owner ; 
 int /*<<< orphan*/  sb1250_unmask_irq (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void enable_sb1250_irq(unsigned int irq)
{
	sb1250_unmask_irq(sb1250_irq_owner[irq], irq);
}