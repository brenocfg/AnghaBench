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
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_5__ {TYPE_1__* avctx; } ;
typedef  TYPE_2__ WavPackEncodeContext ;
struct TYPE_4__ {int sample_fmt; int bits_per_raw_sample; } ;

/* Variables and functions */
#define  AV_SAMPLE_FMT_FLTP 131 
#define  AV_SAMPLE_FMT_S16P 130 
#define  AV_SAMPLE_FMT_S32P 129 
#define  AV_SAMPLE_FMT_U8P 128 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void fill_buffer(WavPackEncodeContext *s,
                        const int8_t *src, int32_t *dst,
                        int nb_samples)
{
    int i;

#define COPY_SAMPLES(type, offset, shift) do {            \
        const type *sptr = (const type *)src;             \
        for (i = 0; i < nb_samples; i++)                  \
            dst[i] = (sptr[i] - offset) >> shift;         \
    } while (0)

    switch (s->avctx->sample_fmt) {
    case AV_SAMPLE_FMT_U8P:
        COPY_SAMPLES(int8_t, 0x80, 0);
        break;
    case AV_SAMPLE_FMT_S16P:
        COPY_SAMPLES(int16_t, 0, 0);
        break;
    case AV_SAMPLE_FMT_S32P:
        if (s->avctx->bits_per_raw_sample <= 24) {
            COPY_SAMPLES(int32_t, 0, 8);
            break;
        }
    case AV_SAMPLE_FMT_FLTP:
        memcpy(dst, src, nb_samples * 4);
    }
}