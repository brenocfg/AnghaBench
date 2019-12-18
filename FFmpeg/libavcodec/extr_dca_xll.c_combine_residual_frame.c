#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_19__ {scalar_t__ output_rate; int npcmsamples; int** output_samples; } ;
struct TYPE_18__ {int packet; TYPE_8__ core; } ;
struct TYPE_17__ {scalar_t__ freq; int nchannels; int residual_encode; int* ch_remap; int pcm_bit_res; int* dmix_scale_inv; int hier_ofs; TYPE_1__* bands; } ;
struct TYPE_16__ {int nframesamples; TYPE_13__* avctx; } ;
struct TYPE_15__ {int** msb_sample_buffer; } ;
struct TYPE_14__ {TYPE_4__* priv_data; } ;
typedef  scalar_t__ SUINT ;
typedef  TYPE_2__ DCAXllDecoder ;
typedef  TYPE_3__ DCAXllChSet ;
typedef  TYPE_4__ DCAContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int DCA_PACKET_CORE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_13__*,int /*<<< orphan*/ ,char*,...) ; 
 int chs_get_lsb_width (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ clip23 (int) ; 
 int ff_dca_core_map_spkr (TYPE_8__*,int) ; 
 TYPE_3__* find_next_hier_dmix_chset (TYPE_2__*,TYPE_3__*) ; 
 int mul16 (int,int) ; 

__attribute__((used)) static int combine_residual_frame(DCAXllDecoder *s, DCAXllChSet *c)
{
    DCAContext *dca = s->avctx->priv_data;
    int ch, nsamples = s->nframesamples;
    DCAXllChSet *o;

    // Verify that core is compatible
    if (!(dca->packet & DCA_PACKET_CORE)) {
        av_log(s->avctx, AV_LOG_ERROR, "Residual encoded channels are present without core\n");
        return AVERROR(EINVAL);
    }

    if (c->freq != dca->core.output_rate) {
        av_log(s->avctx, AV_LOG_WARNING, "Sample rate mismatch between core (%d Hz) and XLL (%d Hz)\n", dca->core.output_rate, c->freq);
        return AVERROR_INVALIDDATA;
    }

    if (nsamples != dca->core.npcmsamples) {
        av_log(s->avctx, AV_LOG_WARNING, "Number of samples per frame mismatch between core (%d) and XLL (%d)\n", dca->core.npcmsamples, nsamples);
        return AVERROR_INVALIDDATA;
    }

    // See if this channel set is downmixed and find the next channel set in
    // hierarchy. If downmixed, undo core pre-scaling before combining with
    // residual (residual is not scaled).
    o = find_next_hier_dmix_chset(s, c);

    // Reduce core bit width and combine with residual
    for (ch = 0; ch < c->nchannels; ch++) {
        int n, spkr, shift, round;
        int32_t *src, *dst;

        if (c->residual_encode & (1 << ch))
            continue;

        // Map this channel to core speaker
        spkr = ff_dca_core_map_spkr(&dca->core, c->ch_remap[ch]);
        if (spkr < 0) {
            av_log(s->avctx, AV_LOG_WARNING, "Residual encoded channel (%d) references unavailable core channel\n", c->ch_remap[ch]);
            return AVERROR_INVALIDDATA;
        }

        // Account for LSB width
        shift = 24 - c->pcm_bit_res + chs_get_lsb_width(s, c, 0, ch);
        if (shift > 24) {
            av_log(s->avctx, AV_LOG_WARNING, "Invalid core shift (%d bits)\n", shift);
            return AVERROR_INVALIDDATA;
        }

        round = shift > 0 ? 1 << (shift - 1) : 0;

        src = dca->core.output_samples[spkr];
        dst = c->bands[0].msb_sample_buffer[ch];
        if (o) {
            // Undo embedded core downmix pre-scaling
            int scale_inv = o->dmix_scale_inv[c->hier_ofs + ch];
            for (n = 0; n < nsamples; n++)
                dst[n] += (SUINT)clip23((mul16(src[n], scale_inv) + round) >> shift);
        } else {
            // No downmix scaling
            for (n = 0; n < nsamples; n++)
                dst[n] += (unsigned)((src[n] + round) >> shift);
        }
    }

    return 0;
}