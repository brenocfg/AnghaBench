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
typedef  int uint64_t ;
struct TYPE_2__ {int hard_int; } ;

/* Variables and functions */
 unsigned int CRIME_IRQ_BASE ; 
 TYPE_1__* crime ; 
 int /*<<< orphan*/  crime_disable_irq (unsigned int) ; 

__attribute__((used)) static void crime_edge_mask_and_ack_irq(unsigned int irq)
{
	unsigned int bit = irq - CRIME_IRQ_BASE;
	uint64_t crime_int;

	/* Edge triggered interrupts must be cleared. */

	crime_int = crime->hard_int;
	crime_int &= ~(1 << bit);
	crime->hard_int = crime_int;

	crime_disable_irq(irq);
}