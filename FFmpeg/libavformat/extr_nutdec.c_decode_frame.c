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

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_18__ {TYPE_1__** streams; int /*<<< orphan*/ * pb; } ;
struct TYPE_17__ {void* pos; int size; int stream_index; scalar_t__ pts; int /*<<< orphan*/  flags; scalar_t__ data; } ;
struct TYPE_16__ {scalar_t__* header_len; scalar_t__* header; TYPE_2__* stream; TYPE_5__* avf; } ;
struct TYPE_15__ {int last_flags; scalar_t__ skip_until_key_frame; } ;
struct TYPE_14__ {int discard; scalar_t__ last_IP_pts; } ;
typedef  TYPE_2__ StreamContext ;
typedef  TYPE_3__ NUTContext ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVDISCARD_ALL ; 
 int AVDISCARD_BIDIR ; 
 int AVDISCARD_NONKEY ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int FLAG_KEY ; 
 int FLAG_SM_DATA ; 
 int av_new_packet (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_4__*) ; 
 int /*<<< orphan*/  av_shrink_packet (TYPE_4__*,scalar_t__) ; 
 int avio_read (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 void* avio_tell (int /*<<< orphan*/ *) ; 
 int decode_frame_header (TYPE_3__*,scalar_t__*,int*,size_t*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ read_sm_data (TYPE_5__*,int /*<<< orphan*/ *,TYPE_4__*,int,void*) ; 

__attribute__((used)) static int decode_frame(NUTContext *nut, AVPacket *pkt, int frame_code)
{
    AVFormatContext *s = nut->avf;
    AVIOContext *bc    = s->pb;
    int size, stream_id, discard, ret;
    int64_t pts, last_IP_pts;
    StreamContext *stc;
    uint8_t header_idx;

    size = decode_frame_header(nut, &pts, &stream_id, &header_idx, frame_code);
    if (size < 0)
        return size;

    stc = &nut->stream[stream_id];

    if (stc->last_flags & FLAG_KEY)
        stc->skip_until_key_frame = 0;

    discard     = s->streams[stream_id]->discard;
    last_IP_pts = s->streams[stream_id]->last_IP_pts;
    if ((discard >= AVDISCARD_NONKEY && !(stc->last_flags & FLAG_KEY)) ||
        (discard >= AVDISCARD_BIDIR  && last_IP_pts != AV_NOPTS_VALUE &&
         last_IP_pts > pts) ||
        discard >= AVDISCARD_ALL ||
        stc->skip_until_key_frame) {
        avio_skip(bc, size);
        return 1;
    }

    ret = av_new_packet(pkt, size + nut->header_len[header_idx]);
    if (ret < 0)
        return ret;
    if (nut->header[header_idx])
        memcpy(pkt->data, nut->header[header_idx], nut->header_len[header_idx]);
    pkt->pos = avio_tell(bc); // FIXME
    if (stc->last_flags & FLAG_SM_DATA) {
        int sm_size;
        if (read_sm_data(s, bc, pkt, 0, pkt->pos + size) < 0) {
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }
        if (read_sm_data(s, bc, pkt, 1, pkt->pos + size) < 0) {
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }
        sm_size = avio_tell(bc) - pkt->pos;
        size      -= sm_size;
        pkt->size -= sm_size;
    }

    ret = avio_read(bc, pkt->data + nut->header_len[header_idx], size);
    if (ret != size) {
        if (ret < 0)
            goto fail;
    }
    av_shrink_packet(pkt, nut->header_len[header_idx] + ret);

    pkt->stream_index = stream_id;
    if (stc->last_flags & FLAG_KEY)
        pkt->flags |= AV_PKT_FLAG_KEY;
    pkt->pts = pts;

    return 0;
fail:
    av_packet_unref(pkt);
    return ret;
}