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
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf_get_configname () ; 
 int /*<<< orphan*/ * conf_message_callback ; 
 int /*<<< orphan*/  conf_parse (char*) ; 
 int /*<<< orphan*/  conf_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf_set_message_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* getenv (char*) ; 
 int handle_exit () ; 
 scalar_t__ init_dialog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rootmenu ; 
 int /*<<< orphan*/  set_config_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sig_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int silent ; 
 int single_menu_mode ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 

int main(int ac, char **av)
{
	char *mode;
	int res;

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	signal(SIGINT, sig_handler);

	if (ac > 1 && strcmp(av[1], "-s") == 0) {
		silent = 1;
		/* Silence conf_read() until the real callback is set up */
		conf_set_message_callback(NULL);
		av++;
	}
	conf_parse(av[1]);
	conf_read(NULL);

	mode = getenv("MENUCONFIG_MODE");
	if (mode) {
		if (!strcasecmp(mode, "single_menu"))
			single_menu_mode = 1;
	}

	if (init_dialog(NULL)) {
		fprintf(stderr, N_("Your display is too small to run Menuconfig!\n"));
		fprintf(stderr, N_("It must be at least 19 lines by 80 columns.\n"));
		return 1;
	}

	set_config_filename(conf_get_configname());
	conf_set_message_callback(conf_message_callback);
	do {
		conf(&rootmenu, NULL);
		res = handle_exit();
	} while (res == KEY_ESC);

	return res;
}