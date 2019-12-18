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
struct TYPE_4__ {int codec; int muxers; } ;
typedef  TYPE_1__ hb_encoder_t ;

/* Variables and functions */
 int HB_ACODEC_INVALID ; 
 int HB_ACODEC_NONE ; 
 int HB_ACODEC_PASS_FLAG ; 
 TYPE_1__* hb_audio_encoder_get_next (TYPE_1__ const*) ; 

int hb_autopassthru_get_encoder(int in_codec, int copy_mask, int fallback,
                                int muxer)
{
    int out_codec_result_set = 0;
    int fallback_result_set  = 0;
    int out_codec_result = HB_ACODEC_INVALID;
    int fallback_result  = HB_ACODEC_INVALID;
    const hb_encoder_t *audio_encoder = NULL;
    int out_codec = (copy_mask & in_codec) | HB_ACODEC_PASS_FLAG;

    // sanitize fallback encoder and selected passthru
    // note: invalid fallbacks are caught in hb_autopassthru_apply_settings
    while ((audio_encoder = hb_audio_encoder_get_next(audio_encoder)) != NULL)
    {
        if (!out_codec_result_set && audio_encoder->codec == out_codec)
        {
            out_codec_result_set = 1;
            if (audio_encoder->muxers & muxer)
                out_codec_result = out_codec;
        }
        else if (!fallback_result_set && audio_encoder->codec == fallback)
        {
            fallback_result_set  = 1;
            if ((audio_encoder->muxers & muxer) || fallback == HB_ACODEC_NONE)
                fallback_result = fallback;
        }
        if (out_codec_result_set && fallback_result_set)
        {
            break;
        }
    }
    return (out_codec_result != HB_ACODEC_INVALID) ? out_codec_result :
                                                     fallback_result;
}