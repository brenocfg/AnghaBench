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
struct modctl {scalar_t__ mod_address; scalar_t__ mod_size; scalar_t__ mod_loaded; int /*<<< orphan*/  mod_modname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int FALSE ; 
 scalar_t__ LIT_STRNEQL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MOD_FBT_DONE (struct modctl*) ; 
 int TRUE ; 
 scalar_t__ ignore_fbt_blacklist ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

int
fbt_module_excluded(struct modctl* ctl)
{
	ASSERT(!MOD_FBT_DONE(ctl));

	if (ctl->mod_address == 0 || ctl->mod_size == 0) {
		return TRUE;
	}

	if (ctl->mod_loaded == 0) {
	        return TRUE;
	}

        /*
	 * If the user sets this, trust they know what they are doing.
	 */
	if (ignore_fbt_blacklist)
		return FALSE;

	/*
	 * These drivers control low level functions that when traced
	 * cause problems often in the sleep/wake paths as well as
	 * critical debug and panic paths.
	 * If somebody really wants to drill in on one of these kexts, then
	 * they can override blacklisting using the boot-arg above.
	 */

#ifdef __x86_64__
	if (strstr(ctl->mod_modname, "AppleACPIEC") != NULL)
		return TRUE;

	if (strstr(ctl->mod_modname, "AppleACPIPlatform") != NULL)
		return TRUE;

	if (strstr(ctl->mod_modname, "AppleRTC") != NULL)
		return TRUE;

	if (strstr(ctl->mod_modname, "IOACPIFamily") != NULL)
		return TRUE;

	if (strstr(ctl->mod_modname, "AppleIntelCPUPowerManagement") != NULL)
		return TRUE;

	if (strstr(ctl->mod_modname, "AppleProfile") != NULL)
		return TRUE;

	if (strstr(ctl->mod_modname, "AppleIntelProfile") != NULL)
		return TRUE;

	if (strstr(ctl->mod_modname, "AppleEFI") != NULL)
		return TRUE;

#elif __arm__ || __arm64__
	if (LIT_STRNEQL(ctl->mod_modname, "com.apple.driver.AppleARMPlatform") ||
	LIT_STRNEQL(ctl->mod_modname, "com.apple.driver.AppleARMPL192VIC") ||
	LIT_STRNEQL(ctl->mod_modname, "com.apple.driver.AppleInterruptController"))
		return TRUE;
#endif

	return FALSE;
}