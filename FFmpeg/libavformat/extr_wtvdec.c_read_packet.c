#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pts; int /*<<< orphan*/ * pb; } ;
typedef  TYPE_1__ WtvContext ;
struct TYPE_10__ {TYPE_1__* priv_data; } ;
struct TYPE_9__ {int stream_index; int /*<<< orphan*/  pts; } ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_TO_DATA ; 
 scalar_t__ WTV_PAD8 (int) ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,scalar_t__) ; 
 int parse_chunks (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s, AVPacket *pkt)
{
    WtvContext *wtv = s->priv_data;
    AVIOContext *pb = wtv->pb;
    int stream_index, len, ret;

    stream_index = parse_chunks(s, SEEK_TO_DATA, 0, &len);
    if (stream_index < 0)
        return stream_index;

    ret = av_get_packet(pb, pkt, len - 32);
    if (ret < 0)
        return ret;
    pkt->stream_index = stream_index;
    pkt->pts          = wtv->pts;
    avio_skip(pb, WTV_PAD8(len) - len);
    return 0;
}