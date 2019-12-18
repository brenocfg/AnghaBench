#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  hb_title_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  const gchar ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkWindow ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_MESSAGE_ERROR ; 
 int /*<<< orphan*/  GTK_MESSAGE_QUESTION ; 
 int /*<<< orphan*/ * GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FILE_TEST_EXISTS ; 
 int /*<<< orphan*/  G_FILE_TEST_IS_DIR ; 
 int R_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int W_OK ; 
 int /*<<< orphan*/ * _ (char*) ; 
 scalar_t__ g_access (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ g_file_test (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* g_path_get_dirname (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* g_strdup_printf (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_unlink (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  const* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_lookup_title (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ghb_message_dialog (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_validate_audio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_validate_filters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_validate_subtitles (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_validate_video (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static gboolean
validate_settings(signal_user_data_t *ud, GhbValue *settings, gint batch)
{
    // Check to see if the dest file exists or is
    // already in the queue
    gchar *message;
    const gchar *dest;
    gint count, ii;
    gint title_id, titleindex;
    const hb_title_t *title;
    GtkWindow *hb_window;

    hb_window = GTK_WINDOW(GHB_WIDGET(ud->builder, "hb_window"));

    title_id = ghb_dict_get_int(settings, "title");
    title = ghb_lookup_title(title_id, &titleindex);
    if (title == NULL) return FALSE;
    dest = ghb_dict_get_string(settings, "destination");
    count = ghb_array_len(ud->queue);
    for (ii = 0; ii < count; ii++)
    {
        GhbValue *queueDict, *uiDict;
        const gchar *filename;

        queueDict = ghb_array_get(ud->queue, ii);
        uiDict = ghb_dict_get(queueDict, "uiSettings");
        filename = ghb_dict_get_string(uiDict, "destination");
        if (strcmp(dest, filename) == 0)
        {
            message = g_strdup_printf(
                        _("Destination: %s\n\n"
                        "Another queued job has specified the same destination.\n"
                        "Do you want to overwrite?"),
                        dest);
            if (!ghb_message_dialog(hb_window, GTK_MESSAGE_QUESTION,
                                    message, _("Cancel"), _("Overwrite")))
            {
                g_free(message);
                return FALSE;
            }
            g_free(message);
            break;
        }
    }
    gchar *destdir = g_path_get_dirname(dest);
    if (!g_file_test(destdir, G_FILE_TEST_IS_DIR))
    {
        message = g_strdup_printf(
                    _("Destination: %s\n\n"
                    "This is not a valid directory."),
                    destdir);
        ghb_message_dialog(hb_window, GTK_MESSAGE_ERROR,
                           message, _("Cancel"), NULL);
        g_free(message);
        g_free(destdir);
        return FALSE;
    }
#if !defined(_WIN32)
    // This doesn't work properly on windows
    if (g_access(destdir, R_OK|W_OK) != 0)
    {
        message = g_strdup_printf(
                    _("Destination: %s\n\n"
                    "Can not read or write the directory."),
                    destdir);
        ghb_message_dialog(hb_window, GTK_MESSAGE_ERROR,
                           message, _("Cancel"), NULL);
        g_free(message);
        g_free(destdir);
        return FALSE;
    }
#endif
    g_free(destdir);
    if (g_file_test(dest, G_FILE_TEST_EXISTS))
    {
        message = g_strdup_printf(
                    _("Destination: %s\n\n"
                    "File already exists.\n"
                    "Do you want to overwrite?"),
                    dest);
        if (!ghb_message_dialog(hb_window, GTK_MESSAGE_QUESTION,
                                message, _("Cancel"), _("Overwrite")))
        {
            g_free(message);
            return FALSE;
        }
        g_free(message);
        g_unlink(dest);
    }
    // Validate audio settings
    if (!ghb_validate_audio(settings, hb_window))
    {
        return FALSE;
    }
    // Validate audio settings
    if (!ghb_validate_subtitles(settings, hb_window))
    {
        return FALSE;
    }
    // Validate video settings
    if (!ghb_validate_video(settings, hb_window))
    {
        return FALSE;
    }
    // Validate filter settings
    if (!ghb_validate_filters(settings, hb_window))
    {
        return FALSE;
    }
    return TRUE;
}