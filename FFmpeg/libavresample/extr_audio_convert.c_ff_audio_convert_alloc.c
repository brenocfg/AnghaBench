#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_13__ {scalar_t__ dither_method; } ;
struct TYPE_12__ {int out_fmt; int in_fmt; int channels; int apply_map; int planes; int /*<<< orphan*/  func_type; int /*<<< orphan*/  dc; TYPE_2__* avr; } ;
typedef  TYPE_1__ AudioConvert ;
typedef  TYPE_2__ AVAudioResampleContext ;

/* Variables and functions */
 scalar_t__ ARCH_AARCH64 ; 
 scalar_t__ ARCH_ARM ; 
 scalar_t__ ARCH_X86 ; 
 scalar_t__ AV_RESAMPLE_DITHER_NONE ; 
 scalar_t__ AV_SAMPLE_FMT_S16 ; 
 int /*<<< orphan*/  CONV_FUNC_TYPE_DEINTERLEAVE ; 
 int /*<<< orphan*/  CONV_FUNC_TYPE_FLAT ; 
 int /*<<< orphan*/  CONV_FUNC_TYPE_INTERLEAVE ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int av_get_bytes_per_sample (int) ; 
 scalar_t__ av_get_packed_sample_fmt (int) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  ff_audio_convert_init_aarch64 (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_audio_convert_init_arm (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_audio_convert_init_x86 (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_dither_alloc (TYPE_2__*,int,int,int,int,int) ; 
 int ff_sample_fmt_is_planar (int,int) ; 
 int /*<<< orphan*/  set_generic_function (TYPE_1__*) ; 

AudioConvert *ff_audio_convert_alloc(AVAudioResampleContext *avr,
                                     enum AVSampleFormat out_fmt,
                                     enum AVSampleFormat in_fmt,
                                     int channels, int sample_rate,
                                     int apply_map)
{
    AudioConvert *ac;
    int in_planar, out_planar;

    ac = av_mallocz(sizeof(*ac));
    if (!ac)
        return NULL;

    ac->avr      = avr;
    ac->out_fmt  = out_fmt;
    ac->in_fmt   = in_fmt;
    ac->channels = channels;
    ac->apply_map = apply_map;

    if (avr->dither_method != AV_RESAMPLE_DITHER_NONE          &&
        av_get_packed_sample_fmt(out_fmt) == AV_SAMPLE_FMT_S16 &&
        av_get_bytes_per_sample(in_fmt) > 2) {
        ac->dc = ff_dither_alloc(avr, out_fmt, in_fmt, channels, sample_rate,
                                 apply_map);
        if (!ac->dc) {
            av_free(ac);
            return NULL;
        }
        return ac;
    }

    in_planar  = ff_sample_fmt_is_planar(in_fmt, channels);
    out_planar = ff_sample_fmt_is_planar(out_fmt, channels);

    if (in_planar == out_planar) {
        ac->func_type = CONV_FUNC_TYPE_FLAT;
        ac->planes    = in_planar ? ac->channels : 1;
    } else if (in_planar)
        ac->func_type = CONV_FUNC_TYPE_INTERLEAVE;
    else
        ac->func_type = CONV_FUNC_TYPE_DEINTERLEAVE;

    set_generic_function(ac);

    if (ARCH_AARCH64)
        ff_audio_convert_init_aarch64(ac);
    if (ARCH_ARM)
        ff_audio_convert_init_arm(ac);
    if (ARCH_X86)
        ff_audio_convert_init_x86(ac);

    return ac;
}