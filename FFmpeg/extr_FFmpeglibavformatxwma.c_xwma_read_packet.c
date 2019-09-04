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
typedef  scalar_t__ int64_t ;
struct TYPE_10__ {scalar_t__ data_end; } ;
typedef  TYPE_2__ XWMAContext ;
struct TYPE_13__ {int /*<<< orphan*/  pb; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_12__ {scalar_t__ stream_index; } ;
struct TYPE_11__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {int block_align; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int FFMIN (int,scalar_t__) ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xwma_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int ret, size;
    int64_t left;
    AVStream *st;
    XWMAContext *xwma = s->priv_data;

    st = s->streams[0];

    left = xwma->data_end - avio_tell(s->pb);
    if (left <= 0) {
        return AVERROR_EOF;
    }

    /* read a single block; the default block size is 2230. */
    size = (st->codecpar->block_align > 1) ? st->codecpar->block_align : 2230;
    size = FFMIN(size, left);

    ret  = av_get_packet(s->pb, pkt, size);
    if (ret < 0)
        return ret;

    pkt->stream_index = 0;
    return ret;
}