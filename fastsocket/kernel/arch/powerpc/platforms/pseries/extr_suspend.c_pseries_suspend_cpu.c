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
 int rtas_suspend_cpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  suspend_data ; 
 scalar_t__ suspending ; 

int pseries_suspend_cpu(void)
{
	if (suspending)
		return rtas_suspend_cpu(&suspend_data);
	return 0;
}