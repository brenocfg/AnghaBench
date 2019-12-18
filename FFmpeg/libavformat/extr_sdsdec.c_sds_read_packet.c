#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  pos; scalar_t__ stream_index; int /*<<< orphan*/  flags; scalar_t__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* read_block ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ SDSContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_PKT_FLAG_CORRUPT ; 
 int av_new_packet (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb16 (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sds_read_packet(AVFormatContext *ctx, AVPacket *pkt)
{
    SDSContext *s = ctx->priv_data;
    AVIOContext *pb = ctx->pb;
    int64_t pos;
    int ret;

    if (avio_feof(pb))
        return AVERROR_EOF;

    pos = avio_tell(pb);
    if (avio_rb16(pb) != 0xF07E)
        return AVERROR_INVALIDDATA;
    avio_skip(pb, 3);

    ret = av_new_packet(pkt, s->size);
    if (ret < 0)
        return ret;

    ret = avio_read(pb, s->data, 120);

    s->read_block(s->data, (uint32_t *)pkt->data);

    avio_skip(pb, 1); // checksum
    if (avio_r8(pb) != 0xF7)
        return AVERROR_INVALIDDATA;

    pkt->flags &= ~AV_PKT_FLAG_CORRUPT;
    pkt->stream_index = 0;
    pkt->pos = pos;

    return ret;
}