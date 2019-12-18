#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int temporal_unit_size; int frame_unit_size; int /*<<< orphan*/  bsf; } ;
typedef  TYPE_1__ AnnexBContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int av_bsf_receive_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int av_bsf_send_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int av_get_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 
 int leb (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int annexb_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    AnnexBContext *c = s->priv_data;
    uint32_t obu_unit_size;
    int ret, len;

retry:
    if (avio_feof(s->pb)) {
        if (c->temporal_unit_size || c->frame_unit_size)
            return AVERROR(EIO);
        av_bsf_send_packet(c->bsf, NULL);
        goto end;
    }

    if (!c->temporal_unit_size) {
        len = leb(s->pb, &c->temporal_unit_size);
        if (len < 0) return AVERROR_INVALIDDATA;
    }

    if (!c->frame_unit_size) {
        len = leb(s->pb, &c->frame_unit_size);
        if (len < 0 || ((int64_t)c->frame_unit_size + len) > c->temporal_unit_size)
            return AVERROR_INVALIDDATA;
        c->temporal_unit_size -= len;
    }

    len = leb(s->pb, &obu_unit_size);
    if (len < 0 || ((int64_t)obu_unit_size + len) > c->frame_unit_size)
        return AVERROR_INVALIDDATA;

    ret = av_get_packet(s->pb, pkt, obu_unit_size);
    if (ret < 0)
        return ret;
    if (ret != obu_unit_size)
        return AVERROR(EIO);

    c->temporal_unit_size -= obu_unit_size + len;
    c->frame_unit_size -= obu_unit_size + len;

    ret = av_bsf_send_packet(c->bsf, pkt);
    if (ret < 0) {
        av_log(s, AV_LOG_ERROR, "Failed to send packet to "
                                "av1_frame_merge filter\n");
        return ret;
    }

end:
    ret = av_bsf_receive_packet(c->bsf, pkt);
    if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
        av_log(s, AV_LOG_ERROR, "av1_frame_merge filter failed to "
                                "send output packet\n");

    if (ret == AVERROR(EAGAIN))
        goto retry;

    return ret;
}