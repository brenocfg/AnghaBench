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
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  cmos_handle ; 

__attribute__((used)) static int issue_thinkpad_cmos_command(int cmos_cmd)
{
	if (!cmos_handle)
		return -ENXIO;

	if (!acpi_evalf(cmos_handle, NULL, NULL, "vd", cmos_cmd))
		return -EIO;

	return 0;
}