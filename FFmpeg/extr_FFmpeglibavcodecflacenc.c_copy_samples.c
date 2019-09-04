#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_8__ {int blocksize; TYPE_2__* subframes; } ;
struct TYPE_9__ {int channels; TYPE_3__ frame; TYPE_1__* avctx; } ;
struct TYPE_7__ {int* samples; } ;
struct TYPE_6__ {scalar_t__ sample_fmt; int bits_per_raw_sample; } ;
typedef  TYPE_3__ FlacFrame ;
typedef  TYPE_4__ FlacEncodeContext ;

/* Variables and functions */
 scalar_t__ AV_SAMPLE_FMT_S16 ; 
 int av_get_bytes_per_sample (scalar_t__) ; 

__attribute__((used)) static void copy_samples(FlacEncodeContext *s, const void *samples)
{
    int i, j, ch;
    FlacFrame *frame;
    int shift = av_get_bytes_per_sample(s->avctx->sample_fmt) * 8 -
                s->avctx->bits_per_raw_sample;

#define COPY_SAMPLES(bits) do {                                     \
    const int ## bits ## _t *samples0 = samples;                    \
    frame = &s->frame;                                              \
    for (i = 0, j = 0; i < frame->blocksize; i++)                   \
        for (ch = 0; ch < s->channels; ch++, j++)                   \
            frame->subframes[ch].samples[i] = samples0[j] >> shift; \
} while (0)

    if (s->avctx->sample_fmt == AV_SAMPLE_FMT_S16)
        COPY_SAMPLES(16);
    else
        COPY_SAMPLES(32);
}