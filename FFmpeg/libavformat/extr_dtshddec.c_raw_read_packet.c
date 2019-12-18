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
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_8__ {scalar_t__ stream_index; } ;
struct TYPE_7__ {scalar_t__ data_end; } ;
typedef  TYPE_1__ DTSHDDemuxContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 scalar_t__ FFMIN (scalar_t__,int) ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raw_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    DTSHDDemuxContext *dtshd = s->priv_data;
    int64_t size, left;
    int ret;

    left = dtshd->data_end - avio_tell(s->pb);
    size = FFMIN(left, 1024);
    if (size <= 0)
        return AVERROR_EOF;

    ret = av_get_packet(s->pb, pkt, size);
    if (ret < 0)
        return ret;

    pkt->stream_index = 0;

    return ret;
}