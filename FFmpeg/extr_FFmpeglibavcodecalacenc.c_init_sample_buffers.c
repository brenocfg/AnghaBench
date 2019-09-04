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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_5__ {int** sample_buf; int frame_size; TYPE_1__* avctx; } ;
struct TYPE_4__ {scalar_t__ sample_fmt; int bits_per_raw_sample; } ;
typedef  TYPE_2__ AlacEncodeContext ;

/* Variables and functions */
 scalar_t__ AV_SAMPLE_FMT_S32P ; 
 int av_get_bytes_per_sample (scalar_t__) ; 

__attribute__((used)) static void init_sample_buffers(AlacEncodeContext *s, int channels,
                                const uint8_t *samples[2])
{
    int ch, i;
    int shift = av_get_bytes_per_sample(s->avctx->sample_fmt) * 8 -
                s->avctx->bits_per_raw_sample;

#define COPY_SAMPLES(type) do {                             \
        for (ch = 0; ch < channels; ch++) {                 \
            int32_t       *bptr = s->sample_buf[ch];        \
            const type *sptr = (const type *)samples[ch];   \
            for (i = 0; i < s->frame_size; i++)             \
                bptr[i] = sptr[i] >> shift;                 \
        }                                                   \
    } while (0)

    if (s->avctx->sample_fmt == AV_SAMPLE_FMT_S32P)
        COPY_SAMPLES(int32_t);
    else
        COPY_SAMPLES(int16_t);
}