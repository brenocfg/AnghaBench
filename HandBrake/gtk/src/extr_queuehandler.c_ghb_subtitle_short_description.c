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
struct TYPE_3__ {char* native_name; char* eng_name; } ;
typedef  TYPE_1__ iso639_lang_t ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  const GhbValue ;

/* Variables and functions */
 int IMPORTSRT ; 
 int IMPORTSSA ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 char* g_strdup_printf (char*,char const*,...) ; 
 int /*<<< orphan*/  const* ghb_dict_get (int /*<<< orphan*/  const*,char*) ; 
 void* ghb_dict_get_string (int /*<<< orphan*/  const*,char*) ; 
 TYPE_1__* lang_lookup (char const*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

char *
ghb_subtitle_short_description(const GhbValue *subsource,
                               const GhbValue *subsettings)
{
    GhbValue *import;
    char *desc = NULL;

    import = ghb_dict_get(subsettings, "Import");
    if (import != NULL)
    {
        const gchar * format = "SRT";
        const gchar * code;
        const gchar * lang;
        int           source = IMPORTSRT;
        const iso639_lang_t *iso;

        format = ghb_dict_get_string(import, "Format");
        lang   = ghb_dict_get_string(import, "Language");
        code   = ghb_dict_get_string(import, "Codeset");

        if (format != NULL && !strcasecmp(format, "SSA"))
        {
            source = IMPORTSSA;
        }
        iso = lang_lookup(lang);
        if (iso != NULL)
        {
            if (iso->native_name != NULL)
                lang = iso->native_name;
            else
                lang = iso->eng_name;
        }

        if (source == IMPORTSRT)
        {
            desc = g_strdup_printf("%s (%s)(%s)", lang, code, format);
        }
        else
        {
            desc = g_strdup_printf("%s (%s)", lang, format);
        }
    }
    else if (subsource == NULL)
    {
        desc = g_strdup(_("Foreign Audio Scan"));
    }
    else
    {
        const char * lang = ghb_dict_get_string(subsource, "Language");
        desc = g_strdup_printf("%s", lang);
    }

    return desc;
}