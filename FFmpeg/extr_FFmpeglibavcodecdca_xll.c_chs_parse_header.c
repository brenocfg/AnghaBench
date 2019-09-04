#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ one_to_one_map_ch_to_spkr; } ;
struct TYPE_12__ {int* orig_order; int highest_pred_order; int* adapt_pred_order; int* fixed_pred_order; int** adapt_refl_coeff; int dmix_embedded; scalar_t__ lsb_section_size; int* nscalablelsbs; int* bit_width_adjust; void** decor_coeff; void* decor_enabled; } ;
struct TYPE_11__ {int nchannels; int residual_encode; int pcm_bit_res; int storage_bit_res; int freq; int primary_chset; int dmix_embedded; int dmix_type; unsigned int ch_mask; int* ch_remap; int nfreqbands; int nabits; TYPE_3__* bands; void* hier_chset; void* dmix_coeffs_present; } ;
struct TYPE_10__ {int nchsets; int ch_mask_nbits; int nsegsamples; int seg_size_nbits; scalar_t__ frame_size; int band_crc_present; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; scalar_t__ scalable_lsbs; TYPE_2__* chset; } ;
typedef  TYPE_1__ DCAXllDecoder ;
typedef  TYPE_2__ DCAXllChSet ;
typedef  TYPE_3__ DCAXllBand ;
typedef  TYPE_4__ DCAExssAsset ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int DCA_DMIX_TYPE_COUNT ; 
 int DCA_SPEAKER_L ; 
 unsigned int DCA_SPEAKER_LAYOUT_STEREO ; 
 int DCA_SPEAKER_R ; 
 int DCA_XLL_CHANNELS_MAX ; 
 int av_ceil_log2 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int av_popcount (unsigned int) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ff_dca_check_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int* ff_dca_sampling_freqs ; 
 scalar_t__ ff_dca_seek_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__* ff_dca_xll_refl_coeff ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 void* get_bits_long (int /*<<< orphan*/ *,int) ; 
 void* get_linear (int /*<<< orphan*/ *,int) ; 
 int parse_dmix_coeffs (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int chs_parse_header(DCAXllDecoder *s, DCAXllChSet *c, DCAExssAsset *asset)
{
    int i, j, k, ret, band, header_size, header_pos = get_bits_count(&s->gb);
    DCAXllChSet *p = &s->chset[0];
    DCAXllBand *b;

    // Size of channel set sub-header
    header_size = get_bits(&s->gb, 10) + 1;

    // Check CRC
    if (ff_dca_check_crc(s->avctx, &s->gb, header_pos, header_pos + header_size * 8)) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid XLL sub-header checksum\n");
        return AVERROR_INVALIDDATA;
    }

    // Number of channels in the channel set
    c->nchannels = get_bits(&s->gb, 4) + 1;
    if (c->nchannels > DCA_XLL_CHANNELS_MAX) {
        avpriv_request_sample(s->avctx, "%d XLL channels", c->nchannels);
        return AVERROR_PATCHWELCOME;
    }

    // Residual type
    c->residual_encode = get_bits(&s->gb, c->nchannels);

    // PCM bit resolution
    c->pcm_bit_res = get_bits(&s->gb, 5) + 1;

    // Storage unit width
    c->storage_bit_res = get_bits(&s->gb, 5) + 1;
    if (c->storage_bit_res != 16 && c->storage_bit_res != 20 && c->storage_bit_res != 24) {
        avpriv_request_sample(s->avctx, "%d-bit XLL storage resolution", c->storage_bit_res);
        return AVERROR_PATCHWELCOME;
    }

    if (c->pcm_bit_res > c->storage_bit_res) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid PCM bit resolution for XLL channel set (%d > %d)\n", c->pcm_bit_res, c->storage_bit_res);
        return AVERROR_INVALIDDATA;
    }

    // Original sampling frequency
    c->freq = ff_dca_sampling_freqs[get_bits(&s->gb, 4)];
    if (c->freq > 192000) {
        avpriv_request_sample(s->avctx, "%d Hz XLL sampling frequency", c->freq);
        return AVERROR_PATCHWELCOME;
    }

    // Sampling frequency modifier
    if (get_bits(&s->gb, 2)) {
        avpriv_request_sample(s->avctx, "XLL sampling frequency modifier");
        return AVERROR_PATCHWELCOME;
    }

    // Which replacement set this channel set is member of
    if (get_bits(&s->gb, 2)) {
        avpriv_request_sample(s->avctx, "XLL replacement set");
        return AVERROR_PATCHWELCOME;
    }

    if (asset->one_to_one_map_ch_to_spkr) {
        // Primary channel set flag
        c->primary_chset = get_bits1(&s->gb);
        if (c->primary_chset != (c == p)) {
            av_log(s->avctx, AV_LOG_ERROR, "The first (and only) XLL channel set must be primary\n");
            return AVERROR_INVALIDDATA;
        }

        // Downmix coefficients present in stream
        c->dmix_coeffs_present = get_bits1(&s->gb);

        // Downmix already performed by encoder
        c->dmix_embedded = c->dmix_coeffs_present && get_bits1(&s->gb);

        // Downmix type
        if (c->dmix_coeffs_present && c->primary_chset) {
            c->dmix_type = get_bits(&s->gb, 3);
            if (c->dmix_type >= DCA_DMIX_TYPE_COUNT) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid XLL primary channel set downmix type\n");
                return AVERROR_INVALIDDATA;
            }
        }

        // Whether the channel set is part of a hierarchy
        c->hier_chset = get_bits1(&s->gb);
        if (!c->hier_chset && s->nchsets != 1) {
            avpriv_request_sample(s->avctx, "XLL channel set outside of hierarchy");
            return AVERROR_PATCHWELCOME;
        }

        // Downmix coefficients
        if (c->dmix_coeffs_present && (ret = parse_dmix_coeffs(s, c)) < 0)
            return ret;

        // Channel mask enabled
        if (!get_bits1(&s->gb)) {
            avpriv_request_sample(s->avctx, "Disabled XLL channel mask");
            return AVERROR_PATCHWELCOME;
        }

        // Channel mask for set
        c->ch_mask = get_bits_long(&s->gb, s->ch_mask_nbits);
        if (av_popcount(c->ch_mask) != c->nchannels) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid XLL channel mask\n");
            return AVERROR_INVALIDDATA;
        }

        // Build the channel to speaker map
        for (i = 0, j = 0; i < s->ch_mask_nbits; i++)
            if (c->ch_mask & (1U << i))
                c->ch_remap[j++] = i;
    } else {
        // Mapping coeffs present flag
        if (c->nchannels != 2 || s->nchsets != 1 || get_bits1(&s->gb)) {
            avpriv_request_sample(s->avctx, "Custom XLL channel to speaker mapping");
            return AVERROR_PATCHWELCOME;
        }

        // Setup for LtRt decoding
        c->primary_chset = 1;
        c->dmix_coeffs_present = 0;
        c->dmix_embedded = 0;
        c->hier_chset = 0;
        c->ch_mask = DCA_SPEAKER_LAYOUT_STEREO;
        c->ch_remap[0] = DCA_SPEAKER_L;
        c->ch_remap[1] = DCA_SPEAKER_R;
    }

    if (c->freq > 96000) {
        // Extra frequency bands flag
        if (get_bits1(&s->gb)) {
            avpriv_request_sample(s->avctx, "Extra XLL frequency bands");
            return AVERROR_PATCHWELCOME;
        }
        c->nfreqbands = 2;
    } else {
        c->nfreqbands = 1;
    }

    // Set the sampling frequency to that of the first frequency band.
    // Frequency will be doubled again after bands assembly.
    c->freq >>= c->nfreqbands - 1;

    // Verify that all channel sets have the same audio characteristics
    if (c != p && (c->nfreqbands != p->nfreqbands || c->freq != p->freq
                   || c->pcm_bit_res != p->pcm_bit_res
                   || c->storage_bit_res != p->storage_bit_res)) {
        avpriv_request_sample(s->avctx, "Different XLL audio characteristics");
        return AVERROR_PATCHWELCOME;
    }

    // Determine number of bits to read bit allocation coding parameter
    if (c->storage_bit_res > 16)
        c->nabits = 5;
    else if (c->storage_bit_res > 8)
        c->nabits = 4;
    else
        c->nabits = 3;

    // Account for embedded downmix and decimator saturation
    if ((s->nchsets > 1 || c->nfreqbands > 1) && c->nabits < 5)
        c->nabits++;

    for (band = 0, b = c->bands; band < c->nfreqbands; band++, b++) {
        // Pairwise channel decorrelation
        if ((b->decor_enabled = get_bits1(&s->gb)) && c->nchannels > 1) {
            int ch_nbits = av_ceil_log2(c->nchannels);

            // Original channel order
            for (i = 0; i < c->nchannels; i++) {
                b->orig_order[i] = get_bits(&s->gb, ch_nbits);
                if (b->orig_order[i] >= c->nchannels) {
                    av_log(s->avctx, AV_LOG_ERROR, "Invalid XLL original channel order\n");
                    return AVERROR_INVALIDDATA;
                }
            }

            // Pairwise channel coefficients
            for (i = 0; i < c->nchannels / 2; i++)
                b->decor_coeff[i] = get_bits1(&s->gb) ? get_linear(&s->gb, 7) : 0;
        } else {
            for (i = 0; i < c->nchannels; i++)
                b->orig_order[i] = i;
            for (i = 0; i < c->nchannels / 2; i++)
                b->decor_coeff[i] = 0;
        }

        // Adaptive predictor order
        b->highest_pred_order = 0;
        for (i = 0; i < c->nchannels; i++) {
            b->adapt_pred_order[i] = get_bits(&s->gb, 4);
            if (b->adapt_pred_order[i] > b->highest_pred_order)
                b->highest_pred_order = b->adapt_pred_order[i];
        }
        if (b->highest_pred_order > s->nsegsamples) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid XLL adaptive predicition order\n");
            return AVERROR_INVALIDDATA;
        }

        // Fixed predictor order
        for (i = 0; i < c->nchannels; i++)
            b->fixed_pred_order[i] = b->adapt_pred_order[i] ? 0 : get_bits(&s->gb, 2);

        // Adaptive predictor quantized reflection coefficients
        for (i = 0; i < c->nchannels; i++) {
            for (j = 0; j < b->adapt_pred_order[i]; j++) {
                k = get_linear(&s->gb, 8);
                if (k == -128) {
                    av_log(s->avctx, AV_LOG_ERROR, "Invalid XLL reflection coefficient index\n");
                    return AVERROR_INVALIDDATA;
                }
                if (k < 0)
                    b->adapt_refl_coeff[i][j] = -(int)ff_dca_xll_refl_coeff[-k];
                else
                    b->adapt_refl_coeff[i][j] =  (int)ff_dca_xll_refl_coeff[ k];
            }
        }

        // Downmix performed by encoder in extension frequency band
        b->dmix_embedded = c->dmix_embedded && (band == 0 || get_bits1(&s->gb));

        // MSB/LSB split flag in extension frequency band
        if ((band == 0 && s->scalable_lsbs) || (band != 0 && get_bits1(&s->gb))) {
            // Size of LSB section in any segment
            b->lsb_section_size = get_bits_long(&s->gb, s->seg_size_nbits);
            if (b->lsb_section_size < 0 || b->lsb_section_size > s->frame_size) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid LSB section size\n");
                return AVERROR_INVALIDDATA;
            }

            // Account for optional CRC bytes after LSB section
            if (b->lsb_section_size && (s->band_crc_present > 2 ||
                                        (band == 0 && s->band_crc_present > 1)))
                b->lsb_section_size += 2;

            // Number of bits to represent the samples in LSB part
            for (i = 0; i < c->nchannels; i++) {
                b->nscalablelsbs[i] = get_bits(&s->gb, 4);
                if (b->nscalablelsbs[i] && !b->lsb_section_size) {
                    av_log(s->avctx, AV_LOG_ERROR, "LSB section missing with non-zero LSB width\n");
                    return AVERROR_INVALIDDATA;
                }
            }
        } else {
            b->lsb_section_size = 0;
            for (i = 0; i < c->nchannels; i++)
                b->nscalablelsbs[i] = 0;
        }

        // Scalable resolution flag in extension frequency band
        if ((band == 0 && s->scalable_lsbs) || (band != 0 && get_bits1(&s->gb))) {
            // Number of bits discarded by authoring
            for (i = 0; i < c->nchannels; i++)
                b->bit_width_adjust[i] = get_bits(&s->gb, 4);
        } else {
            for (i = 0; i < c->nchannels; i++)
                b->bit_width_adjust[i] = 0;
        }
    }

    // Reserved
    // Byte align
    // CRC16 of channel set sub-header
    if (ff_dca_seek_bits(&s->gb, header_pos + header_size * 8)) {
        av_log(s->avctx, AV_LOG_ERROR, "Read past end of XLL sub-header\n");
        return AVERROR_INVALIDDATA;
    }

    return 0;
}