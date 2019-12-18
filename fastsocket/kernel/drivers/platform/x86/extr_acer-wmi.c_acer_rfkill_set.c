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
typedef  unsigned long u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  set_u32 (int,unsigned long) ; 

__attribute__((used)) static int acer_rfkill_set(void *data, bool blocked)
{
	acpi_status status;
	u32 cap = (unsigned long)data;
	status = set_u32(!blocked, cap);
	if (ACPI_FAILURE(status))
		return -ENODEV;
	return 0;
}