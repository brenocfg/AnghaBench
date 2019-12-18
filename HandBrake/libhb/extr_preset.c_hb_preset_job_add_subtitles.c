#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct subtitle_behavior_s {int one; int burn_foreign; int make_default; int burn_first; int one_burned; int* used; void* burn_bd; void* burn_dvd; } ;
struct TYPE_12__ {char* iso639_2; } ;
typedef  TYPE_2__ iso639_lang_t ;
typedef  int /*<<< orphan*/  const hb_value_t ;
typedef  int /*<<< orphan*/  const hb_value_array_t ;
struct TYPE_13__ {int /*<<< orphan*/  list_subtitle; int /*<<< orphan*/  list_audio; } ;
typedef  TYPE_3__ hb_title_t ;
struct TYPE_14__ {scalar_t__ source; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ hb_subtitle_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;
typedef  int /*<<< orphan*/  const hb_dict_t ;
struct TYPE_11__ {char* iso639_2; } ;
struct TYPE_15__ {TYPE_1__ lang; } ;
typedef  TYPE_5__ hb_audio_config_t ;

/* Variables and functions */
 scalar_t__ CC608SUB ; 
 scalar_t__ CC708SUB ; 
 int HB_MUX_INVALID ; 
 int /*<<< orphan*/  add_subtitle (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_subtitle_for_lang (int /*<<< orphan*/  const*,TYPE_3__*,int,char const*,struct subtitle_behavior_s*) ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int get_job_mux (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* hb_dict_get (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  const* hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hb_error (char*,int) ; 
 TYPE_3__* hb_find_title_by_index (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* hb_list_audio_config_item (int /*<<< orphan*/ ,int) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_4__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_subtitle_can_pass (scalar_t__,int) ; 
 int /*<<< orphan*/  const* hb_value_array_get (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* hb_value_array_init () ; 
 int hb_value_array_len (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* hb_value_bool (int) ; 
 int hb_value_get_bool (int /*<<< orphan*/  const*) ; 
 void* hb_value_get_int (int /*<<< orphan*/  const*) ; 
 char* hb_value_get_string (int /*<<< orphan*/  const*) ; 
 TYPE_2__* lang_get_any () ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

int hb_preset_job_add_subtitles(hb_handle_t *h, int title_index,
                                const hb_dict_t *preset, hb_dict_t *job_dict)
{
    hb_title_t *title = hb_find_title_by_index(h, title_index);
    if (title == NULL)
    {
        // Can't create subtitle track list without knowing source
        hb_error("Invalid title index (%d)", title_index);
        return -1;
    }

    int mux = get_job_mux(job_dict);
    if (mux == HB_MUX_INVALID)
    {
        return -1;
    }

    // Get the language of the first audio output track
    // Needed for subtitle track selection
    hb_dict_t *audio_dict = hb_dict_get(job_dict, "Audio");
    hb_value_array_t *audio_list = hb_dict_get(audio_dict, "AudioList");
    const char *first_audio_lang = NULL;
    if (hb_value_array_len(audio_list) > 0)
    {
        int track;
        hb_value_t *audio = hb_value_array_get(audio_list, 0);
        track = hb_value_get_int(hb_dict_get(audio, "Track"));
        if (hb_list_count(title->list_audio) > track)
        {
            hb_audio_config_t *aconfig;
            aconfig = hb_list_audio_config_item(title->list_audio, track);
            if (aconfig != NULL)
                first_audio_lang = aconfig->lang.iso639_2;
        }
    }

    int source_subtitle_count = hb_list_count(title->list_subtitle);
    if (source_subtitle_count == 0)
        return 0;

    hb_dict_t *subtitle_dict = hb_dict_get(job_dict, "Subtitle");
    if (subtitle_dict == NULL)
    {
        subtitle_dict = hb_dict_init();
        hb_dict_set(job_dict, "Subtitle", subtitle_dict);
    }
    hb_value_array_t *list = hb_dict_get(subtitle_dict, "SubtitleList");
    if (list == NULL)
    {
        list = hb_value_array_init();
        hb_dict_set(subtitle_dict, "SubtitleList", list);
    }

    int track_behavior = 0;   // default no subtitles
    int burn_behavior = 0;
    int burn_foreign;

    struct subtitle_behavior_s behavior;
    behavior.one = 0;
    behavior.burn_foreign = 0;
    behavior.make_default = 0;
    behavior.burn_first = 0;
    behavior.burn_dvd = 0;
    behavior.burn_bd = 0;
    behavior.one_burned = 0;
    // Create array that is used to track which tracks have been already added
    // We do not want to add the same track with the same settings twice
    behavior.used = calloc(source_subtitle_count, sizeof(*behavior.used));

    // Since this function can be called multiple times, we need to
    // initialize the "used" array from the existing subtitles in the list.
    int count, ii;
    count = hb_value_array_len(list);
    for (ii = 0; ii < count; ii++)
    {
        hb_value_t *sub = hb_value_array_get(list, ii);
        int track = hb_value_get_int(hb_dict_get(sub, "Track"));
        behavior.used[track] = 1;
    }

    const char *s;
    s = hb_value_get_string(hb_dict_get(preset,
                                        "SubtitleTrackSelectionBehavior"));
    if (s != NULL)
    {
        if      (!strcasecmp(s, "first"))
            track_behavior = 1;
        else if (!strcasecmp(s, "all"))
            track_behavior = 2;
    }

    s = hb_value_get_string(hb_dict_get(preset, "SubtitleBurnBehavior"));
    if (s != NULL)
    {
        if      (!strcasecmp(s, "foreign"))
            burn_behavior = 1;
        else if (!strcasecmp(s, "first"))
            burn_behavior = 2;
        else if (!strcasecmp(s, "foreign_first"))
            burn_behavior = 3;
    }

    behavior.burn_dvd = hb_value_get_int(hb_dict_get(preset,
                                                     "SubtitleBurnDVDSub"));
    behavior.burn_bd  = hb_value_get_int(hb_dict_get(preset,
                                                     "SubtitleBurnBDSub"));

    burn_foreign        = burn_behavior == 1 || burn_behavior == 3;
    behavior.burn_first = burn_behavior == 2 || burn_behavior == 3;

    int foreign_audio_search, foreign_first_audio;
    foreign_audio_search = hb_value_get_bool(hb_dict_get(preset,
                                            "SubtitleAddForeignAudioSearch"));
    foreign_first_audio  = hb_value_get_bool(hb_dict_get(preset,
                                            "SubtitleAddForeignAudioSubtitle"));


    // Add tracks for all languages in the language list
    hb_value_array_t * lang_list = hb_dict_get(preset, "SubtitleLanguageList");
    const iso639_lang_t * lang_any  = lang_get_any();
    const char          * pref_lang = lang_any->iso639_2;

    count = hb_value_array_len(lang_list);
    if (count > 0)
    {
        pref_lang = hb_value_get_string(hb_value_array_get(lang_list, 0));
    }
    if (!strcmp(pref_lang, lang_any->iso639_2))
    {
        if (first_audio_lang != NULL)
        {
            pref_lang = first_audio_lang;
            foreign_first_audio = 0;
        }
        else
        {
            foreign_audio_search = foreign_first_audio = 0;
        }
    }

    int track;
    if (first_audio_lang != NULL &&
        foreign_first_audio && strncmp(first_audio_lang, pref_lang, 4))
    {
        // First audio lang does not match the preferred subittle lang.
        // Preset says to add pref lang subtitle.
        // Foreign audio search is not necessary since entire audio track
        // is foreign.
        foreign_audio_search = 0;
        behavior.one = 1;
        behavior.burn_foreign = burn_foreign;
        behavior.make_default = 1;
        add_subtitle_for_lang(list, title, mux, pref_lang, &behavior);
    }

    hb_dict_t *search_dict = hb_dict_get(subtitle_dict, "Search");
    if (search_dict == NULL)
    {
        search_dict = hb_dict_init();
        hb_dict_set(subtitle_dict, "Search", search_dict);
    }
    if (first_audio_lang != NULL &&
        foreign_audio_search && !strncmp(first_audio_lang, pref_lang, 4))
    {
        // First audio lang matches the preferred subtitle lang.
        // Preset says to add search for foreign audio subtitles.
        int burn = burn_foreign || behavior.burn_first;
        // If not burning, make this the default track.
        hb_dict_set(search_dict, "Enable", hb_value_bool(1));
        hb_dict_set(search_dict, "Default", hb_value_bool(!burn));
        hb_dict_set(search_dict, "Forced", hb_value_bool(1));
        hb_dict_set(search_dict, "Burn", hb_value_bool(burn));
    }
    else
    {
        hb_dict_set(search_dict, "Enable", hb_value_bool(0));
    }

    if (track_behavior > 0)
    {
        int ii;
        behavior.one = track_behavior == 1;
        behavior.burn_foreign = 0;
        behavior.make_default = 0;
        for (ii = 0; ii < count; ii++)
        {
            const char *lang;
            lang = hb_value_get_string(hb_value_array_get(lang_list, ii));
            add_subtitle_for_lang(list, title, mux, lang, &behavior);
        }
        if (count <= 0)
        {
            // No matching language.  Try "Unknown" language
            add_subtitle_for_lang(list, title, mux, "und", &behavior);
        }
    }

    if (hb_value_get_bool(hb_dict_get(preset, "SubtitleAddCC")))
    {
        // Add Closed Caption track
        for (track = 0; track < source_subtitle_count; track++)
        {
            if (behavior.used[track])
            {
                continue;
            }
            hb_subtitle_t *subtitle = hb_list_item(title->list_subtitle, track);
            if (subtitle->source == CC608SUB || subtitle->source == CC708SUB)
            {
                int burn;
                burn = !behavior.one_burned &&
                       (!hb_subtitle_can_pass(subtitle->source, mux) ||
                        behavior.burn_first);
                behavior.used[track] = 1;
                behavior.one_burned |= burn;
                add_subtitle(list, track, 0 /*default*/, 0 /*!force*/, burn,
                             subtitle->name);
                break;
            }
        }
    }
    free(behavior.used);

    return 0;
}