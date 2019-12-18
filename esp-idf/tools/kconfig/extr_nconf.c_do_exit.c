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
 int KEY_EXIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int btn_dialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  conf_get_changed () ; 
 int conf_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 int global_exit ; 
 int /*<<< orphan*/  main_window ; 

__attribute__((used)) static int do_exit(void)
{
	int res;
	if (!conf_get_changed()) {
		global_exit = 1;
		return 0;
	}
	res = btn_dialog(main_window,
			_("Do you wish to save your new configuration?\n"
				"<ESC> to cancel and resume nconfig."),
			2,
			"   <save>   ",
			"<don't save>");
	if (res == KEY_EXIT) {
		global_exit = 0;
		return -1;
	}

	/* if we got here, the user really wants to exit */
	switch (res) {
	case 0:
		res = conf_write(filename);
		if (res)
			btn_dialog(
				main_window,
				_("Error during writing of configuration.\n"
				  "Your configuration changes were NOT saved."),
				  1,
				  "<OK>");
		break;
	default:
		btn_dialog(
			main_window,
			_("Your configuration changes were NOT saved."),
			1,
			"<OK>");
		break;
	}
	global_exit = 1;
	return 0;
}