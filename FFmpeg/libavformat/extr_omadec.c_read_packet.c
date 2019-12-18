#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_15__ {int /*<<< orphan*/  pb; TYPE_4__** streams; TYPE_3__* priv_data; } ;
struct TYPE_14__ {int /*<<< orphan*/  data; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; scalar_t__ stream_index; int /*<<< orphan*/  flags; } ;
struct TYPE_11__ {scalar_t__ num; int /*<<< orphan*/  den; } ;
struct TYPE_13__ {TYPE_2__ time_base; TYPE_1__* codecpar; } ;
struct TYPE_12__ {scalar_t__ content_start; int /*<<< orphan*/  iv; int /*<<< orphan*/  av_des; scalar_t__ encrypted; } ;
struct TYPE_10__ {int block_align; int bit_rate; } ;
typedef  TYPE_3__ OMAContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_PKT_FLAG_CORRUPT ; 
 int /*<<< orphan*/  av_des_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  av_rescale (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s, AVPacket *pkt)
{
    OMAContext *oc  = s->priv_data;
    AVStream *st    = s->streams[0];
    int packet_size = st->codecpar->block_align;
    int byte_rate   = st->codecpar->bit_rate >> 3;
    int64_t pos     = avio_tell(s->pb);
    int ret         = av_get_packet(s->pb, pkt, packet_size);

    if (ret < packet_size)
        pkt->flags |= AV_PKT_FLAG_CORRUPT;

    if (ret < 0)
        return ret;
    if (!ret)
        return AVERROR_EOF;

    pkt->stream_index = 0;

    if (pos >= oc->content_start && byte_rate > 0) {
        pkt->pts =
        pkt->dts = av_rescale(pos - oc->content_start, st->time_base.den,
                              byte_rate * (int64_t)st->time_base.num);
    }

    if (oc->encrypted) {
        /* previous unencrypted block saved in IV for
         * the next packet (CBC mode) */
        if (ret == packet_size)
            av_des_crypt(oc->av_des, pkt->data, pkt->data,
                         (packet_size >> 3), oc->iv, 1);
        else
            memset(oc->iv, 0, 8);
    }

    return ret;
}