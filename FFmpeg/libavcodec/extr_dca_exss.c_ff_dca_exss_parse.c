#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int asset_offset; int asset_size; } ;
struct TYPE_6__ {int exss_index; int exss_size_nbits; int exss_size; int static_fields_present; int npresents; int nassets; int mix_metadata_enabled; int nmixoutconfigs; scalar_t__ avctx; int /*<<< orphan*/  gb; TYPE_2__* assets; int /*<<< orphan*/ * nmixoutchs; } ;
typedef  TYPE_1__ DCAExssParser ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int av_popcount (int) ; 
 int /*<<< orphan*/  avpriv_request_sample (scalar_t__,char*,int) ; 
 scalar_t__ ff_dca_check_crc (scalar_t__,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ff_dca_count_chs_for_mask (int) ; 
 scalar_t__ ff_dca_seek_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int parse_descriptor (TYPE_1__*,TYPE_2__*) ; 
 int set_exss_offsets (TYPE_2__*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

int ff_dca_exss_parse(DCAExssParser *s, const uint8_t *data, int size)
{
    int i, ret, offset, wide_hdr, header_size;

    if ((ret = init_get_bits8(&s->gb, data, size)) < 0)
        return ret;

    // Extension substream sync word
    skip_bits_long(&s->gb, 32);

    // User defined bits
    skip_bits(&s->gb, 8);

    // Extension substream index
    s->exss_index = get_bits(&s->gb, 2);

    // Flag indicating short or long header size
    wide_hdr = get_bits1(&s->gb);

    // Extension substream header length
    header_size = get_bits(&s->gb, 8 + 4 * wide_hdr) + 1;

    // Check CRC
    if (s->avctx && ff_dca_check_crc(s->avctx, &s->gb, 32 + 8, header_size * 8)) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid EXSS header checksum\n");
        return AVERROR_INVALIDDATA;
    }

    s->exss_size_nbits = 16 + 4 * wide_hdr;

    // Number of bytes of extension substream
    s->exss_size = get_bits(&s->gb, s->exss_size_nbits) + 1;
    if (s->exss_size > size) {
        if (s->avctx)
            av_log(s->avctx, AV_LOG_ERROR, "Packet too short for EXSS frame\n");
        return AVERROR_INVALIDDATA;
    }

    // Per stream static fields presence flag
    if (s->static_fields_present = get_bits1(&s->gb)) {
        int active_exss_mask[8];

        // Reference clock code
        skip_bits(&s->gb, 2);

        // Extension substream frame duration
        skip_bits(&s->gb, 3);

        // Timecode presence flag
        if (get_bits1(&s->gb))
            // Timecode data
            skip_bits_long(&s->gb, 36);

        // Number of defined audio presentations
        s->npresents = get_bits(&s->gb, 3) + 1;
        if (s->npresents > 1) {
            if (s->avctx)
                avpriv_request_sample(s->avctx, "%d audio presentations", s->npresents);
            return AVERROR_PATCHWELCOME;
        }

        // Number of audio assets in extension substream
        s->nassets = get_bits(&s->gb, 3) + 1;
        if (s->nassets > 1) {
            if (s->avctx)
                avpriv_request_sample(s->avctx, "%d audio assets", s->nassets);
            return AVERROR_PATCHWELCOME;
        }

        // Active extension substream mask for audio presentation
        for (i = 0; i < s->npresents; i++)
            active_exss_mask[i] = get_bits(&s->gb, s->exss_index + 1);

        // Active audio asset mask
        for (i = 0; i < s->npresents; i++)
            skip_bits_long(&s->gb, av_popcount(active_exss_mask[i]) * 8);

        // Mixing metadata enable flag
        if (s->mix_metadata_enabled = get_bits1(&s->gb)) {
            int spkr_mask_nbits;

            // Mixing metadata adjustment level
            skip_bits(&s->gb, 2);

            // Number of bits for mixer output speaker activity mask
            spkr_mask_nbits = (get_bits(&s->gb, 2) + 1) << 2;

            // Number of mixing configurations
            s->nmixoutconfigs = get_bits(&s->gb, 2) + 1;

            // Speaker layout mask for mixer output channels
            for (i = 0; i < s->nmixoutconfigs; i++)
                s->nmixoutchs[i] = ff_dca_count_chs_for_mask(get_bits(&s->gb, spkr_mask_nbits));
        }
    } else {
        s->npresents = 1;
        s->nassets = 1;
    }

    // Size of encoded asset data in bytes
    offset = header_size;
    for (i = 0; i < s->nassets; i++) {
        s->assets[i].asset_offset = offset;
        s->assets[i].asset_size = get_bits(&s->gb, s->exss_size_nbits) + 1;
        offset += s->assets[i].asset_size;
        if (offset > s->exss_size) {
            if (s->avctx)
                av_log(s->avctx, AV_LOG_ERROR, "EXSS asset out of bounds\n");
            return AVERROR_INVALIDDATA;
        }
    }

    // Audio asset descriptor
    for (i = 0; i < s->nassets; i++) {
        if ((ret = parse_descriptor(s, &s->assets[i])) < 0)
            return ret;
        if ((ret = set_exss_offsets(&s->assets[i])) < 0) {
            if (s->avctx)
                av_log(s->avctx, AV_LOG_ERROR, "Invalid extension size in EXSS asset descriptor\n");
            return ret;
        }
    }

    // Backward compatible core present
    // Backward compatible core substream index
    // Backward compatible core asset index
    // Reserved
    // Byte align
    // CRC16 of extension substream header
    if (ff_dca_seek_bits(&s->gb, header_size * 8)) {
        if (s->avctx)
            av_log(s->avctx, AV_LOG_ERROR, "Read past end of EXSS header\n");
        return AVERROR_INVALIDDATA;
    }

    return 0;
}