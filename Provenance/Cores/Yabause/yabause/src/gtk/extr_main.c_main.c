#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_2__ {int cdcoretype; scalar_t__ sndcoretype; void* biospath; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_STDERR ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FILE_TEST_EXISTS ; 
 int /*<<< orphan*/  G_KEY_FILE_NONE ; 
 int /*<<< orphan*/  LogChangeOutput (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogStart () ; 
 int /*<<< orphan*/  LogStop () ; 
 int /*<<< orphan*/  MappedMemoryLoadExec (char*,unsigned int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  YTSDIR ; 
 int /*<<< orphan*/  YUI_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YabauseDeInit () ; 
 int /*<<< orphan*/  YuiLoadState () ; 
 void* biospath ; 
 void* cdpath ; 
 int /*<<< orphan*/ * g_build_filename (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  g_file_get_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_file_set_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ g_file_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_get_user_config_dir () ; 
 int /*<<< orphan*/  g_key_file_get_integer (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_key_file_get_value (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_key_file_load_from_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_key_file_new () ; 
 int /*<<< orphan*/  g_mkdir_with_parents (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_strlcpy (void*,char*,int) ; 
 int /*<<< orphan*/  gtk_gl_init (int*,char***) ; 
 int /*<<< orphan*/  gtk_init (int*,char***) ; 
 int /*<<< orphan*/  gtk_main () ; 
 int /*<<< orphan*/  gtk_window_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * inifile ; 
 int /*<<< orphan*/  keyfile ; 
 int /*<<< orphan*/  mini18n_set_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mini18n_set_locale (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_usage (char*) ; 
 int sscanf (char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 TYPE_1__ yinit ; 
 int /*<<< orphan*/  yui ; 
 int /*<<< orphan*/  yui_new () ; 
 int /*<<< orphan*/  yui_settings_init () ; 
 int /*<<< orphan*/  yui_settings_load () ; 
 int /*<<< orphan*/  yui_window_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_window_set_frameskip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  yui_window_set_fullscreen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_window_start (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
#ifndef NO_CLI
	int i;
	int autostart = 0;
#endif
	LogStart();
	LogChangeOutput( DEBUG_STDERR, NULL );
	inifile = g_build_filename(g_get_user_config_dir(), "yabause", "gtk", "yabause.ini", NULL);

	if (! g_file_test(inifile, G_FILE_TEST_EXISTS)) {
		// no inifile found, but it could be in the old location
		gchar * oldinifile = g_build_filename(g_get_user_config_dir(), "yabause.ini", NULL);

		// we need to create the directory for the new file anyways
		gchar * xdgpath = g_build_filename(g_get_user_config_dir(), "yabause", "gtk", NULL);

		if (! g_file_test(xdgpath, G_FILE_TEST_EXISTS))
			g_mkdir_with_parents(xdgpath, 0755);
		g_free(xdgpath);

		if (g_file_test(oldinifile, G_FILE_TEST_EXISTS)) {
			// ok, we found an old .ini file, let's copy the content
			gchar * data;

			g_file_get_contents(oldinifile, &data, NULL, NULL);
			g_file_set_contents(inifile, data, -1, NULL);
		}

		g_free(oldinifile);
	}
	
	keyfile = g_key_file_new();

	gtk_init(&argc, &argv);
#ifdef HAVE_LIBGTKGLEXT
	gtk_gl_init(&argc, &argv);
#endif

	yui_settings_init();

#ifdef HAVE_LIBMINI18N
	mini18n_set_domain(YTSDIR);
	g_key_file_load_from_file(keyfile, inifile, G_KEY_FILE_NONE, 0);
	mini18n_set_locale(g_key_file_get_value(keyfile, "General", "TranslationPath", NULL));
#endif

	yui = yui_new();

	yui_settings_load();

	gtk_window_move(GTK_WINDOW(yui), g_key_file_get_integer(keyfile, "Gtk", "X", 0), g_key_file_get_integer(keyfile, "Gtk", "Y", 0));

#ifndef NO_CLI
   //handle command line arguments
   for (i = 1; i < argc; ++i) {
      if (argv[i]) {
         //show usage
         if (0 == strcmp(argv[i], "-h") || 0 == strcmp(argv[i], "-?") || 0 == strcmp(argv[i], "--help")) {
            print_usage(argv[0]);
            return 0;
         }
			
         //set bios
         if (0 == strcmp(argv[i], "-b") && argv[i + 1]) {
            g_strlcpy(biospath, argv[i + 1], 256);
            yinit.biospath = biospath;
	 } else if (strstr(argv[i], "--bios=")) {
            g_strlcpy(biospath, argv[i] + strlen("--bios="), 256);
            yinit.biospath = biospath;
	 }
         //set iso
         else if (0 == strcmp(argv[i], "-i") && argv[i + 1]) {
            g_strlcpy(cdpath, argv[i + 1], 256);
	    yinit.cdcoretype = 1;
	 } else if (strstr(argv[i], "--iso=")) {
            g_strlcpy(cdpath, argv[i] + strlen("--iso="), 256);
	    yinit.cdcoretype = 1;
	 }
         //set cdrom
	 else if (0 == strcmp(argv[i], "-c") && argv[i + 1]) {
            g_strlcpy(cdpath, argv[i + 1], 256);
	    yinit.cdcoretype = 2;
	 } else if (strstr(argv[i], "--cdrom=")) {
            g_strlcpy(cdpath, argv[i] + strlen("--cdrom="), 256);
	    yinit.cdcoretype = 2;
	 }
         // Set sound
         else if (strcmp(argv[i], "-ns") == 0 || strcmp(argv[i], "--nosound") == 0) {
	    yinit.sndcoretype = 0;
	 }
	 // Autoload
	 else if (strcmp(argv[i], "--autoload") == 0) {
            yui_window_start(YUI_WINDOW(yui));
            YuiLoadState();
            autostart = 1;
	 }
	 // Autostart
	 else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--autostart") == 0) {
            autostart = 1;
	 }
	 // Fullscreen
	 else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--fullscreen") == 0) {
            yui_window_set_fullscreen(YUI_WINDOW(yui), TRUE);
	 }
         // Auto frame skip
         else if (strstr(argv[i], "--autoframeskip=")) {
            int fscount;
            int fsenable;
            fscount = sscanf(argv[i] + strlen("--autoframeskip="), "%d", &fsenable);
            if (fscount > 0)
               yui_window_set_frameskip(YUI_WINDOW(yui), fsenable);
         }
	 // Binary
	 else if (strstr(argv[i], "--binary=")) {
	    char binname[1024];
	    unsigned int binaddress;
	    int bincount;

	    bincount = sscanf(argv[i] + strlen("--binary="), "%[^:]:%x", binname, &binaddress);
	    if (bincount > 0) {
	       if (bincount < 2) binaddress = 0x06004000;

               yui_window_run(YUI_WINDOW(yui));
	       MappedMemoryLoadExec(binname, binaddress);
	    }
	 }
      }
   }

   if (autostart) yui_window_run(YUI_WINDOW(yui));
#endif

	gtk_main ();

	YabauseDeInit();
	LogStop();

	return 0;
}