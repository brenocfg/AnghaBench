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
typedef  int /*<<< orphan*/  gdouble ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  audio_add_to_settings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_dict_new () ; 
 int /*<<< orphan*/  ghb_dict_set_double (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_dict_set_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ghb_dict_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int ghb_get_best_mix (int,int,int) ; 
 int /*<<< orphan*/ * ghb_get_title_audio_track (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ghb_sanitize_audio_settings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char const* hb_audio_encoder_get_short_name (int) ; 
 char const* hb_mixdown_get_short_name (int) ; 

__attribute__((used)) static GhbValue*
audio_add_track(
    GhbValue *settings,
    int track,
    int encoder,
    gdouble quality,
    int bitrate,
    int samplerate,
    int mix,
    gdouble drc,
    gdouble gain)
{
    GhbValue *asettings;
    GhbValue *atrack;

    asettings = ghb_dict_new();

    ghb_dict_set_int(asettings, "Track", track);
    ghb_dict_set_string(asettings, "Encoder",
                        hb_audio_encoder_get_short_name(encoder));
    ghb_dict_set_double(asettings, "Quality", quality);
    ghb_dict_set_int(asettings, "Bitrate", bitrate);
    ghb_dict_set_int(asettings, "Samplerate", samplerate);

    atrack = ghb_get_title_audio_track(settings, track);
    if (atrack != NULL)
    {
        int layout = ghb_dict_get_int(atrack, "ChannelLayout");
        const char * name = ghb_dict_get_string(atrack, "Name");
        mix = ghb_get_best_mix(layout, encoder, mix);
        if (name != NULL)
        {
            ghb_dict_set_string(asettings, "Name", name);
        }
    }
    ghb_dict_set_string(asettings, "Mixdown", hb_mixdown_get_short_name(mix));
    ghb_dict_set_double(asettings, "DRC", drc);
    ghb_dict_set_double(asettings, "Gain", gain);

    ghb_sanitize_audio_settings(settings, asettings);
    audio_add_to_settings(settings, asettings);

    return asettings;
}