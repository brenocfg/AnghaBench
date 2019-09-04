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
 int /*<<< orphan*/  VMX_KPRINTF (char*) ; 
 int /*<<< orphan*/  vmx_off (int /*<<< orphan*/ *) ; 
 scalar_t__ vmx_use_count ; 

void
vmx_suspend()
{
	VMX_KPRINTF("vmx_suspend\n");

	if (vmx_use_count)
		vmx_off(NULL);
}