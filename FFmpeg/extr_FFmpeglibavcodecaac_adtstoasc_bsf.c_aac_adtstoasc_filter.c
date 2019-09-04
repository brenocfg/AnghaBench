#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_19__ {int num_aac_frames; int /*<<< orphan*/  chan_config; int /*<<< orphan*/  sampling_index; int /*<<< orphan*/  object_type; int /*<<< orphan*/  crc_absent; } ;
struct TYPE_18__ {int first_frame_done; } ;
struct TYPE_17__ {TYPE_1__* par_in; TYPE_4__* priv_data; } ;
struct TYPE_16__ {int size; int data; } ;
struct TYPE_15__ {scalar_t__ extradata; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVBSFContext ;
typedef  TYPE_4__ AACBSFContext ;
typedef  TYPE_5__ AACADTSHeaderInfo ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int AV_AAC_ADTS_HEADER_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_NEW_EXTRADATA ; 
 int AV_RB16 (int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MAX_PCE_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_3__*,char*) ; 
 scalar_t__ ff_adts_header_parse (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int ff_bsf_get_packet_ref (TYPE_3__*,TYPE_2__*) ; 
 int ff_copy_pce_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aac_adtstoasc_filter(AVBSFContext *bsfc, AVPacket *pkt)
{
    AACBSFContext *ctx = bsfc->priv_data;

    GetBitContext gb;
    PutBitContext pb;
    AACADTSHeaderInfo hdr;
    int ret;

    ret = ff_bsf_get_packet_ref(bsfc, pkt);
    if (ret < 0)
        return ret;

    if (bsfc->par_in->extradata && pkt->size >= 2 && (AV_RB16(pkt->data) >> 4) != 0xfff)
        return 0;

    if (pkt->size < AV_AAC_ADTS_HEADER_SIZE)
        goto packet_too_small;

    init_get_bits(&gb, pkt->data, AV_AAC_ADTS_HEADER_SIZE * 8);

    if (ff_adts_header_parse(&gb, &hdr) < 0) {
        av_log(bsfc, AV_LOG_ERROR, "Error parsing ADTS frame header!\n");
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    if (!hdr.crc_absent && hdr.num_aac_frames > 1) {
        avpriv_report_missing_feature(bsfc,
                                      "Multiple RDBs per frame with CRC");
        ret = AVERROR_PATCHWELCOME;
        goto fail;
    }

    pkt->size -= AV_AAC_ADTS_HEADER_SIZE + 2 * !hdr.crc_absent;
    if (pkt->size <= 0)
        goto packet_too_small;
    pkt->data += AV_AAC_ADTS_HEADER_SIZE + 2 * !hdr.crc_absent;

    if (!ctx->first_frame_done) {
        int            pce_size = 0;
        uint8_t        pce_data[MAX_PCE_SIZE];
        uint8_t       *extradata;

        if (!hdr.chan_config) {
            init_get_bits(&gb, pkt->data, pkt->size * 8);
            if (get_bits(&gb, 3) != 5) {
                avpriv_report_missing_feature(bsfc,
                                              "PCE-based channel configuration "
                                              "without PCE as first syntax "
                                              "element");
                ret = AVERROR_PATCHWELCOME;
                goto fail;
            }
            init_put_bits(&pb, pce_data, MAX_PCE_SIZE);
            pce_size = ff_copy_pce_data(&pb, &gb) / 8;
            flush_put_bits(&pb);
            pkt->size -= get_bits_count(&gb)/8;
            pkt->data += get_bits_count(&gb)/8;
        }

        extradata = av_packet_new_side_data(pkt, AV_PKT_DATA_NEW_EXTRADATA,
                                            2 + pce_size);
        if (!extradata) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        init_put_bits(&pb, extradata, 2 + pce_size);
        put_bits(&pb, 5, hdr.object_type);
        put_bits(&pb, 4, hdr.sampling_index);
        put_bits(&pb, 4, hdr.chan_config);
        put_bits(&pb, 1, 0); //frame length - 1024 samples
        put_bits(&pb, 1, 0); //does not depend on core coder
        put_bits(&pb, 1, 0); //is not extension
        flush_put_bits(&pb);
        if (pce_size) {
            memcpy(extradata + 2, pce_data, pce_size);
        }

        ctx->first_frame_done = 1;
    }

    return 0;

packet_too_small:
    av_log(bsfc, AV_LOG_ERROR, "Input packet too small\n");
    ret = AVERROR_INVALIDDATA;
fail:
    av_packet_unref(pkt);
    return ret;
}