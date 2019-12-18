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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 char* ghb_value_get_string (int /*<<< orphan*/ *) ; 

void
ghb_subtitle_set_pref_lang(GhbValue *settings)
{
    GhbValue *lang_list;
    gboolean set = FALSE;
    lang_list = ghb_dict_get_value(settings, "SubtitleLanguageList");
    if (ghb_array_len(lang_list) > 0)
    {
        GhbValue *glang = ghb_array_get(lang_list, 0);
        if (glang != NULL)
        {
            ghb_dict_set_string(settings, "PreferredLanguage",
                                    ghb_value_get_string(glang));
            set = TRUE;
        }
    }
    if (!set)
    {
        ghb_dict_set_string(settings, "PreferredLanguage", "und");
    }
}