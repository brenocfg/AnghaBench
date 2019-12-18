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
struct TYPE_3__ {char* iso639_2; } ;
typedef  TYPE_1__ iso639_lang_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  hb_value_array_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMPORTSRT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int hb_str_vlen (char**) ; 
 scalar_t__ hb_subtitle_can_burn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_bool (int) ; 
 int /*<<< orphan*/ * hb_value_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_value_string (char*) ; 
 TYPE_1__* lang_lookup (char*) ; 
 int srtburn ; 
 char** srtcodeset ; 
 int srtdefault ; 
 char** srtfile ; 
 char** srtlang ; 
 char** srtoffset ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strtoll (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_srt(hb_value_array_t *list, int track, int *one_burned)
{
    char *codeset = "ISO-8859-1";
    int64_t offset = 0;
    char *iso639_2 = "und";
    int burn = !*one_burned && srtburn == track + 1 &&
               hb_subtitle_can_burn(IMPORTSRT);
    *one_burned |= burn;
    int def  = srtdefault == track + 1;

    if (srtcodeset && track < hb_str_vlen(srtcodeset) && srtcodeset[track])
        codeset = srtcodeset[track];
    if (srtoffset && track < hb_str_vlen(srtoffset) && srtoffset[track])
        offset = strtoll(srtoffset[track], NULL, 0);
    if (srtlang && track < hb_str_vlen(srtlang) && srtlang[track])
    {
        const iso639_lang_t *lang = lang_lookup(srtlang[track]);
        if (lang != NULL)
        {
            iso639_2 = lang->iso639_2;
        }
        else
        {
            fprintf(stderr, "Warning: Invalid SRT language (%s)\n",
                    srtlang[track]);
        }
    }

    hb_dict_t *subtitle_dict = hb_dict_init();
    hb_dict_t *srt_dict = hb_dict_init();
    hb_dict_set(subtitle_dict, "Import", srt_dict);
    hb_dict_set(subtitle_dict, "Default", hb_value_bool(def));
    hb_dict_set(subtitle_dict, "Burn", hb_value_bool(burn));
    hb_dict_set(subtitle_dict, "Offset", hb_value_int(offset));
    hb_dict_set(srt_dict, "Format", hb_value_string("SRT"));
    hb_dict_set(srt_dict, "Filename", hb_value_string(srtfile[track]));
    hb_dict_set(srt_dict, "Language", hb_value_string(iso639_2));
    hb_dict_set(srt_dict, "Codeset", hb_value_string(codeset));
    hb_value_array_append(list, subtitle_dict);
    return 0;
}