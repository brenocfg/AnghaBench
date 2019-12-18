#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_2__ signal_user_data_t ;
typedef  int /*<<< orphan*/  hb_title_t ;
struct TYPE_18__ {int muxers; scalar_t__ codec; } ;
typedef  TYPE_3__ hb_encoder_t ;
struct TYPE_19__ {int format; } ;
typedef  TYPE_4__ hb_container_t ;
struct TYPE_16__ {int /*<<< orphan*/  codec; int /*<<< orphan*/  channel_layout; } ;
struct TYPE_20__ {TYPE_1__ in; } ;
typedef  TYPE_5__ hb_audio_config_t ;
typedef  int /*<<< orphan*/  guint32 ;
typedef  int /*<<< orphan*/  gint64 ;
typedef  int /*<<< orphan*/  gint ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HB_ACODEC_NONE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ghb_dict_get_int (int /*<<< orphan*/ ,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* ghb_get_audio_info (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_get_copy_mask (int /*<<< orphan*/ ) ; 
 TYPE_4__* ghb_lookup_container_by_name (char const*) ; 
 int /*<<< orphan*/ * ghb_lookup_title (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_select_audio_codec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_select_fallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_settings_audio_encoder_codec (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grey_builder_combo_box_item (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grey_mix_opts (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grey_passthru (TYPE_2__*,TYPE_5__*) ; 
 TYPE_3__* hb_audio_encoder_get_next (TYPE_3__ const*) ; 
 TYPE_3__* hb_video_encoder_get_next (TYPE_3__ const*) ; 

void
ghb_grey_combo_options(signal_user_data_t *ud)
{
    gint track, title_id, titleindex, acodec, fallback;
    const hb_title_t *title;
    hb_audio_config_t *aconfig = NULL;

    title_id = ghb_dict_get_int(ud->settings, "title");
    title = ghb_lookup_title(title_id, &titleindex);

    track = ghb_dict_get_int(ud->settings, "AudioTrack");
    aconfig = ghb_get_audio_info(title, track);

    const char *mux_id;
    const hb_container_t *mux;

    mux_id = ghb_dict_get_string(ud->settings, "FileFormat");
    mux = ghb_lookup_container_by_name(mux_id);

    const hb_encoder_t *enc;
    for (enc = hb_audio_encoder_get_next(NULL); enc != NULL;
         enc = hb_audio_encoder_get_next(enc))
    {
        if (!(mux->format & enc->muxers) && enc->codec != HB_ACODEC_NONE)
        {
            grey_builder_combo_box_item(ud->builder, "AudioEncoder",
                enc->codec, TRUE);
            grey_builder_combo_box_item(ud->builder, "AudioEncoderFallback",
                enc->codec, TRUE);
        }
        else
        {
            grey_builder_combo_box_item(ud->builder, "AudioEncoder",
                enc->codec, FALSE);
            grey_builder_combo_box_item(ud->builder, "AudioEncoderFallback",
                enc->codec, FALSE);
        }
    }
    for (enc = hb_video_encoder_get_next(NULL); enc != NULL;
         enc = hb_video_encoder_get_next(enc))
    {
        if (!(mux->format & enc->muxers))
        {
            grey_builder_combo_box_item(ud->builder, "VideoEncoder",
                enc->codec, TRUE);
        }
        else
        {
            grey_builder_combo_box_item(ud->builder, "VideoEncoder",
                enc->codec, FALSE);
        }
    }
    grey_passthru(ud, aconfig);

    acodec = ghb_settings_audio_encoder_codec(ud->settings, "AudioEncoder");

    gint64 layout = aconfig != NULL ? aconfig->in.channel_layout : ~0;
    guint32 in_codec = aconfig != NULL ? aconfig->in.codec : 0;
    fallback = ghb_select_fallback(ud->settings, acodec);
    gint copy_mask = ghb_get_copy_mask(ud->settings);
    acodec = ghb_select_audio_codec(mux->format, in_codec, acodec,
                                    fallback, copy_mask);
    grey_mix_opts(ud, acodec, layout);
}