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
typedef  int /*<<< orphan*/  ia64_vector ;

/* Variables and functions */
 int IA64_NUM_VECTORS ; 

ia64_vector sn_irq_to_vector(int irq)
{
	if (irq >= IA64_NUM_VECTORS)
		return 0;
	return (ia64_vector)irq;
}