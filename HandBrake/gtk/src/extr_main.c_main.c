#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ stderr_src_id; struct TYPE_8__* current_dvd_device; struct TYPE_8__* extra_activity_path; int /*<<< orphan*/ * activity_buffer; int /*<<< orphan*/ * queue_activity_buffer; int /*<<< orphan*/ * extra_activity_buffer; int /*<<< orphan*/ * builder; int /*<<< orphan*/ * activity_log; int /*<<< orphan*/  globals; int /*<<< orphan*/  prefs; int /*<<< orphan*/  settings_array; int /*<<< orphan*/  queue; int /*<<< orphan*/  app; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_9__ {void* _file; } ;
typedef  int /*<<< orphan*/  GCallback ;

/* Variables and functions */
 int /*<<< orphan*/  ATTACH_PARENT_PROCESS ; 
 scalar_t__ AllocConsole () ; 
 scalar_t__ AttachConsole (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GETTEXT_PACKAGE ; 
 int /*<<< orphan*/  G_APPLICATION (int /*<<< orphan*/ ) ; 
 int G_APPLICATION_HANDLES_OPEN ; 
 int G_APPLICATION_NON_UNIQUE ; 
 int /*<<< orphan*/  PACKAGE_LOCALE_DIR ; 
 void* STDERR_FILENO ; 
 void* STDOUT_FILENO ; 
 int /*<<< orphan*/  _putenv_s (char*,char*) ; 
 int /*<<< orphan*/  bind_textdomain_codeset (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (void*) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  freopen (char*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  g_application_add_main_option_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_application_add_option_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_application_run (int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_io_channel_unref (int /*<<< orphan*/ *) ; 
 TYPE_1__* g_malloc0 (int) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  g_source_remove (scalar_t__) ; 
 scalar_t__ ghb_activate_cb ; 
 int /*<<< orphan*/  ghb_backend_close () ; 
 scalar_t__ ghb_open_file_cb ; 
 int /*<<< orphan*/  ghb_resource_free () ; 
 int /*<<< orphan*/  ghb_settings_close () ; 
 int /*<<< orphan*/  ghb_ui_register_resource () ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_init_get_option_group () ; 
 int /*<<< orphan*/  gtk_application_new (char*,int) ; 
 TYPE_2__* stderr ; 
 TYPE_2__* stdout ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 scalar_t__ win32_console ; 

int
main(int argc, char *argv[])
{
#if defined(_WIN32)
    // Tell gdk pixbuf where it's loader config file is.
    _putenv_s("GDK_PIXBUF_MODULE_FILE", "ghb.exe.local/loaders.cache");
    _putenv_s("GST_PLUGIN_PATH", "lib/gstreamer-1.0");
#endif


#ifdef ENABLE_NLS
    bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);
#endif

#if defined(_WIN32)
    if (win32_console)
    {
        // Enable console logging
        if(AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()){
            close(STDOUT_FILENO);
            freopen("CONOUT$", "w", stdout);
            close(STDERR_FILENO);
            freopen("CONOUT$", "w", stderr);
        }
    }
    else
    {
        // Non-console windows apps do not have a stderr->_file
        // assigned properly
        stderr->_file = STDERR_FILENO;
        stdout->_file = STDOUT_FILENO;
    }
#endif

    int                  status;
    signal_user_data_t * ud;

    ghb_ui_register_resource();
    ud = g_malloc0(sizeof(signal_user_data_t));
    ud->app = gtk_application_new("fr.handbrake.ghb",
                                  G_APPLICATION_NON_UNIQUE |
                                  G_APPLICATION_HANDLES_OPEN);
    // Connect application signals
    g_signal_connect(ud->app, "activate", (GCallback)ghb_activate_cb, ud);
    g_signal_connect(ud->app, "open", (GCallback)ghb_open_file_cb, ud);
    // Set application options
    g_application_add_main_option_entries(G_APPLICATION(ud->app), entries);
#if defined(_ENABLE_GST)
    g_application_add_option_group(G_APPLICATION(ud->app),
                                   gst_init_get_option_group());
#endif
    status = g_application_run(G_APPLICATION(ud->app), argc, argv);

    ghb_backend_close();

    // Remove stderr redirection
    if (ud->stderr_src_id > 0)
        g_source_remove(ud->stderr_src_id);
    ghb_value_free(&ud->queue);
    ghb_value_free(&ud->settings_array);
    ghb_value_free(&ud->prefs);
    ghb_value_free(&ud->globals);

    if (ud->activity_log != NULL)
        g_io_channel_unref(ud->activity_log);
    ghb_settings_close();
    ghb_resource_free();

    if (ud->builder != NULL)
        g_object_unref(ud->builder);

    g_object_unref(ud->extra_activity_buffer);
    g_object_unref(ud->queue_activity_buffer);
    g_object_unref(ud->activity_buffer);
    g_free(ud->extra_activity_path);

    g_free(ud->current_dvd_device);
    g_free(ud);

    return status;
}