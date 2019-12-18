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
struct address_info {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unload_mpu401 (struct address_info*) ; 
 int /*<<< orphan*/  unload_uart401 (struct address_info*) ; 

void unload_sbmpu(struct address_info *hw_config)
{
#if defined(CONFIG_SOUND_MPU401)
	if (!strcmp (hw_config->name, "ESS1xxx MPU")) {
		unload_mpu401(hw_config);
		return;
	}
#endif
	unload_uart401(hw_config);
}