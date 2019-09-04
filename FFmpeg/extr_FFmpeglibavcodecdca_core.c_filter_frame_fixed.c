#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_18__ {int bits_per_raw_sample; int channels; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  sample_rate; TYPE_3__* priv_data; } ;
struct TYPE_17__ {int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_16__ {int packet; } ;
struct TYPE_15__ {int npcmsamples; int ext_audio_mask; size_t audio_mode; int** output_samples; int xxch_dmix_scale_inv; int* xxch_dmix_coeff; int nchannels; int xxch_mask_nbits; unsigned int xxch_core_mask; unsigned int* xxch_dmix_mask; size_t* ch_remap; int /*<<< orphan*/  ch_mask; int /*<<< orphan*/  prim_dmix_coeff; TYPE_11__* dcadsp; int /*<<< orphan*/  request_mask; TYPE_1__* fixed_dsp; scalar_t__ sumdiff_surround; scalar_t__ sumdiff_front; scalar_t__ xxch_dmix_embedded; scalar_t__ es_format; int /*<<< orphan*/  output_rate; TYPE_5__* avctx; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* butterflies_fixed ) (int*,int*,int) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* dmix_sub ) (int*,int*,int,int) ;int /*<<< orphan*/  (* dmix_scale_inv ) (int*,int,int) ;int /*<<< orphan*/  (* dmix_sub_xch ) (int*,int*,int*,int) ;} ;
typedef  TYPE_2__ DCACoreDecoder ;
typedef  TYPE_3__ DCAContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S32P ; 
 size_t DCA_AMODE_2F2R ; 
 size_t DCA_AMODE_MONO ; 
 size_t DCA_AMODE_STEREO_SUMDIFF ; 
 int DCA_CSS_XCH ; 
 int DCA_CSS_XXCH ; 
 int DCA_EXSS_XXCH ; 
 int DCA_PACKET_XLL ; 
 size_t DCA_SPEAKER_Cs ; 
 size_t DCA_SPEAKER_L ; 
 size_t DCA_SPEAKER_Ls ; 
 size_t DCA_SPEAKER_R ; 
 size_t DCA_SPEAKER_Rs ; 
 int DCA_XXCH_CHANNELS_MAX ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int clip23 (int) ; 
 int* ff_dca_channels ; 
 int ff_dca_core_filter_fixed (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_dca_downmix_to_stereo_fixed (TYPE_11__*,int**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int map_prm_ch_to_spkr (TYPE_2__*,int) ; 
 int mul16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int*,int) ; 
 int /*<<< orphan*/  stub2 (int*,int,int) ; 
 int /*<<< orphan*/  stub3 (int*,int*,int,int) ; 
 int /*<<< orphan*/  stub4 (int*,int*,int) ; 
 int /*<<< orphan*/  stub5 (int*,int*,int) ; 

__attribute__((used)) static int filter_frame_fixed(DCACoreDecoder *s, AVFrame *frame)
{
    AVCodecContext *avctx = s->avctx;
    DCAContext *dca = avctx->priv_data;
    int i, n, ch, ret, spkr, nsamples;

    // Don't filter twice when falling back from XLL
    if (!(dca->packet & DCA_PACKET_XLL) && (ret = ff_dca_core_filter_fixed(s, 0)) < 0)
        return ret;

    avctx->sample_rate = s->output_rate;
    avctx->sample_fmt = AV_SAMPLE_FMT_S32P;
    avctx->bits_per_raw_sample = 24;

    frame->nb_samples = nsamples = s->npcmsamples;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    // Undo embedded XCH downmix
    if (s->es_format && (s->ext_audio_mask & DCA_CSS_XCH)
        && s->audio_mode >= DCA_AMODE_2F2R) {
        s->dcadsp->dmix_sub_xch(s->output_samples[DCA_SPEAKER_Ls],
                                s->output_samples[DCA_SPEAKER_Rs],
                                s->output_samples[DCA_SPEAKER_Cs],
                                nsamples);

    }

    // Undo embedded XXCH downmix
    if ((s->ext_audio_mask & (DCA_CSS_XXCH | DCA_EXSS_XXCH))
        && s->xxch_dmix_embedded) {
        int scale_inv   = s->xxch_dmix_scale_inv;
        int *coeff_ptr  = s->xxch_dmix_coeff;
        int xch_base    = ff_dca_channels[s->audio_mode];
        av_assert1(s->nchannels - xch_base <= DCA_XXCH_CHANNELS_MAX);

        // Undo embedded core downmix pre-scaling
        for (spkr = 0; spkr < s->xxch_mask_nbits; spkr++) {
            if (s->xxch_core_mask & (1U << spkr)) {
                s->dcadsp->dmix_scale_inv(s->output_samples[spkr],
                                          scale_inv, nsamples);
            }
        }

        // Undo downmix
        for (ch = xch_base; ch < s->nchannels; ch++) {
            int src_spkr = map_prm_ch_to_spkr(s, ch);
            if (src_spkr < 0)
                return AVERROR(EINVAL);
            for (spkr = 0; spkr < s->xxch_mask_nbits; spkr++) {
                if (s->xxch_dmix_mask[ch - xch_base] & (1U << spkr)) {
                    int coeff = mul16(*coeff_ptr++, scale_inv);
                    if (coeff) {
                        s->dcadsp->dmix_sub(s->output_samples[spkr    ],
                                            s->output_samples[src_spkr],
                                            coeff, nsamples);
                    }
                }
            }
        }
    }

    if (!(s->ext_audio_mask & (DCA_CSS_XXCH | DCA_CSS_XCH | DCA_EXSS_XXCH))) {
        // Front sum/difference decoding
        if ((s->sumdiff_front && s->audio_mode > DCA_AMODE_MONO)
            || s->audio_mode == DCA_AMODE_STEREO_SUMDIFF) {
            s->fixed_dsp->butterflies_fixed(s->output_samples[DCA_SPEAKER_L],
                                            s->output_samples[DCA_SPEAKER_R],
                                            nsamples);
        }

        // Surround sum/difference decoding
        if (s->sumdiff_surround && s->audio_mode >= DCA_AMODE_2F2R) {
            s->fixed_dsp->butterflies_fixed(s->output_samples[DCA_SPEAKER_Ls],
                                            s->output_samples[DCA_SPEAKER_Rs],
                                            nsamples);
        }
    }

    // Downmix primary channel set to stereo
    if (s->request_mask != s->ch_mask) {
        ff_dca_downmix_to_stereo_fixed(s->dcadsp,
                                       s->output_samples,
                                       s->prim_dmix_coeff,
                                       nsamples, s->ch_mask);
    }

    for (i = 0; i < avctx->channels; i++) {
        int32_t *samples = s->output_samples[s->ch_remap[i]];
        int32_t *plane = (int32_t *)frame->extended_data[i];
        for (n = 0; n < nsamples; n++)
            plane[n] = clip23(samples[n]) * (1 << 8);
    }

    return 0;
}