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
struct TYPE_3__ {int /*<<< orphan*/ * prefs; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  char const gchar ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int IMPORTSRT ; 
 int TRUE ; 
 int /*<<< orphan*/  g_free (char const*) ; 
 char* g_strdup_printf (char*,char const*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_dict_new () ; 
 int /*<<< orphan*/  ghb_dict_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ghb_dict_set_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ghb_dict_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * ghb_get_title_subtitle_track (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_subtitle_can_pass (int,int) ; 
 int /*<<< orphan*/  subtitle_add_to_settings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GhbValue*  subtitle_add_track(
    signal_user_data_t *ud,
    GhbValue *settings,
    int track,
    int mux,
    gboolean default_track,
    gboolean import,
    int source,
    gboolean burn,
    gboolean *burned)
{
    const char * name = NULL;
    if (track >= 0 && !import)
    {
        GhbValue * strack;

        strack = ghb_get_title_subtitle_track(settings, track);
        source = ghb_dict_get_int(strack, "Source");
        name   = ghb_dict_get_string(strack, "Name");
    }

    burn |= !hb_subtitle_can_pass(source, mux);

    if (*burned && burn)
    {
        // Can only burn one.  Skip others that must be burned.
        return NULL;
    }

    GhbValue *subsettings = ghb_dict_new();
    if (import)
    {
        // Set default SRT settings
        GhbValue *import_dict;
        const gchar *pref_lang, *dir;
        gchar *filename;

        import_dict = ghb_dict_new();
        hb_dict_set(subsettings, "Import", import_dict);

        ghb_dict_set_string(import_dict, "Format",
                            source == IMPORTSRT ? "SRT" : "SSA");
        pref_lang = ghb_dict_get_string(settings, "PreferredLanguage");
        ghb_dict_set_string(import_dict, "Language", pref_lang);
        ghb_dict_set_string(import_dict, "Codeset", "UTF-8");

        dir = ghb_dict_get_string(ud->prefs, "SrtDir");
        filename = g_strdup_printf("%s/none", dir);
        ghb_dict_set_string(import_dict, "Filename", filename);
        g_free(filename);
    }

    if (name != NULL && name[0] != 0)
    {
        ghb_dict_set_string(subsettings, "Name", name);
    }
    ghb_dict_set_int(subsettings, "Track", track);
    ghb_dict_set_int(subsettings, "Offset", 0);
    ghb_dict_set_bool(subsettings, "Forced", track == -1);
    ghb_dict_set_bool(subsettings, "Default", default_track);
    ghb_dict_set_bool(subsettings, "Burn", burn);
    if (burn && track != -1)
    {
        // Allow 2 tracks to be marked burned when one is
        // foreign audio search.  Extra burned track will be
        // sanitized away if foreign audio search actually finds
        // something.
        *burned = TRUE;
    }

    subtitle_add_to_settings(settings, subsettings);

    return subsettings;
}