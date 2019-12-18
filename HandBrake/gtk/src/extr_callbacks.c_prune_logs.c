#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct stat {int st_mtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  prefs; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GDir ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_TEST_IS_DIR ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_read_name (int /*<<< orphan*/ *) ; 
 scalar_t__ g_file_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_stat (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_user_config_dir (char*) ; 
 int /*<<< orphan*/  ghb_preview_cleanup (TYPE_1__*) ; 
 int ghb_settings_combo_int (int /*<<< orphan*/ ,char*) ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prune_logs(signal_user_data_t *ud)
{
    gchar *dest_dir;
    gint days;

    // Only prune logs stored in the default config dir location
    days = ghb_settings_combo_int(ud->prefs, "LogLongevity");
    if (days > 365)
        return;

    dest_dir = ghb_get_user_config_dir("EncodeLogs");
    if (g_file_test(dest_dir, G_FILE_TEST_IS_DIR))
    {
        const gchar *file;
        gint duration = days * 24 * 60 * 60;

        GDir *gdir = g_dir_open(dest_dir, 0, NULL);
        time_t now;

        now = time(NULL);
        file = g_dir_read_name(gdir);
        while (file)
        {
            gchar *path;
            struct stat stbuf;

            path = g_strdup_printf("%s/%s", dest_dir, file);
            g_stat(path, &stbuf);
            if (now - stbuf.st_mtime > duration)
            {
                g_unlink(path);
            }
            g_free(path);
            file = g_dir_read_name(gdir);
        }
        g_dir_close(gdir);
    }
    g_free(dest_dir);
    ghb_preview_cleanup(ud);
}