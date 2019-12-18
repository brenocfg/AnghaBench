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
struct ewma {scalar_t__ internal; void* factor; void* weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* ilog2 (unsigned long) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 

void ewma_init(struct ewma *avg, unsigned long factor, unsigned long weight)
{
	WARN_ON(!is_power_of_2(weight) || !is_power_of_2(factor));

	avg->weight = ilog2(weight);
	avg->factor = ilog2(factor);
	avg->internal = 0;
}