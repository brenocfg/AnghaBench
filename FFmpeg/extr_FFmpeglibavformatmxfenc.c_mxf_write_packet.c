#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_38__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;

/* Type definitions */
struct TYPE_47__ {int /*<<< orphan*/ * oformat; TYPE_5__** streams; int /*<<< orphan*/ * pb; TYPE_4__* priv_data; } ;
struct TYPE_46__ {size_t stream_index; int size; int /*<<< orphan*/  data; } ;
struct TYPE_45__ {int index; TYPE_1__* codecpar; TYPE_2__* priv_data; } ;
struct TYPE_44__ {int edit_units_count; int header_written; int body_offset; TYPE_38__* index_entries; scalar_t__ edit_unit_byte_count; scalar_t__ cbr_index; } ;
struct TYPE_43__ {int flags; int /*<<< orphan*/  temporal_ref; int /*<<< orphan*/  member_0; } ;
struct TYPE_42__ {int offset; int flags; int slice_offset; int /*<<< orphan*/  temporal_ref; } ;
struct TYPE_41__ {int frame_size; int /*<<< orphan*/  track_essence_element_key; } ;
struct TYPE_40__ {scalar_t__ codec_id; scalar_t__ codec_type; } ;
typedef  TYPE_2__ MXFStreamContext ;
typedef  TYPE_3__ MXFIndexEntry ;
typedef  TYPE_4__ MXFContext ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_DNXHD ; 
 scalar_t__ AV_CODEC_ID_DVVIDEO ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 scalar_t__ AV_CODEC_ID_PRORES ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int EDIT_UNITS_PER_BODY ; 
 int KAG_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_reallocp_array (TYPE_38__**,int,int) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  body_partition_key ; 
 int /*<<< orphan*/  ff_mxf_d10_muxer ; 
 int /*<<< orphan*/  ff_mxf_opatom_muxer ; 
 int /*<<< orphan*/  header_open_partition_key ; 
 int /*<<< orphan*/  klv_encode_ber4_length (int /*<<< orphan*/ *,int) ; 
 int klv_fill_size (int) ; 
 int /*<<< orphan*/  mxf_compute_edit_unit_byte_count (TYPE_7__*) ; 
 int /*<<< orphan*/  mxf_parse_dnxhd_frame (TYPE_7__*,TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  mxf_parse_dv_frame (TYPE_7__*,TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  mxf_parse_h264_frame (TYPE_7__*,TYPE_5__*,TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  mxf_parse_mpeg2_frame (TYPE_7__*,TYPE_5__*,TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  mxf_parse_prores_frame (TYPE_7__*,TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  mxf_write_d10_audio_packet (TYPE_7__*,TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  mxf_write_index_table_segment (TYPE_7__*) ; 
 int /*<<< orphan*/  mxf_write_klv_fill (TYPE_7__*) ; 
 int mxf_write_opatom_packet (TYPE_7__*,TYPE_6__*,TYPE_3__*) ; 
 int mxf_write_partition (TYPE_7__*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxf_write_system_item (TYPE_7__*) ; 

__attribute__((used)) static int mxf_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st = s->streams[pkt->stream_index];
    MXFStreamContext *sc = st->priv_data;
    MXFIndexEntry ie = {0};
    int err;

    if (!mxf->cbr_index && !mxf->edit_unit_byte_count && !(mxf->edit_units_count % EDIT_UNITS_PER_BODY)) {
        if ((err = av_reallocp_array(&mxf->index_entries, mxf->edit_units_count
                                     + EDIT_UNITS_PER_BODY, sizeof(*mxf->index_entries))) < 0) {
            mxf->edit_units_count = 0;
            av_log(s, AV_LOG_ERROR, "could not allocate index entries\n");
            return err;
        }
    }

    if (st->codecpar->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
        if (!mxf_parse_mpeg2_frame(s, st, pkt, &ie)) {
            av_log(s, AV_LOG_ERROR, "could not get mpeg2 profile and level\n");
            return -1;
        }
    } else if (st->codecpar->codec_id == AV_CODEC_ID_DNXHD) {
        if (!mxf_parse_dnxhd_frame(s, st, pkt)) {
            av_log(s, AV_LOG_ERROR, "could not get dnxhd profile\n");
            return -1;
        }
    } else if (st->codecpar->codec_id == AV_CODEC_ID_PRORES) {
        if (!mxf_parse_prores_frame(s, st, pkt)) {
            av_log(s, AV_LOG_ERROR, "could not get prores profile\n");
            return -1;
        }
    } else if (st->codecpar->codec_id == AV_CODEC_ID_DVVIDEO) {
        if (!mxf_parse_dv_frame(s, st, pkt)) {
            av_log(s, AV_LOG_ERROR, "could not get dv profile\n");
            return -1;
        }
    } else if (st->codecpar->codec_id == AV_CODEC_ID_H264) {
        if (!mxf_parse_h264_frame(s, st, pkt, &ie)) {
            av_log(s, AV_LOG_ERROR, "could not get h264 profile\n");
            return -1;
        }
    }

    if (mxf->cbr_index) {
        if (pkt->size != sc->frame_size && st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            av_log(s, AV_LOG_ERROR, "track %d: frame size does not match index unit size, %d != %d\n",
                   st->index, pkt->size, sc->frame_size);
            return -1;
        }
        if (!mxf->header_written)
            mxf_compute_edit_unit_byte_count(s);
    }

    if (s->oformat == &ff_mxf_opatom_muxer)
        return mxf_write_opatom_packet(s, pkt, &ie);

    if (!mxf->header_written) {
        if (mxf->edit_unit_byte_count) {
            if ((err = mxf_write_partition(s, 1, 2, header_open_partition_key, 1)) < 0)
                return err;
            mxf_write_klv_fill(s);
            mxf_write_index_table_segment(s);
        } else {
            if ((err = mxf_write_partition(s, 0, 0, header_open_partition_key, 1)) < 0)
                return err;
        }
        mxf->header_written = 1;
    }

    if (st->index == 0) {
        if (!mxf->edit_unit_byte_count &&
            (!mxf->edit_units_count || mxf->edit_units_count > EDIT_UNITS_PER_BODY) &&
            !(ie.flags & 0x33)) { // I-frame, GOP start
            mxf_write_klv_fill(s);
            if ((err = mxf_write_partition(s, 1, 2, body_partition_key, 0)) < 0)
                return err;
            mxf_write_klv_fill(s);
            mxf_write_index_table_segment(s);
        }

        mxf_write_klv_fill(s);
        mxf_write_system_item(s);

        if (!mxf->edit_unit_byte_count) {
            mxf->index_entries[mxf->edit_units_count].offset = mxf->body_offset;
            mxf->index_entries[mxf->edit_units_count].flags = ie.flags;
            mxf->index_entries[mxf->edit_units_count].temporal_ref = ie.temporal_ref;
            mxf->body_offset += KAG_SIZE; // size of system element
        }
        mxf->edit_units_count++;
    } else if (!mxf->edit_unit_byte_count && st->index == 1) {
        if (!mxf->edit_units_count) {
            av_log(s, AV_LOG_ERROR, "No packets in first stream\n");
            return AVERROR_PATCHWELCOME;
        }
        mxf->index_entries[mxf->edit_units_count-1].slice_offset =
            mxf->body_offset - mxf->index_entries[mxf->edit_units_count-1].offset;
    }

    mxf_write_klv_fill(s);
    avio_write(pb, sc->track_essence_element_key, 16); // write key
    if (s->oformat == &ff_mxf_d10_muxer &&
        st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
        mxf_write_d10_audio_packet(s, st, pkt);
    } else {
        klv_encode_ber4_length(pb, pkt->size); // write length
        avio_write(pb, pkt->data, pkt->size);
        mxf->body_offset += 16+4+pkt->size + klv_fill_size(16+4+pkt->size);
    }

    avio_flush(pb);

    return 0;
}