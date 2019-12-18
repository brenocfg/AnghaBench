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
typedef  size_t UINT ;

/* Variables and functions */
 size_t NUM_KERNEL_STATUS ; 
 int /*<<< orphan*/  OSUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kernel_status_lock ; 

void UnlockKernelStatus(UINT id)
{
	// Validate arguments
	if (id >= NUM_KERNEL_STATUS)
	{
		return;
	}

	OSUnlock(kernel_status_lock[id]);
}