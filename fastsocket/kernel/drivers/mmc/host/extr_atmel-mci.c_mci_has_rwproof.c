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
 scalar_t__ cpu_is_at91rm9200 () ; 
 scalar_t__ cpu_is_at91sam9261 () ; 

__attribute__((used)) static bool mci_has_rwproof(void)
{
	if (cpu_is_at91sam9261() || cpu_is_at91rm9200())
		return false;
	else
		return true;
}