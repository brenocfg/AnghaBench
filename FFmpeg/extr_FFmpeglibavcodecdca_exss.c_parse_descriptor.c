#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int asset_index; int pcm_bit_res; int nchannels_total; int one_to_one_map_ch_to_spkr; int embedded_stereo; int embedded_6ch; int spkr_mask_enabled; int spkr_mask; int representation_type; int coding_mode; int extension_mask; int core_size; int xbr_size; int xxch_size; int x96_size; int hd_stream_id; int /*<<< orphan*/  max_sample_rate; } ;
struct TYPE_9__ {int nmixoutconfigs; int* nmixoutchs; scalar_t__ avctx; int /*<<< orphan*/  gb; scalar_t__ mix_metadata_enabled; scalar_t__ static_fields_present; } ;
typedef  TYPE_1__ DCAExssParser ;
typedef  TYPE_2__ DCAExssAsset ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int DCA_EXSS_CORE ; 
 int DCA_EXSS_LBR ; 
 int DCA_EXSS_RSV1 ; 
 int DCA_EXSS_RSV2 ; 
 int DCA_EXSS_X96 ; 
 int DCA_EXSS_XBR ; 
 int DCA_EXSS_XLL ; 
 int DCA_EXSS_XXCH ; 
 int /*<<< orphan*/  av_log (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int av_popcount (int) ; 
 int ff_dca_count_chs_for_mask (int) ; 
 int /*<<< orphan*/ * ff_dca_sampling_freqs ; 
 scalar_t__ ff_dca_seek_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  parse_lbr_parameters (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  parse_xll_parameters (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_descriptor(DCAExssParser *s, DCAExssAsset *asset)
{
    int i, j, drc_present, descr_size, descr_pos = get_bits_count(&s->gb);

    // Size of audio asset descriptor in bytes
    descr_size = get_bits(&s->gb, 9) + 1;

    // Audio asset identifier
    asset->asset_index = get_bits(&s->gb, 3);

    //
    // Per stream static metadata
    //

    if (s->static_fields_present) {
        // Asset type descriptor presence
        if (get_bits1(&s->gb))
            // Asset type descriptor
            skip_bits(&s->gb, 4);

        // Language descriptor presence
        if (get_bits1(&s->gb))
            // Language descriptor
            skip_bits(&s->gb, 24);

        // Additional textual information presence
        if (get_bits1(&s->gb)) {
            // Byte size of additional text info
            int text_size = get_bits(&s->gb, 10) + 1;

            // Sanity check available size
            if (get_bits_left(&s->gb) < text_size * 8)
                return AVERROR_INVALIDDATA;

            // Additional textual information string
            skip_bits_long(&s->gb, text_size * 8);
        }

        // PCM bit resolution
        asset->pcm_bit_res = get_bits(&s->gb, 5) + 1;

        // Maximum sample rate
        asset->max_sample_rate = ff_dca_sampling_freqs[get_bits(&s->gb, 4)];

        // Total number of channels
        asset->nchannels_total = get_bits(&s->gb, 8) + 1;

        // One to one map channel to speakers
        if (asset->one_to_one_map_ch_to_spkr = get_bits1(&s->gb)) {
            int spkr_mask_nbits = 0;
            int spkr_remap_nsets;
            int nspeakers[8];

            // Embedded stereo flag
            asset->embedded_stereo = asset->nchannels_total > 2 && get_bits1(&s->gb);

            // Embedded 6 channels flag
            asset->embedded_6ch = asset->nchannels_total > 6 && get_bits1(&s->gb);

            // Speaker mask enabled flag
            if (asset->spkr_mask_enabled = get_bits1(&s->gb)) {
                // Number of bits for speaker activity mask
                spkr_mask_nbits = (get_bits(&s->gb, 2) + 1) << 2;

                // Loudspeaker activity mask
                asset->spkr_mask = get_bits(&s->gb, spkr_mask_nbits);
            }

            // Number of speaker remapping sets
            if ((spkr_remap_nsets = get_bits(&s->gb, 3)) && !spkr_mask_nbits) {
                if (s->avctx)
                    av_log(s->avctx, AV_LOG_ERROR, "Speaker mask disabled yet there are remapping sets\n");
                return AVERROR_INVALIDDATA;
            }

            // Standard loudspeaker layout mask
            for (i = 0; i < spkr_remap_nsets; i++)
                nspeakers[i] = ff_dca_count_chs_for_mask(get_bits(&s->gb, spkr_mask_nbits));

            for (i = 0; i < spkr_remap_nsets; i++) {
                // Number of channels to be decoded for speaker remapping
                int nch_for_remaps = get_bits(&s->gb, 5) + 1;

                for (j = 0; j < nspeakers[i]; j++) {
                    // Decoded channels to output speaker mapping mask
                    int remap_ch_mask = get_bits_long(&s->gb, nch_for_remaps);

                    // Loudspeaker remapping codes
                    skip_bits_long(&s->gb, av_popcount(remap_ch_mask) * 5);
                }
            }
        } else {
            asset->embedded_stereo = 0;
            asset->embedded_6ch = 0;
            asset->spkr_mask_enabled = 0;
            asset->spkr_mask = 0;

            // Representation type
            asset->representation_type = get_bits(&s->gb, 3);
        }
    }

    //
    // DRC, DNC and mixing metadata
    //

    // Dynamic range coefficient presence flag
    drc_present = get_bits1(&s->gb);

    // Code for dynamic range coefficient
    if (drc_present)
        skip_bits(&s->gb, 8);

    // Dialog normalization presence flag
    if (get_bits1(&s->gb))
        // Dialog normalization code
        skip_bits(&s->gb, 5);

    // DRC for stereo downmix
    if (drc_present && asset->embedded_stereo)
        skip_bits(&s->gb, 8);

    // Mixing metadata presence flag
    if (s->mix_metadata_enabled && get_bits1(&s->gb)) {
        int nchannels_dmix;

        // External mixing flag
        skip_bits1(&s->gb);

        // Post mixing / replacement gain adjustment
        skip_bits(&s->gb, 6);

        // DRC prior to mixing
        if (get_bits(&s->gb, 2) == 3)
            // Custom code for mixing DRC
            skip_bits(&s->gb, 8);
        else
            // Limit for mixing DRC
            skip_bits(&s->gb, 3);

        // Scaling type for channels of main audio
        // Scaling parameters of main audio
        if (get_bits1(&s->gb))
            for (i = 0; i < s->nmixoutconfigs; i++)
                skip_bits_long(&s->gb, 6 * s->nmixoutchs[i]);
        else
            skip_bits_long(&s->gb, 6 * s->nmixoutconfigs);

        nchannels_dmix = asset->nchannels_total;
        if (asset->embedded_6ch)
            nchannels_dmix += 6;
        if (asset->embedded_stereo)
            nchannels_dmix += 2;

        for (i = 0; i < s->nmixoutconfigs; i++) {
            if (!s->nmixoutchs[i]) {
                if (s->avctx)
                    av_log(s->avctx, AV_LOG_ERROR, "Invalid speaker layout mask for mixing configuration\n");
                return AVERROR_INVALIDDATA;
            }
            for (j = 0; j < nchannels_dmix; j++) {
                // Mix output mask
                int mix_map_mask = get_bits(&s->gb, s->nmixoutchs[i]);

                // Mixing coefficients
                skip_bits_long(&s->gb, av_popcount(mix_map_mask) * 6);
            }
        }
    }

    //
    // Decoder navigation data
    //

    // Coding mode for the asset
    asset->coding_mode = get_bits(&s->gb, 2);

    // Coding components used in asset
    switch (asset->coding_mode) {
    case 0: // Coding mode that may contain multiple coding components
        asset->extension_mask = get_bits(&s->gb, 12);

        if (asset->extension_mask & DCA_EXSS_CORE) {
            // Size of core component in extension substream
            asset->core_size = get_bits(&s->gb, 14) + 1;
            // Core sync word present flag
            if (get_bits1(&s->gb))
                // Core sync distance
                skip_bits(&s->gb, 2);
        }

        if (asset->extension_mask & DCA_EXSS_XBR)
            // Size of XBR extension in extension substream
            asset->xbr_size = get_bits(&s->gb, 14) + 1;

        if (asset->extension_mask & DCA_EXSS_XXCH)
            // Size of XXCH extension in extension substream
            asset->xxch_size = get_bits(&s->gb, 14) + 1;

        if (asset->extension_mask & DCA_EXSS_X96)
            // Size of X96 extension in extension substream
            asset->x96_size = get_bits(&s->gb, 12) + 1;

        if (asset->extension_mask & DCA_EXSS_LBR)
            parse_lbr_parameters(s, asset);

        if (asset->extension_mask & DCA_EXSS_XLL)
            parse_xll_parameters(s, asset);

        if (asset->extension_mask & DCA_EXSS_RSV1)
            skip_bits(&s->gb, 16);

        if (asset->extension_mask & DCA_EXSS_RSV2)
            skip_bits(&s->gb, 16);
        break;

    case 1: // Loss-less coding mode without CBR component
        asset->extension_mask = DCA_EXSS_XLL;
        parse_xll_parameters(s, asset);
        break;

    case 2: // Low bit rate mode
        asset->extension_mask = DCA_EXSS_LBR;
        parse_lbr_parameters(s, asset);
        break;

    case 3: // Auxiliary coding mode
        asset->extension_mask = 0;

        // Size of auxiliary coded data
        skip_bits(&s->gb, 14);

        // Auxiliary codec identification
        skip_bits(&s->gb, 8);

        // Aux sync word present flag
        if (get_bits1(&s->gb))
            // Aux sync distance
            skip_bits(&s->gb, 3);
        break;
    }

    if (asset->extension_mask & DCA_EXSS_XLL)
        // DTS-HD stream ID
        asset->hd_stream_id = get_bits(&s->gb, 3);

    // One to one mixing flag
    // Per channel main audio scaling flag
    // Main audio scaling codes
    // Decode asset in secondary decoder flag
    // Revision 2 DRC metadata
    // Reserved
    // Zero pad
    if (ff_dca_seek_bits(&s->gb, descr_pos + descr_size * 8)) {
        if (s->avctx)
            av_log(s->avctx, AV_LOG_ERROR, "Read past end of EXSS asset descriptor\n");
        return AVERROR_INVALIDDATA;
    }

    return 0;
}