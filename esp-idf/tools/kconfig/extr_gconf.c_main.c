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
typedef  int /*<<< orphan*/  gchar ;

/* Variables and functions */
#define  FULL_VIEW 130 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  PACKAGE ; 
#define  SINGLE_VIEW 129 
#define  SPLIT_VIEW 128 
 int /*<<< orphan*/  SRCTREE ; 
 int /*<<< orphan*/  bind_textdomain_codeset (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf_parse (char const*) ; 
 int /*<<< orphan*/  conf_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf_set_message_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_list () ; 
 int /*<<< orphan*/  display_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_tree_part () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixup_rootmenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_get_current_dir () ; 
 int /*<<< orphan*/ * g_strconcat (char*,char*,char*,...) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glade_init () ; 
 int /*<<< orphan*/  gtk_init (int*,char***) ; 
 int /*<<< orphan*/  gtk_main () ; 
 int /*<<< orphan*/  gtk_set_locale () ; 
 int /*<<< orphan*/  init_left_tree () ; 
 int /*<<< orphan*/  init_main_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_right_tree () ; 
 int /*<<< orphan*/  init_tree_model () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  rootmenu ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 int view_mode ; 

int main(int ac, char *av[])
{
	const char *name;
	char *env;
	gchar *glade_file;

	bindtextdomain(PACKAGE, LOCALEDIR);
	bind_textdomain_codeset(PACKAGE, "UTF-8");
	textdomain(PACKAGE);

	/* GTK stuffs */
	gtk_set_locale();
	gtk_init(&ac, &av);
	glade_init();

	//add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");
	//add_pixmap_directory (PACKAGE_SOURCE_DIR "/pixmaps");

	/* Determine GUI path */
	env = getenv(SRCTREE);
	if (env)
		glade_file = g_strconcat(env, "/scripts/kconfig/gconf.glade", NULL);
	else if (av[0][0] == '/')
		glade_file = g_strconcat(av[0], ".glade", NULL);
	else
		glade_file = g_strconcat(g_get_current_dir(), "/", av[0], ".glade", NULL);

	/* Conf stuffs */
	if (ac > 1 && av[1][0] == '-') {
		switch (av[1][1]) {
		case 'a':
			//showAll = 1;
			break;
		case 's':
			conf_set_message_callback(NULL);
			break;
		case 'h':
		case '?':
			printf("%s [-s] <config>\n", av[0]);
			exit(0);
		}
		name = av[2];
	} else
		name = av[1];

	conf_parse(name);
	fixup_rootmenu(&rootmenu);
	conf_read(NULL);

	/* Load the interface and connect signals */
	init_main_window(glade_file);
	init_tree_model();
	init_left_tree();
	init_right_tree();

	switch (view_mode) {
	case SINGLE_VIEW:
		display_tree_part();
		break;
	case SPLIT_VIEW:
		display_list();
		break;
	case FULL_VIEW:
		display_tree(&rootmenu);
		break;
	}

	gtk_main();

	return 0;
}