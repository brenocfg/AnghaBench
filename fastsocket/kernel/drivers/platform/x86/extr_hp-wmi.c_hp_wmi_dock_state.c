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
 int /*<<< orphan*/  HPWMI_HARDWARE_QUERY ; 
 int hp_wmi_perform_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hp_wmi_dock_state(void)
{
	int ret = hp_wmi_perform_query(HPWMI_HARDWARE_QUERY, 0, 0);

	if (ret < 0)
		return ret;

	return ret & 0x1;
}