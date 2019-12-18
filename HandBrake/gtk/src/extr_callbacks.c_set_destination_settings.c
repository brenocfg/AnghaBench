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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * globals; int /*<<< orphan*/ * prefs; int /*<<< orphan*/ * settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  const* const* const* const* const* gint ;
typedef  int /*<<< orphan*/  const* const* const* const* gchar ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_FILE_TEST_IS_DIR ; 
 int /*<<< orphan*/  W_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 scalar_t__ g_file_test (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_path_get_dirname (int /*<<< orphan*/  const* const* const* const* const*) ; 
 int /*<<< orphan*/  g_string_append_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  const* const* const***** g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (char*) ; 
 int /*<<< orphan*/  const* const* const***** get_creation_date (char*,int /*<<< orphan*/  const* const* const*****,int /*<<< orphan*/  const* const* const* const* const*) ; 
 int /*<<< orphan*/  const* const* const***** get_extension (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 double ghb_dict_get_double (int /*<<< orphan*/ *,char*) ; 
 void* ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  const* const* const***** ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_get_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_dict_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ ghb_settings_combo_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  const* const* const***** ghb_settings_video_encoder_codec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_value_dup (int /*<<< orphan*/ ) ; 
 char* hb_video_quality_get_name (int /*<<< orphan*/  const* const* const* const* const*) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_unique_dest (int /*<<< orphan*/  const* const* const* const* const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const* const* const* const* const*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/  const* const* const* const* const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_destination_settings(signal_user_data_t *ud, GhbValue *settings)
{
    const gchar *extension, *dest_file, *dest_dir;
    gchar *filename;

    extension = get_extension(ud, settings);

    g_debug("set_destination_settings");
    dest_file = ghb_dict_get_string(ud->settings, "dest_file");
    if (dest_file == NULL)
    {
        // Initialize destination filename if it has no value yet.
        // If auto-naming is disabled, this will be the default filename.
        GString *str = g_string_new("");
        const gchar *vol_name;
        vol_name = ghb_dict_get_string(settings, "volume");
        g_string_append_printf(str, "%s", vol_name);
        g_string_append_printf(str, ".%s", extension);
        filename = g_string_free(str, FALSE);
        ghb_dict_set_string(settings, "dest_file", filename);
        g_free(filename);
    }
    ghb_dict_set(settings, "dest_dir", ghb_value_dup(
                 ghb_dict_get_value(ud->prefs, "destination_dir")));
    if (ghb_dict_get_bool(ud->prefs, "auto_name"))
    {
        GString *str = g_string_new("");
        const gchar *p;

        p = ghb_dict_get_string(ud->prefs, "auto_name_template");
        // {source-path} is only allowed as the first element of the
        // template since the path must come first in the filename
        if (p != NULL &&
            (!strncasecmp(p, "{source-path}", strlen("{source-path}")) ||
             !strncasecmp(p, "{source_path}", strlen("{source_path}"))))
        {
            const gchar * source;

            source = ghb_dict_get_string(ud->globals, "scan_source");
            if (source != NULL)
            {
                char * dirname = g_path_get_dirname(source);
                // if dirname is a directory and it is writable...
                if (dirname != NULL &&
                    g_file_test(dirname, G_FILE_TEST_IS_DIR) &&
                    access(dirname, W_OK) == 0)
                {
                    ghb_dict_set_string(settings, "dest_dir", dirname);
                }
                g_free(dirname);
            }
            p += strlen("{source-path}");
        }
        while (*p)
        {
            if (!strncasecmp(p, "{source}", strlen("{source}")))
            {
                const gchar *vol_name;
                vol_name = ghb_dict_get_string(settings, "volume");
                g_string_append_printf(str, "%s", vol_name);
                p += strlen("{source}");
            }
            else if (!strncasecmp(p, "{title}", strlen("{title}")))
            {
                gint title = ghb_dict_get_int(settings, "title");
                if (title >= 0)
                    g_string_append_printf(str, "%d", title);
                p += strlen("{title}");
            }
            else if (!strncasecmp(p, "{preset}", strlen("{preset}")))
            {
                const gchar *preset_name;
                preset_name = ghb_dict_get_string(settings, "PresetName");
                g_string_append_printf(str, "%s", preset_name);
                p += strlen("{preset}");
            }
            else if (!strncasecmp(p, "{chapters}", strlen("{chapters}")))
            {
                if (ghb_settings_combo_int(settings, "PtoPType") == 0)
                {
                    gint start, end;
                    start = ghb_dict_get_int(settings, "start_point");
                    end = ghb_dict_get_int(settings, "end_point");
                    if (start == end)
                        g_string_append_printf(str, "%d", start);
                    else
                        g_string_append_printf(str, "%d-%d", start, end);
                }
                p += strlen("{chapters}");
            }
            else if (!strncasecmp(p, "{time}", strlen("{time}")))
            {
                char st[6];
                struct tm *lt;
                time_t t = time(NULL);
                lt = localtime(&t);
                st[0] = 0;
                strftime(st, 6, "%H:%M", lt);
                g_string_append_printf(str, "%s", st);
                p += strlen("{time}");
            }
            else if (!strncasecmp(p, "{date}", strlen("{date}")))
            {
                char dt[11];
                struct tm *lt;
                time_t t = time(NULL);
                lt = localtime(&t);
                dt[0] = 0;
                strftime(dt, 11, "%Y-%m-%d", lt);
                g_string_append_printf(str, "%s", dt);
                p += strlen("{date}");
            }
            else if (!strncasecmp(p, "{creation-date}", strlen("{creation-date}")))
            {
                gchar *val;
                const gchar *source = ghb_dict_get_string(ud->globals, "scan_source");
                val = get_creation_date("%Y-%m-%d", ghb_dict_get_string(settings, "MetaReleaseDate"), source);
                g_string_append_printf(str, "%s", val);
                p += strlen("{creation-date}");
                g_free(val);
            }
            else if (!strncasecmp(p, "{creation-time}", strlen("{creation-time}")))
            {
                gchar *val;
                const gchar *source = ghb_dict_get_string(ud->globals, "scan_source");
                val = get_creation_date("%H:%M", ghb_dict_get_string(settings, "MetaReleaseDate"), source);
                g_string_append_printf(str, "%s", val);
                p += strlen("{creation-time}");
                g_free(val);
            }
            else if (!strncasecmp(p, "{quality}", strlen("{quality}")))
            {
                if (ghb_dict_get_bool(settings, "vquality_type_constant"))
                {
                    gint vcodec;
                    const char *vqname;
                    double vquality;
                    vcodec = ghb_settings_video_encoder_codec(settings, "VideoEncoder");
                    vqname = hb_video_quality_get_name(vcodec);
                    vquality = ghb_dict_get_double(settings, "VideoQualitySlider");
                    g_string_append_printf(str, "%s%.3g", vqname, vquality);
                }
                p += strlen("{quality}");
            }
            else if (!strncasecmp(p, "{bitrate}", strlen("{bitrate}")))
            {
                if (ghb_dict_get_bool(settings, "vquality_type_bitrate"))
                {
                    int vbitrate;
                    vbitrate = ghb_dict_get_int(settings, "VideoAvgBitrate");
                    g_string_append_printf(str, "%dkbps", vbitrate);
                }
                p += strlen("{bitrate}");
            }
            else
            {
                g_string_append_printf(str, "%c", *p);
                p++;
            }
        }
        dest_dir = ghb_dict_get_string(settings, "dest_dir");
        make_unique_dest(dest_dir, str, extension);
        g_string_append_printf(str, ".%s", extension);
        filename = g_string_free(str, FALSE);
        ghb_dict_set_string(settings, "dest_file", filename);
        g_free(filename);
    }
}