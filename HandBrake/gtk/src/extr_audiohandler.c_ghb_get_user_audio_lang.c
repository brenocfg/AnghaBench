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
typedef  int /*<<< orphan*/  hb_title_t ;
typedef  int /*<<< orphan*/  gint ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_get_job_audio_list (int /*<<< orphan*/ *) ; 
 char* ghb_get_source_audio_lang (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

const gchar*
ghb_get_user_audio_lang(GhbValue *settings, const hb_title_t *title, gint track)
{
    GhbValue *audio_list, *asettings;
    const gchar *lang;

    audio_list = ghb_get_job_audio_list(settings);
    if (ghb_array_len(audio_list) <= track)
        return "und";
    asettings = ghb_array_get(audio_list, track);
    track = ghb_dict_get_int(asettings, "Track");
    lang = ghb_get_source_audio_lang(title, track);
    return lang;
}