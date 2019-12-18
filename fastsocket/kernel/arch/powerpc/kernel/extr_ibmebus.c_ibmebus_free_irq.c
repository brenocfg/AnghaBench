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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (unsigned int,void*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (unsigned int) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ibmebus_free_irq(u32 ist, void *dev_id)
{
	unsigned int irq = irq_find_mapping(NULL, ist);

	free_irq(irq, dev_id);
	irq_dispose_mapping(irq);
}