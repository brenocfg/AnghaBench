#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_15__ {int nterms; scalar_t__ best_bits; TYPE_3__* dps; int /*<<< orphan*/  log_limit; } ;
typedef  TYPE_1__ WavPackExtraInfo ;
struct TYPE_16__ {int block_samples; TYPE_3__*** sampleptrs; TYPE_3__* decorr_passes; } ;
typedef  TYPE_2__ WavPackEncodeContext ;
struct TYPE_17__ {int delta; scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (TYPE_3__*) ; 
 int /*<<< orphan*/  decorr_stereo_buffer (TYPE_1__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,int,int) ; 
 scalar_t__ log2stereo (TYPE_3__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 

__attribute__((used)) static void delta_stereo(WavPackEncodeContext *s, WavPackExtraInfo *info)
{
    int lower = 0, delta, d, i;
    uint32_t bits;

    if (!s->decorr_passes[0].value)
        return;
    delta = s->decorr_passes[0].delta;

    for (d = delta - 1; d >= 0; d--) {
        for (i = 0; i < info->nterms && s->decorr_passes[i].value; i++) {
            info->dps[i].value = s->decorr_passes[i].value;
            info->dps[i].delta = d;
            decorr_stereo_buffer(info,
                                 s->sampleptrs[i  ][0], s->sampleptrs[i  ][1],
                                 s->sampleptrs[i+1][0], s->sampleptrs[i+1][1],
                                 s->block_samples, i);
        }

        bits = log2stereo(s->sampleptrs[i][0], s->sampleptrs[i][1],
                          s->block_samples, info->log_limit);
        if (bits >= info->best_bits)
            break;
        lower = 1;
        info->best_bits = bits;
        CLEAR(s->decorr_passes);
        memcpy(s->decorr_passes, info->dps, sizeof(info->dps[0]) * i);
        memcpy(s->sampleptrs[info->nterms + 1][0], s->sampleptrs[i][0],
               s->block_samples * 4);
        memcpy(s->sampleptrs[info->nterms + 1][1], s->sampleptrs[i][1],
               s->block_samples * 4);
    }

    for (d = delta + 1; !lower && d <= 7; d++) {
        for (i = 0; i < info->nterms && s->decorr_passes[i].value; i++) {
            info->dps[i].value = s->decorr_passes[i].value;
            info->dps[i].delta = d;
            decorr_stereo_buffer(info,
                                 s->sampleptrs[i  ][0], s->sampleptrs[i  ][1],
                                 s->sampleptrs[i+1][0], s->sampleptrs[i+1][1],
                                 s->block_samples, i);
        }

        bits = log2stereo(s->sampleptrs[i][0], s->sampleptrs[i][1],
                          s->block_samples, info->log_limit);

        if (bits < info->best_bits) {
            info->best_bits = bits;
            CLEAR(s->decorr_passes);
            memcpy(s->decorr_passes, info->dps, sizeof(info->dps[0]) * i);
            memcpy(s->sampleptrs[info->nterms + 1][0],
                   s->sampleptrs[i][0], s->block_samples * 4);
            memcpy(s->sampleptrs[info->nterms + 1][1],
                   s->sampleptrs[i][1], s->block_samples * 4);
        }
        else
            break;
    }
}