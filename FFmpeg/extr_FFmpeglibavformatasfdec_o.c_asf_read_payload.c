#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_21__ {int sub_left; int stream_index; int nb_streams; scalar_t__ packet_offset; scalar_t__ packet_size; scalar_t__ data_offset; scalar_t__ data_size; int prop_flags; scalar_t__ rep_data_len; TYPE_1__** asf_st; int /*<<< orphan*/  state; scalar_t__ nb_mult_left; scalar_t__ sub_dts; } ;
struct TYPE_20__ {scalar_t__ frame_num; int /*<<< orphan*/  dts; int /*<<< orphan*/  flags; scalar_t__ size_left; int /*<<< orphan*/  stream_index; } ;
struct TYPE_19__ {int /*<<< orphan*/ * pb; TYPE_5__* priv_data; } ;
struct TYPE_18__ {int /*<<< orphan*/  stream_index; int /*<<< orphan*/  dts; int /*<<< orphan*/  flags; } ;
struct TYPE_17__ {int stream_index; int /*<<< orphan*/  index; TYPE_4__ pkt; } ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ ASFPacket ;
typedef  TYPE_5__ ASFContext ;

/* Variables and functions */
 int /*<<< orphan*/  ASF_PL_FLAG_MEDIA_OBJECT_NUMBER_LENGTH_FIELD_ ; 
 int /*<<< orphan*/  ASF_PL_FLAG_OFFSET_INTO_MEDIA_OBJECT_LENGTH_FIELD_ ; 
 int /*<<< orphan*/  ASF_PL_FLAG_REPLICATED_DATA_LENGTH_FIELD_ ; 
 int ASF_PL_MASK_MEDIA_OBJECT_NUMBER_LENGTH_FIELD_SIZE ; 
 int ASF_PL_MASK_OFFSET_INTO_MEDIA_OBJECT_LENGTH_FIELD_SIZE ; 
 int ASF_PL_MASK_REPLICATED_DATA_LENGTH_FIELD_SIZE ; 
 int ASF_STREAM_NUM ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  READ_LEN (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  READ_SINGLE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int asf_read_multiple_payload (TYPE_3__*,TYPE_2__*,TYPE_4__*) ; 
 int asf_read_single_payload (TYPE_3__*,TYPE_4__*) ; 
 int asf_read_subpayload (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_packet (TYPE_4__*) ; 

__attribute__((used)) static int asf_read_payload(AVFormatContext *s, AVPacket *pkt)
{
    ASFContext *asf = s->priv_data;
    AVIOContext *pb = s->pb;
    int ret, i;
    ASFPacket *asf_pkt = NULL;

    if (!asf->sub_left) {
        uint32_t off_len, media_len;
        uint8_t stream_num;

        stream_num = avio_r8(pb);
        asf->stream_index = stream_num & ASF_STREAM_NUM;
        for (i = 0; i < asf->nb_streams; i++) {
            if (asf->stream_index == asf->asf_st[i]->stream_index) {
                asf_pkt               = &asf->asf_st[i]->pkt;
                asf_pkt->stream_index = asf->asf_st[i]->index;
                break;
            }
        }
        if (!asf_pkt) {
            if (asf->packet_offset + asf->packet_size <= asf->data_offset + asf->data_size) {
                if (!asf->packet_size) {
                    av_log(s, AV_LOG_ERROR, "Invalid packet size 0.\n");
                    return AVERROR_INVALIDDATA;
                }
                avio_seek(pb, asf->packet_offset + asf->packet_size, SEEK_SET);
                av_log(s, AV_LOG_WARNING, "Skipping the stream with the invalid stream index %d.\n",
                       asf->stream_index);
                return AVERROR(EAGAIN);
            } else
                return AVERROR_INVALIDDATA;
        }

        if (stream_num >> 7)
            asf_pkt->flags |= AV_PKT_FLAG_KEY;
        READ_LEN(asf->prop_flags & ASF_PL_MASK_MEDIA_OBJECT_NUMBER_LENGTH_FIELD_SIZE,
                 ASF_PL_FLAG_MEDIA_OBJECT_NUMBER_LENGTH_FIELD_, media_len);
        READ_LEN(asf->prop_flags & ASF_PL_MASK_OFFSET_INTO_MEDIA_OBJECT_LENGTH_FIELD_SIZE,
                 ASF_PL_FLAG_OFFSET_INTO_MEDIA_OBJECT_LENGTH_FIELD_, off_len);
        READ_LEN(asf->prop_flags & ASF_PL_MASK_REPLICATED_DATA_LENGTH_FIELD_SIZE,
                 ASF_PL_FLAG_REPLICATED_DATA_LENGTH_FIELD_, asf->rep_data_len);
        if (asf_pkt->size_left && (asf_pkt->frame_num != media_len)) {
            av_log(s, AV_LOG_WARNING, "Unfinished frame will be ignored\n");
            reset_packet(asf_pkt);
        }
        asf_pkt->frame_num = media_len;
        asf->sub_dts = off_len;
        if (asf->nb_mult_left) {
            if ((ret = asf_read_multiple_payload(s, pkt, asf_pkt)) < 0)
                return ret;
        } else if (asf->rep_data_len == 1) {
            asf->sub_left = 1;
            asf->state    = READ_SINGLE;
            pkt->flags    = asf_pkt->flags;
            if ((ret = asf_read_subpayload(s, pkt, 1)) < 0)
                return ret;
        } else {
            if ((ret = asf_read_single_payload(s, asf_pkt)) < 0)
                return ret;
        }
    } else {
        for (i = 0; i <= asf->nb_streams; i++) {
            if (asf->stream_index == asf->asf_st[i]->stream_index) {
                asf_pkt = &asf->asf_st[i]->pkt;
                break;
            }
        }
        if (!asf_pkt)
            return AVERROR_INVALIDDATA;
        pkt->flags         = asf_pkt->flags;
        pkt->dts           = asf_pkt->dts;
        pkt->stream_index  = asf->asf_st[i]->index;
        if ((ret = asf_read_subpayload(s, pkt, 0)) < 0) // read subpayload without its header
            return ret;
    }

    return 0;
}