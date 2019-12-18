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
 int /*<<< orphan*/  EEEPC_EC_FAN_HRPM ; 
 int /*<<< orphan*/  EEEPC_EC_FAN_LRPM ; 
 int /*<<< orphan*/  read_acpi_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int eeepc_get_fan_rpm(void)
{
	int high = 0;
	int low = 0;

	read_acpi_int(NULL, EEEPC_EC_FAN_HRPM, &high);
	read_acpi_int(NULL, EEEPC_EC_FAN_LRPM, &low);
	return (high << 8 | low);
}