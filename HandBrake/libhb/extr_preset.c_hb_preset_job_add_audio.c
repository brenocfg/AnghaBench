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
typedef  int /*<<< orphan*/  const hb_value_t ;
typedef  int /*<<< orphan*/  const hb_value_array_t ;
struct TYPE_4__ {int /*<<< orphan*/  list_audio; } ;
typedef  TYPE_1__ hb_title_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;
typedef  int /*<<< orphan*/  const hb_dict_t ;

/* Variables and functions */
 int HB_MUX_INVALID ; 
 scalar_t__ HB_VALUE_TYPE_STRING ; 
 int /*<<< orphan*/  add_audio_for_lang (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_1__*,int,int,int,char const*,int,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* get_audio_copy_mask (int /*<<< orphan*/  const*,int*) ; 
 int get_job_mux (int /*<<< orphan*/  const*) ; 
 int hb_audio_encoder_get_from_name (char const*) ; 
 int /*<<< orphan*/  hb_dict_free (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  const* hb_dict_get (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  const* hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hb_error (char*,...) ; 
 TYPE_1__* hb_find_title_by_index (int /*<<< orphan*/ *,int) ; 
 scalar_t__ hb_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* hb_value_array_get (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* hb_value_array_init () ; 
 int hb_value_array_len (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* hb_value_dup (int /*<<< orphan*/  const*) ; 
 int hb_value_get_bool (int /*<<< orphan*/  const*) ; 
 int hb_value_get_int (int /*<<< orphan*/  const*) ; 
 char* hb_value_get_string (int /*<<< orphan*/  const*) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 scalar_t__ validate_audio_encoders (int /*<<< orphan*/  const*) ; 

int hb_preset_job_add_audio(hb_handle_t *h, int title_index,
                            const hb_dict_t *preset, hb_dict_t *job_dict)
{
    hb_title_t *title = hb_find_title_by_index(h, title_index);
    if (title == NULL)
    {
        // Can't create audio track list without knowing source audio tracks
        hb_error("Invalid title index (%d)", title_index);
        return -1;
    }
    if (hb_list_count(title->list_audio) <= 0)
    {
        // Source has no audio
        return 0;
    }

    int mux = get_job_mux(job_dict);
    if (mux == HB_MUX_INVALID)
    {
        return -1;
    }

    hb_dict_t *audio_dict = hb_dict_get(job_dict, "Audio");
    if (audio_dict == NULL)
    {
        audio_dict = hb_dict_init();
        hb_dict_set(job_dict, "Audio", audio_dict);
    }
    int copy_mask;
    hb_value_t *copy_mask_array = get_audio_copy_mask(preset, &copy_mask);
    if (copy_mask_array == NULL)
    {
        return -1;
    }
    int fallback = 0;
    hb_dict_set(audio_dict, "CopyMask", copy_mask_array);
    hb_value_t *fallback_value = hb_dict_get(preset, "AudioEncoderFallback");
    if (fallback_value != NULL)
    {
        hb_dict_set(audio_dict, "FallbackEncoder",
                    hb_value_dup(fallback_value));
        if (hb_value_type(fallback_value) == HB_VALUE_TYPE_STRING)
        {
            const char * s = hb_value_get_string(fallback_value);
            fallback = hb_audio_encoder_get_from_name(s);
            if (fallback == 0)
            {
                hb_error("Invalid fallback audio codec (%s)", s);
                return -1;
            }
        }
        else
        {
            fallback = hb_value_get_int(fallback_value);
        }
    }
    if (validate_audio_encoders(preset) < 0)
        return -1;

    hb_value_array_t *list = hb_dict_get(audio_dict, "AudioList");
    if (list == NULL)
    {
        list = hb_value_array_init();
        hb_dict_set(audio_dict, "AudioList", list);
    }

    int behavior = 1;   // default first
    const char *s;
    s = hb_value_get_string(hb_dict_get(preset, "AudioTrackSelectionBehavior"));
    if (s != NULL)
    {
        if      (!strcasecmp(s, "none"))
            return 0;
        else if (!strcasecmp(s, "all"))
            behavior = 2;
    }

    // Create hash that is used to track which tracks have been already added
    // We do not want to add the same track with the same settings twice
    hb_dict_t *track_dict = hb_dict_init();

    // Add tracks for all languages in the language list
    int mode;
    hb_value_array_t *lang_list = hb_dict_get(preset, "AudioLanguageList");
    mode = hb_value_get_bool(hb_dict_get(preset, "AudioSecondaryEncoderMode"));
    int count = hb_value_array_len(lang_list);
    int ii;
    for (ii = 0; ii < count; ii++)
    {
        const char *lang;
        lang = hb_value_get_string(hb_value_array_get(lang_list, ii));
        add_audio_for_lang(list, preset, title, mux, copy_mask, fallback,
                           lang, behavior, mode, track_dict);
    }
    // If AudioLanguageList is empty, try "any" language option
    if (count <= 0)
    {
        add_audio_for_lang(list, preset, title, mux, copy_mask, fallback,
                           "any", behavior, mode, track_dict);
    }
    hb_dict_free(&track_dict);
    return 0;
}