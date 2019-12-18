#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  hb_title_t ;
struct TYPE_4__ {int /*<<< orphan*/  codec; } ;
struct TYPE_5__ {TYPE_1__ in; } ;
typedef  TYPE_2__ hb_audio_config_t ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ghb_get_audio_info (int /*<<< orphan*/  const*,int) ; 
 int ghb_get_copy_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_lookup_title (int,int /*<<< orphan*/ *) ; 
 int ghb_select_audio_codec (int,int /*<<< orphan*/ ,int,int,int) ; 
 int ghb_select_fallback (int /*<<< orphan*/ *,int) ; 
 int ghb_settings_audio_encoder_codec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_audio_encoder_get_short_name (int) ; 
 int hb_container_get_from_name (char const*) ; 
 int /*<<< orphan*/  hb_sanitize_audio_settings (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ghb_sanitize_audio_settings(GhbValue *settings, GhbValue *asettings)
{
    // Sanitize codec
    const char        * mux_name;
    int                 title_id, mux, acodec, fallback, copy_mask, track;
    uint32_t            in_codec = 0;
    hb_audio_config_t * aconfig;
    const hb_title_t  * title;

    title_id = ghb_dict_get_int(settings, "title");
    title    = ghb_lookup_title(title_id, NULL);

    mux_name  = ghb_dict_get_string(settings, "FileFormat");
    mux       = hb_container_get_from_name(mux_name);

    acodec    = ghb_settings_audio_encoder_codec(asettings, "Encoder");
    fallback  = ghb_select_fallback(settings, acodec);
    copy_mask = ghb_get_copy_mask(settings);
    track     = ghb_dict_get_int(asettings, "Track");
    aconfig   = ghb_get_audio_info(title, track);
    if (aconfig != NULL)
    {
        in_codec = aconfig->in.codec;
    }
    acodec    = ghb_select_audio_codec(mux, in_codec, acodec,
                                       fallback, copy_mask);
    ghb_dict_set_string(asettings, "Encoder",
                        hb_audio_encoder_get_short_name(acodec));

    // Sanitize the rest
    hb_sanitize_audio_settings(title, asettings);
}