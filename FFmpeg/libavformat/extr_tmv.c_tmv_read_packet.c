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
struct TYPE_9__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int stream_index; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int stream_index; int audio_chunk_size; int video_chunk_size; int /*<<< orphan*/  padding; } ;
typedef  TYPE_1__ TMVContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tmv_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    TMVContext *tmv   = s->priv_data;
    AVIOContext *pb = s->pb;
    int ret, pkt_size = tmv->stream_index ?
                        tmv->audio_chunk_size : tmv->video_chunk_size;

    if (avio_feof(pb))
        return AVERROR_EOF;

    ret = av_get_packet(pb, pkt, pkt_size);

    if (tmv->stream_index)
        avio_skip(pb, tmv->padding);

    pkt->stream_index  = tmv->stream_index;
    tmv->stream_index ^= 1;
    pkt->flags        |= AV_PKT_FLAG_KEY;

    return ret;
}