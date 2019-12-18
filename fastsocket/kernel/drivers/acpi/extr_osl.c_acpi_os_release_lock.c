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
typedef  int /*<<< orphan*/  acpi_spinlock ;
typedef  int /*<<< orphan*/  acpi_cpu_flags ;

/* Variables and functions */
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void acpi_os_release_lock(acpi_spinlock lockp, acpi_cpu_flags flags)
{
	spin_unlock_irqrestore(lockp, flags);
}