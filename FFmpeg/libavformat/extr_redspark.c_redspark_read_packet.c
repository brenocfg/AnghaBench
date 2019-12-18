#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_14__ {int channels; } ;
struct TYPE_13__ {int /*<<< orphan*/  pb; TYPE_1__** streams; TYPE_2__* priv_data; } ;
struct TYPE_12__ {int duration; scalar_t__ stream_index; } ;
struct TYPE_11__ {scalar_t__ samples_count; } ;
struct TYPE_10__ {scalar_t__ duration; TYPE_5__* codecpar; } ;
typedef  TYPE_2__ RedSparkContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EIO ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int redspark_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVCodecParameters *par = s->streams[0]->codecpar;
    RedSparkContext *redspark = s->priv_data;
    uint32_t size = 8 * par->channels;
    int ret;

    if (avio_feof(s->pb) || redspark->samples_count == s->streams[0]->duration)
        return AVERROR_EOF;

    ret = av_get_packet(s->pb, pkt, size);
    if (ret != size) {
        av_packet_unref(pkt);
        return AVERROR(EIO);
    }

    pkt->duration = 14;
    redspark->samples_count += pkt->duration;
    pkt->stream_index = 0;

    return ret;
}