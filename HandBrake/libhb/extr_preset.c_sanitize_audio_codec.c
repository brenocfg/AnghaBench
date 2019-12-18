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
 int HB_ACODEC_AUTO_PASS ; 
 int HB_ACODEC_INVALID ; 
 int HB_ACODEC_NONE ; 
 int HB_ACODEC_PASS_FLAG ; 
 int HB_ACODEC_PASS_MASK ; 
 int hb_audio_encoder_get_default (int) ; 
 int hb_audio_encoder_get_fallback_for_passthru (int) ; 
 TYPE_1__* hb_audio_encoder_get_next (TYPE_1__ const*) ; 
 int hb_autopassthru_get_encoder (int,int,int,int) ; 

__attribute__((used)) static int sanitize_audio_codec(int in_codec, int out_codec,
                                int copy_mask, int fallback, int mux)
{
    int codec = out_codec;
    if (out_codec == HB_ACODEC_AUTO_PASS)
    {
        codec = hb_autopassthru_get_encoder(in_codec, copy_mask, fallback, mux);
    }
    else if ((out_codec & HB_ACODEC_PASS_FLAG) &&
             !(in_codec & out_codec & HB_ACODEC_PASS_MASK))
    {
        codec = hb_audio_encoder_get_fallback_for_passthru(out_codec);
        if (codec == HB_ACODEC_INVALID)
            codec = fallback;
    }

    // Check that encoder is valid for mux
    const hb_encoder_t *encoder = NULL;
    while ((encoder = hb_audio_encoder_get_next(encoder)) != NULL)
    {
        if (encoder->codec == codec && codec != HB_ACODEC_NONE &&
            !(encoder->muxers & mux))
        {
            codec = hb_audio_encoder_get_default(mux);
            break;
        }
    }
    if (codec == HB_ACODEC_INVALID)
        codec = hb_audio_encoder_get_default(mux);
    return codec;
}