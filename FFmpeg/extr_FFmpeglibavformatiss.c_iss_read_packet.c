#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__** streams; int /*<<< orphan*/  pb; TYPE_3__* priv_data; } ;
struct TYPE_12__ {int pts; scalar_t__ stream_index; } ;
struct TYPE_11__ {int packet_size; int sample_start_pos; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {int channels; } ;
typedef  TYPE_3__ IssDemuxContext ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int avio_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iss_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    IssDemuxContext *iss = s->priv_data;
    int ret = av_get_packet(s->pb, pkt, iss->packet_size);

    if(ret != iss->packet_size)
        return AVERROR(EIO);

    pkt->stream_index = 0;
    pkt->pts = avio_tell(s->pb) - iss->sample_start_pos;
    if(s->streams[0]->codecpar->channels > 0)
        pkt->pts /= s->streams[0]->codecpar->channels*2;
    return 0;
}