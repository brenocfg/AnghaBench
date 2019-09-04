#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_15__ {scalar_t__ sample_fmt; int /*<<< orphan*/  nb_samples; int /*<<< orphan*/  channels; scalar_t__ data; int /*<<< orphan*/  samples_align; int /*<<< orphan*/  ptr_align; } ;
struct TYPE_13__ {int samples_align; int ptr_align; int /*<<< orphan*/  quantize; } ;
struct TYPE_14__ {scalar_t__ method; int samples_align; TYPE_3__* s16_data; int /*<<< orphan*/  ac_out; int /*<<< orphan*/  quantize; TYPE_1__ ddsp; int /*<<< orphan*/  ch_map_info; scalar_t__ apply_map; int /*<<< orphan*/  ac_in; TYPE_3__* flt_data; } ;
typedef  TYPE_2__ DitherContext ;
typedef  TYPE_3__ AudioData ;

/* Variables and functions */
 scalar_t__ AV_RESAMPLE_DITHER_TRIANGULAR_NS ; 
 scalar_t__ AV_SAMPLE_FMT_FLTP ; 
 scalar_t__ AV_SAMPLE_FMT_S16 ; 
 scalar_t__ AV_SAMPLE_FMT_S16P ; 
 int FFALIGN (int /*<<< orphan*/ ,int) ; 
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int convert_samples (TYPE_2__*,int /*<<< orphan*/ **,float* const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_audio_convert (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*) ; 
 int ff_audio_data_copy (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_audio_data_realloc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quantize_c ; 

int ff_convert_dither(DitherContext *c, AudioData *dst, AudioData *src)
{
    int ret;
    AudioData *flt_data;

    /* output directly to dst if it is planar */
    if (dst->sample_fmt == AV_SAMPLE_FMT_S16P)
        c->s16_data = dst;
    else {
        /* make sure s16_data is large enough for the output */
        ret = ff_audio_data_realloc(c->s16_data, src->nb_samples);
        if (ret < 0)
            return ret;
    }

    if (src->sample_fmt != AV_SAMPLE_FMT_FLTP || c->apply_map) {
        /* make sure flt_data is large enough for the input */
        ret = ff_audio_data_realloc(c->flt_data, src->nb_samples);
        if (ret < 0)
            return ret;
        flt_data = c->flt_data;
    }

    if (src->sample_fmt != AV_SAMPLE_FMT_FLTP) {
        /* convert input samples to fltp and scale to s16 range */
        ret = ff_audio_convert(c->ac_in, flt_data, src);
        if (ret < 0)
            return ret;
    } else if (c->apply_map) {
        ret = ff_audio_data_copy(flt_data, src, c->ch_map_info);
        if (ret < 0)
            return ret;
    } else {
        flt_data = src;
    }

    /* check alignment and padding constraints */
    if (c->method != AV_RESAMPLE_DITHER_TRIANGULAR_NS) {
        int ptr_align     = FFMIN(flt_data->ptr_align,     c->s16_data->ptr_align);
        int samples_align = FFMIN(flt_data->samples_align, c->s16_data->samples_align);
        int aligned_len   = FFALIGN(src->nb_samples, c->ddsp.samples_align);

        if (!(ptr_align % c->ddsp.ptr_align) && samples_align >= aligned_len) {
            c->quantize      = c->ddsp.quantize;
            c->samples_align = c->ddsp.samples_align;
        } else {
            c->quantize      = quantize_c;
            c->samples_align = 1;
        }
    }

    ret = convert_samples(c, (int16_t **)c->s16_data->data,
                          (float * const *)flt_data->data, src->channels,
                          src->nb_samples);
    if (ret < 0)
        return ret;

    c->s16_data->nb_samples = src->nb_samples;

    /* interleave output to dst if needed */
    if (dst->sample_fmt == AV_SAMPLE_FMT_S16) {
        ret = ff_audio_convert(c->ac_out, dst, c->s16_data);
        if (ret < 0)
            return ret;
    } else
        c->s16_data = NULL;

    return 0;
}