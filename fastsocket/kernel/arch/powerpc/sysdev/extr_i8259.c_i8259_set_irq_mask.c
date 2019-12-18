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
 int /*<<< orphan*/  cached_21 ; 
 int /*<<< orphan*/  cached_A1 ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i8259_set_irq_mask(int irq_nr)
{
	outb(cached_A1,0xA1);
	outb(cached_21,0x21);
}