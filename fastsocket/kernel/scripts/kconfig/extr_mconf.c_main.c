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
 int KEY_ESC ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 char* N_ (char*) ; 
 int /*<<< orphan*/  PACKAGE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf (int /*<<< orphan*/ *) ; 
 scalar_t__ conf_get_changed () ; 
 int /*<<< orphan*/  conf_get_configname () ; 
 int /*<<< orphan*/  conf_parse (char*) ; 
 int /*<<< orphan*/  conf_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dialog_clear () ; 
 int dialog_yesno (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  end_dialog (int,int) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ init_dialog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initscr () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rootmenu ; 
 int /*<<< orphan*/  set_config_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int single_menu_mode ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 

int main(int ac, char **av)
{
	int saved_x, saved_y;
	char *mode;
	int res;

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	conf_parse(av[1]);
	conf_read(NULL);

	mode = getenv("MENUCONFIG_MODE");
	if (mode) {
		if (!strcasecmp(mode, "single_menu"))
			single_menu_mode = 1;
	}

	initscr();

	getyx(stdscr, saved_y, saved_x);
	if (init_dialog(NULL)) {
		fprintf(stderr, N_("Your display is too small to run Menuconfig!\n"));
		fprintf(stderr, N_("It must be at least 19 lines by 80 columns.\n"));
		return 1;
	}

	set_config_filename(conf_get_configname());
	do {
		conf(&rootmenu);
		dialog_clear();
		if (conf_get_changed())
			res = dialog_yesno(NULL,
					   _("Do you wish to save your "
					     "new kernel configuration?\n"
					     "<ESC><ESC> to continue."),
					   6, 60);
		else
			res = -1;
	} while (res == KEY_ESC);
	end_dialog(saved_x, saved_y);

	switch (res) {
	case 0:
		if (conf_write(filename)) {
			fprintf(stderr, _("\n\n"
				"Error during writing of the kernel configuration.\n"
				"Your kernel configuration changes were NOT saved."
				"\n\n"));
			return 1;
		}
	case -1:
		printf(_("\n\n"
			"*** End of Linux kernel configuration.\n"
			"*** Execute 'make' to build the kernel or try 'make help'."
			"\n\n"));
		break;
	default:
		fprintf(stderr, _("\n\n"
			"Your kernel configuration changes were NOT saved."
			"\n\n"));
	}

	return 0;
}