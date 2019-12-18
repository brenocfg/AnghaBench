#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * prefs; int /*<<< orphan*/  globals; int /*<<< orphan*/ * settings; int /*<<< orphan*/  settings_array; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  hb_title_t ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ghb_array_replace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_dict_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ghb_load_settings (TYPE_1__*) ; 
 int /*<<< orphan*/ * ghb_lookup_title (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * ghb_queue_edit_settings ; 
 int /*<<< orphan*/ * last_scan_file ; 
 int /*<<< orphan*/  load_all_titles (TYPE_1__*,int) ; 
 int /*<<< orphan*/  prune_logs (TYPE_1__*) ; 
 int /*<<< orphan*/  show_scan_progress (TYPE_1__*) ; 
 int /*<<< orphan*/  start_scan (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void
ghb_do_scan(
    signal_user_data_t *ud,
    const gchar *filename,
    gint title_id,
    gboolean force)
{
    int titleindex;
    const hb_title_t *title;

    (void)title; // Silence "unused variable" warning

    g_debug("ghb_do_scan()");
    if (!force && last_scan_file != NULL &&
        strcmp(last_scan_file, filename) == 0)
    {
        if (ghb_queue_edit_settings != NULL)
        {
            title_id = ghb_dict_get_int(ghb_queue_edit_settings, "title");
            title = ghb_lookup_title(title_id, &titleindex);
            ghb_array_replace(ud->settings_array, titleindex,
                              ghb_queue_edit_settings);
            ud->settings = ghb_queue_edit_settings;
            ghb_load_settings(ud);
            ghb_queue_edit_settings = NULL;
        }
        else
        {
            title = ghb_lookup_title(title_id, &titleindex);
            load_all_titles(ud, titleindex);
        }
        return;
    }
    if (last_scan_file != NULL)
        g_free(last_scan_file);
    last_scan_file = NULL;
    if (filename != NULL)
    {
        const gchar *path;
        gint preview_count;

        last_scan_file = g_strdup(filename);
        ghb_dict_set_string(ud->globals, "scan_source", filename);

        show_scan_progress(ud);
        path = ghb_dict_get_string(ud->globals, "scan_source");
        prune_logs(ud);

        preview_count = ghb_dict_get_int(ud->prefs, "preview_count");
        start_scan(ud, path, title_id, preview_count);
    }
}