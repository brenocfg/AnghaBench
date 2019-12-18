#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_value_t ;
struct TYPE_7__ {int /*<<< orphan*/  list_audio; } ;
typedef  TYPE_2__ hb_title_t ;
struct TYPE_6__ {int samplerate; int channel_layout; } ;
struct TYPE_8__ {TYPE_1__ in; } ;
typedef  TYPE_3__ hb_audio_config_t ;

/* Variables and functions */
 int AV_CH_LAYOUT_5POINT1 ; 
 int HB_ACODEC_PASS_FLAG ; 
 int HB_AMIXDOWN_NONE ; 
 int HB_INVALID_AMIXDOWN ; 
 double HB_INVALID_AUDIO_QUALITY ; 
 int hb_audio_bitrate_get_best (int,int,int,int) ; 
 int hb_audio_bitrate_get_default (int,int,int) ; 
 int hb_audio_encoder_get_from_name (char const*) ; 
 int /*<<< orphan*/  hb_audio_encoder_get_short_name (int) ; 
 double hb_audio_quality_get_best (int,double) ; 
 double hb_audio_quality_get_default (int) ; 
 int /*<<< orphan*/  hb_audio_quality_get_limits (int,float*,float*,float*,int*) ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 double hb_dict_get_double (int /*<<< orphan*/ *,char*) ; 
 int hb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* hb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* hb_list_audio_config_item (int /*<<< orphan*/ ,int) ; 
 int hb_mixdown_get_best (int,int,int) ; 
 int hb_mixdown_get_from_name (char const*) ; 
 int /*<<< orphan*/  hb_mixdown_get_short_name (int) ; 
 int /*<<< orphan*/  hb_value_double (double) ; 
 int /*<<< orphan*/  hb_value_int (int) ; 
 int /*<<< orphan*/  hb_value_string (int /*<<< orphan*/ ) ; 

void hb_sanitize_audio_settings(const hb_title_t * title,
                                hb_value_t * audio_settings)
{
    const char        * mix_name;
    const char        * codec_name;
    int                 track, codec, mix, bitrate, samplerate;
    int                 quality_enable;
    double              quality;
    hb_value_t        * val;
    hb_audio_config_t * audio_config = NULL;

    track      = hb_dict_get_int(audio_settings, "Track");
    codec_name = hb_dict_get_string(audio_settings, "Encoder");
    codec      = hb_audio_encoder_get_from_name(codec_name);
    mix_name   = hb_dict_get_string(audio_settings, "Mixdown");
    mix        = hb_mixdown_get_from_name(mix_name);
    bitrate    = hb_dict_get_int(audio_settings, "Bitrate");
    quality    = hb_dict_get_double(audio_settings, "Quality");
    samplerate = hb_dict_get_int(audio_settings, "Samplerate");
    val        = hb_dict_get(audio_settings, "Quality");
    quality_enable = !(bitrate > 0 || val == NULL ||
                       quality == HB_INVALID_AUDIO_QUALITY);

    if (title != NULL)
    {
        audio_config = hb_list_audio_config_item(title->list_audio, track);
    }
    if (samplerate == 0 && audio_config != NULL)
    {
        samplerate = audio_config->in.samplerate;
    }

    if (codec & HB_ACODEC_PASS_FLAG)
    {
        mix = HB_AMIXDOWN_NONE;
        hb_dict_set(audio_settings, "Mixdown",
                    hb_value_string(hb_mixdown_get_short_name(mix)));
        hb_dict_set(audio_settings, "Samplerate", hb_value_int(0));
        hb_dict_set(audio_settings, "DRC", hb_value_double(0.0));
    }
    else
    {
        int layout = AV_CH_LAYOUT_5POINT1;
        if (audio_config != NULL)
        {
            layout = audio_config->in.channel_layout;
        }
        if (mix == HB_AMIXDOWN_NONE)
        {
            mix = HB_INVALID_AMIXDOWN;
        }
        mix = hb_mixdown_get_best(codec, layout, mix);
        if (quality_enable)
        {
            float low, high, gran;
            int dir;
            hb_audio_quality_get_limits(codec, &low, &high, &gran, &dir);
            if (quality < low || quality > high)
            {
                quality = hb_audio_quality_get_default(codec);
            }
            else
            {
                quality = hb_audio_quality_get_best(codec, quality);
            }
        }
        else
        {
            if (bitrate != -1)
            {
                bitrate = hb_audio_bitrate_get_best(codec, bitrate,
                                                    samplerate, mix);
            }
            else
            {
                bitrate = hb_audio_bitrate_get_default(codec, samplerate, mix);
            }
        }
        hb_dict_set(audio_settings, "Mixdown",
                    hb_value_string(hb_mixdown_get_short_name(mix)));
    }
    if (quality_enable)
    {
        bitrate = -1;
    }
    else
    {
        quality = HB_INVALID_AUDIO_QUALITY;
    }
    hb_dict_set(audio_settings, "Quality", hb_value_double(quality));
    hb_dict_set(audio_settings, "Bitrate", hb_value_int(bitrate));
    hb_dict_set(audio_settings, "Encoder",
                hb_value_string(hb_audio_encoder_get_short_name(codec)));
}