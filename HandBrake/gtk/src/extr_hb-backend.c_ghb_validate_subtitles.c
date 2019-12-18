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
typedef  int /*<<< orphan*/  hb_title_t ;
struct TYPE_3__ {int format; } ;
typedef  TYPE_1__ hb_container_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkWindow ;
typedef  int /*<<< orphan*/  const GhbValue ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GTK_MESSAGE_WARNING ; 
 int /*<<< orphan*/  G_FILE_TEST_IS_REGULAR ; 
 int HB_MUX_MASK_WEBM ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  g_file_test (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_strdup_printf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* ghb_array_get (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ghb_dict_get (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ ghb_dict_get_bool (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ ghb_dict_get_int (int /*<<< orphan*/  const*,char*) ; 
 void* ghb_dict_get_string (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  const* ghb_get_job_subtitle_list (int /*<<< orphan*/  const*) ; 
 TYPE_1__* ghb_lookup_container_by_name (char const*) ; 
 int /*<<< orphan*/ * ghb_lookup_title (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ghb_message_dialog (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

gboolean
ghb_validate_subtitles(GhbValue *settings, GtkWindow *parent)
{
    gint title_id, titleindex;
    const hb_title_t * title;
    gchar *message;

    title_id = ghb_dict_get_int(settings, "title");
    title = ghb_lookup_title(title_id, &titleindex);
    if (title == NULL)
    {
        /* No valid title, stop right there */
        g_message(_("No title found.\n"));
        return FALSE;
    }

    const GhbValue *slist, *subtitle, *import;
    gint count, ii, track;
    gboolean burned, one_burned = FALSE;

    const char *mux_id;
    const hb_container_t *mux;

    mux_id = ghb_dict_get_string(settings, "FileFormat");
    mux = ghb_lookup_container_by_name(mux_id);

    slist = ghb_get_job_subtitle_list(settings);
    count = ghb_array_len(slist);
    for (ii = 0; ii < count; ii++)
    {
        subtitle = ghb_array_get(slist, ii);
        track = ghb_dict_get_int(subtitle, "Track");
        import = ghb_dict_get(subtitle, "Import");
        burned = track != -1 && ghb_dict_get_bool(subtitle, "Burn");
        if (burned && one_burned)
        {
            // MP4 can only handle burned vobsubs.  make sure there isn't
            // already something burned in the list
            message = g_strdup_printf(
            _("Only one subtitle may be burned into the video.\n\n"
                "You should change your subtitle selections.\n"
                "If you continue, some subtitles will be lost."));
            if (!ghb_message_dialog(parent, GTK_MESSAGE_WARNING,
                                    message, _("Cancel"), _("Continue")))
            {
                g_free(message);
                return FALSE;
            }
            g_free(message);
            break;
        }
        else if (burned)
        {
            one_burned = TRUE;
        }
        else if (mux->format & HB_MUX_MASK_WEBM)
        {
            // WebM can only handle burned subs afaik. Their specs are ambiguous here
            message = g_strdup_printf(
            _("WebM in HandBrake only supports burned subtitles.\n\n"
                "You should change your subtitle selections.\n"
                "If you continue, some subtitles will be lost."));
            if (!ghb_message_dialog(parent, GTK_MESSAGE_WARNING,
                                    message, _("Cancel"), _("Continue")))
            {
                g_free(message);
                return FALSE;
            }
            g_free(message);
            break;
        }
        if (import != NULL)
        {
            const gchar *filename;

            filename = ghb_dict_get_string(import, "Filename");
            if (!g_file_test(filename, G_FILE_TEST_IS_REGULAR))
            {
                message = g_strdup_printf(
                _("SRT file does not exist or not a regular file.\n\n"
                    "You should choose a valid file.\n"
                    "If you continue, this subtitle will be ignored."));
                if (!ghb_message_dialog(parent, GTK_MESSAGE_WARNING, message,
                    _("Cancel"), _("Continue")))
                {
                    g_free(message);
                    return FALSE;
                }
                g_free(message);
                break;
            }
        }
    }
    return TRUE;
}