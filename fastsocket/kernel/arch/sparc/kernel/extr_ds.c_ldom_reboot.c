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
 int /*<<< orphan*/  ldom_set_var (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  sun4v_mach_sir () ; 

void ldom_reboot(const char *boot_command)
{
	/* Don't bother with any of this if the boot_command
	 * is empty.
	 */
	if (boot_command && strlen(boot_command)) {
		char full_boot_str[256];

		strcpy(full_boot_str, "boot ");
		strcpy(full_boot_str + strlen("boot "), boot_command);

		ldom_set_var("reboot-command", full_boot_str);
	}
	sun4v_mach_sir();
}