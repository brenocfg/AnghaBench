#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_16__ {int nb_samples; } ;
struct TYPE_15__ {int out_sample_rate; int in_sample_rate; int cutoff; int phase_shift; int internal_sample_fmt; double filter_size; int /*<<< orphan*/  resample_channels; int /*<<< orphan*/  kaiser_beta; int /*<<< orphan*/  filter_type; int /*<<< orphan*/  linear_interp; } ;
struct TYPE_14__ {int phase_shift; int phase_mask; int filter_length; int padding_size; int initial_padding_samples; struct TYPE_14__* filter_bank; TYPE_9__* buffer; scalar_t__ frac; scalar_t__ index; scalar_t__ initial_padding_filled; int /*<<< orphan*/  dst_incr; int /*<<< orphan*/  ideal_dst_incr; int /*<<< orphan*/  src_incr; scalar_t__ compensation_distance; int /*<<< orphan*/  set_filter; int /*<<< orphan*/  resample_nearest; int /*<<< orphan*/  linear; int /*<<< orphan*/  resample_one; int /*<<< orphan*/  kaiser_beta; int /*<<< orphan*/  filter_type; TYPE_2__* avr; } ;
typedef  TYPE_1__ ResampleContext ;
typedef  TYPE_2__ AVAudioResampleContext ;

/* Variables and functions */
 scalar_t__ ARCH_AARCH64 ; 
 scalar_t__ ARCH_ARM ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_SAMPLE_FMT_DBLP 131 
#define  AV_SAMPLE_FMT_FLTP 130 
#define  AV_SAMPLE_FMT_S16P 129 
#define  AV_SAMPLE_FMT_S32P 128 
 int FFMAX (int,int) ; 
 double FFMIN (int,double) ; 
 int INT32_MAX ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int av_get_bytes_per_sample (int) ; 
 int /*<<< orphan*/  av_get_sample_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 void* av_mallocz (int) ; 
 int /*<<< orphan*/  av_reduce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 scalar_t__ build_filter (TYPE_1__*,double) ; 
 scalar_t__ ceil (double) ; 
 TYPE_9__* ff_audio_data_alloc (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  ff_audio_data_free (TYPE_9__**) ; 
 int /*<<< orphan*/  ff_audio_resample_init_aarch64 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ff_audio_resample_init_arm (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  resample_linear_dbl ; 
 int /*<<< orphan*/  resample_linear_flt ; 
 int /*<<< orphan*/  resample_linear_s16 ; 
 int /*<<< orphan*/  resample_linear_s32 ; 
 int /*<<< orphan*/  resample_nearest_dbl ; 
 int /*<<< orphan*/  resample_nearest_flt ; 
 int /*<<< orphan*/  resample_nearest_s16 ; 
 int /*<<< orphan*/  resample_nearest_s32 ; 
 int /*<<< orphan*/  resample_one_dbl ; 
 int /*<<< orphan*/  resample_one_flt ; 
 int /*<<< orphan*/  resample_one_s16 ; 
 int /*<<< orphan*/  resample_one_s32 ; 
 int /*<<< orphan*/  set_filter_dbl ; 
 int /*<<< orphan*/  set_filter_flt ; 
 int /*<<< orphan*/  set_filter_s16 ; 
 int /*<<< orphan*/  set_filter_s32 ; 

ResampleContext *ff_audio_resample_init(AVAudioResampleContext *avr)
{
    ResampleContext *c;
    int out_rate    = avr->out_sample_rate;
    int in_rate     = avr->in_sample_rate;
    double factor   = FFMIN(out_rate * avr->cutoff / in_rate, 1.0);
    int phase_count = 1 << avr->phase_shift;
    int felem_size;

    if (avr->internal_sample_fmt != AV_SAMPLE_FMT_S16P &&
        avr->internal_sample_fmt != AV_SAMPLE_FMT_S32P &&
        avr->internal_sample_fmt != AV_SAMPLE_FMT_FLTP &&
        avr->internal_sample_fmt != AV_SAMPLE_FMT_DBLP) {
        av_log(avr, AV_LOG_ERROR, "Unsupported internal format for "
               "resampling: %s\n",
               av_get_sample_fmt_name(avr->internal_sample_fmt));
        return NULL;
    }
    c = av_mallocz(sizeof(*c));
    if (!c)
        return NULL;

    c->avr           = avr;
    c->phase_shift   = avr->phase_shift;
    c->phase_mask    = phase_count - 1;
    c->linear        = avr->linear_interp;
    c->filter_length = FFMAX((int)ceil(avr->filter_size / factor), 1);
    c->filter_type   = avr->filter_type;
    c->kaiser_beta   = avr->kaiser_beta;

    switch (avr->internal_sample_fmt) {
    case AV_SAMPLE_FMT_DBLP:
        c->resample_one  = c->linear ? resample_linear_dbl : resample_one_dbl;
        c->resample_nearest = resample_nearest_dbl;
        c->set_filter    = set_filter_dbl;
        break;
    case AV_SAMPLE_FMT_FLTP:
        c->resample_one  = c->linear ? resample_linear_flt : resample_one_flt;
        c->resample_nearest = resample_nearest_flt;
        c->set_filter    = set_filter_flt;
        break;
    case AV_SAMPLE_FMT_S32P:
        c->resample_one  = c->linear ? resample_linear_s32 : resample_one_s32;
        c->resample_nearest = resample_nearest_s32;
        c->set_filter    = set_filter_s32;
        break;
    case AV_SAMPLE_FMT_S16P:
        c->resample_one  = c->linear ? resample_linear_s16 : resample_one_s16;
        c->resample_nearest = resample_nearest_s16;
        c->set_filter    = set_filter_s16;
        break;
    }

    if (ARCH_AARCH64)
        ff_audio_resample_init_aarch64(c, avr->internal_sample_fmt);
    if (ARCH_ARM)
        ff_audio_resample_init_arm(c, avr->internal_sample_fmt);

    felem_size = av_get_bytes_per_sample(avr->internal_sample_fmt);
    c->filter_bank = av_mallocz(c->filter_length * (phase_count + 1) * felem_size);
    if (!c->filter_bank)
        goto error;

    if (build_filter(c, factor) < 0)
        goto error;

    memcpy(&c->filter_bank[(c->filter_length * phase_count + 1) * felem_size],
           c->filter_bank, (c->filter_length - 1) * felem_size);
    memcpy(&c->filter_bank[c->filter_length * phase_count * felem_size],
           &c->filter_bank[(c->filter_length - 1) * felem_size], felem_size);

    c->compensation_distance = 0;
    if (!av_reduce(&c->src_incr, &c->dst_incr, out_rate,
                   in_rate * (int64_t)phase_count, INT32_MAX / 2))
        goto error;
    c->ideal_dst_incr = c->dst_incr;

    c->padding_size   = (c->filter_length - 1) / 2;
    c->initial_padding_filled = 0;
    c->index = 0;
    c->frac  = 0;

    /* allocate internal buffer */
    c->buffer = ff_audio_data_alloc(avr->resample_channels, c->padding_size,
                                    avr->internal_sample_fmt,
                                    "resample buffer");
    if (!c->buffer)
        goto error;
    c->buffer->nb_samples      = c->padding_size;
    c->initial_padding_samples = c->padding_size;

    av_log(avr, AV_LOG_DEBUG, "resample: %s from %d Hz to %d Hz\n",
           av_get_sample_fmt_name(avr->internal_sample_fmt),
           avr->in_sample_rate, avr->out_sample_rate);

    return c;

error:
    ff_audio_data_free(&c->buffer);
    av_free(c->filter_bank);
    av_free(c);
    return NULL;
}