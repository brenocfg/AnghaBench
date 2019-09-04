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
 int /*<<< orphan*/  kPEPanicRestartCPU ; 
 int /*<<< orphan*/  kdp_machine_reboot_type (int /*<<< orphan*/ ) ; 

void
kdp_machine_reboot(void)
{
	kdp_machine_reboot_type(kPEPanicRestartCPU);
}