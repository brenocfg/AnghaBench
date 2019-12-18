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
 int /*<<< orphan*/  GIUINTENL ; 
 int GPIO_PIN_OF_IRQ (unsigned int) ; 
 int /*<<< orphan*/  giu_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void unmask_giuint_low(unsigned int irq)
{
	giu_set(GIUINTENL, 1 << GPIO_PIN_OF_IRQ(irq));
}