#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {double delta; scalar_t__ value; } ;
typedef  TYPE_1__ int32_t ;
struct TYPE_29__ {int gt16bit; int log_limit; int nterms; int /*<<< orphan*/  best_bits; TYPE_1__* dps; } ;
typedef  TYPE_2__ WavPackExtraInfo ;
struct TYPE_30__ {int flags; int num_terms; int block_samples; int extra_flags; double delta_decay; TYPE_1__* decorr_passes; TYPE_1__*** sampleptrs; } ;
typedef  TYPE_3__ WavPackEncodeContext ;

/* Variables and functions */
 int EXTRA_ADJUST_DELTAS ; 
 int EXTRA_BRANCHES ; 
 int EXTRA_SORT_FIRST ; 
 int EXTRA_SORT_LAST ; 
 int EXTRA_TRY_DELTAS ; 
 int FFMIN (int,int) ; 
 int MAG_LSB ; 
 int MAG_MASK ; 
 scalar_t__ allocate_buffers2 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  decorr_stereo (TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  decorr_stereo_quick (TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  delta_stereo (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ floor (double) ; 
 int /*<<< orphan*/  log2stereo (TYPE_1__*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  recurse_stereo (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_stereo (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static void analyze_stereo(WavPackEncodeContext *s,
                           int32_t *in_left, int32_t *in_right,
                           int do_samples)
{
    WavPackExtraInfo info;
    int i;

    info.gt16bit = ((s->flags & MAG_MASK) >> MAG_LSB) >= 16;

    info.log_limit = (((s->flags & MAG_MASK) >> MAG_LSB) + 4) * 256;
    info.log_limit = FFMIN(6912, info.log_limit);

    info.nterms = s->num_terms;

    if (allocate_buffers2(s, s->num_terms))
        return;

    memcpy(info.dps, s->decorr_passes, sizeof(info.dps));
    memcpy(s->sampleptrs[0][0], in_left,  s->block_samples * 4);
    memcpy(s->sampleptrs[0][1], in_right, s->block_samples * 4);

    for (i = 0; i < info.nterms && info.dps[i].value; i++)
        if (info.gt16bit)
            decorr_stereo(s->sampleptrs[i    ][0], s->sampleptrs[i    ][1],
                          s->sampleptrs[i + 1][0], s->sampleptrs[i + 1][1],
                          s->block_samples, info.dps + i, 1);
        else
            decorr_stereo_quick(s->sampleptrs[i    ][0], s->sampleptrs[i    ][1],
                                s->sampleptrs[i + 1][0], s->sampleptrs[i + 1][1],
                                s->block_samples, info.dps + i);

    info.best_bits = log2stereo(s->sampleptrs[info.nterms][0], s->sampleptrs[info.nterms][1],
                                s->block_samples, 0);

    memcpy(s->sampleptrs[info.nterms + 1][0], s->sampleptrs[i][0], s->block_samples * 4);
    memcpy(s->sampleptrs[info.nterms + 1][1], s->sampleptrs[i][1], s->block_samples * 4);

    if (s->extra_flags & EXTRA_BRANCHES)
        recurse_stereo(s, &info, 0, (int) floor(s->delta_decay + 0.5),
                       log2stereo(s->sampleptrs[0][0], s->sampleptrs[0][1],
                                  s->block_samples, 0));

    if (s->extra_flags & EXTRA_SORT_FIRST)
        sort_stereo(s, &info);

    if (s->extra_flags & EXTRA_TRY_DELTAS) {
        delta_stereo(s, &info);

        if ((s->extra_flags & EXTRA_ADJUST_DELTAS) && s->decorr_passes[0].value)
            s->delta_decay = (float)((s->delta_decay * 2.0 + s->decorr_passes[0].delta) / 3.0);
        else
            s->delta_decay = 2.0;
    }

    if (s->extra_flags & EXTRA_SORT_LAST)
        sort_stereo(s, &info);

    if (do_samples) {
        memcpy(in_left,  s->sampleptrs[info.nterms + 1][0], s->block_samples * 4);
        memcpy(in_right, s->sampleptrs[info.nterms + 1][1], s->block_samples * 4);
    }

    for (i = 0; i < info.nterms; i++)
        if (!s->decorr_passes[i].value)
            break;

    s->num_terms = i;
}