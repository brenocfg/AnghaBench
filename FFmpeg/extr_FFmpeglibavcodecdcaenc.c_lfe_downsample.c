#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {size_t channel_config; int channels; scalar_t__* downsampled_lfe; int /*<<< orphan*/ * lfe_fir_64i; int /*<<< orphan*/ ** history; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int DCA_LFE_SAMPLES ; 
 int* lfe_index ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mul32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lfe_downsample(DCAEncContext *c, const int32_t *input)
{
    /* FIXME: make 128x LFE downsampling possible */
    const int lfech = lfe_index[c->channel_config];
    int i, j, lfes;
    int32_t hist[512];
    int32_t accum;
    int hist_start = 0;

    memcpy(hist, &c->history[c->channels - 1][0], 512 * sizeof(int32_t));

    for (lfes = 0; lfes < DCA_LFE_SAMPLES; lfes++) {
        /* Calculate the convolution */
        accum = 0;

        for (i = hist_start, j = 0; i < 512; i++, j++)
            accum += mul32(hist[i], c->lfe_fir_64i[j]);
        for (i = 0; i < hist_start; i++, j++)
            accum += mul32(hist[i], c->lfe_fir_64i[j]);

        c->downsampled_lfe[lfes] = accum;

        /* Copy in 64 new samples from input */
        for (i = 0; i < 64; i++)
            hist[i + hist_start] = input[(lfes * 64 + i) * c->channels + lfech];

        hist_start = (hist_start + 64) & 511;
    }
}