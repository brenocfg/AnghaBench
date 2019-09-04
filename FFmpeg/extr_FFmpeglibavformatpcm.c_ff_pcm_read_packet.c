#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int block_align; int sample_rate; } ;
struct TYPE_10__ {int /*<<< orphan*/  pb; TYPE_1__** streams; } ;
struct TYPE_9__ {scalar_t__ stream_index; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_4__* codecpar; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_FLAG_CORRUPT ; 
 int /*<<< orphan*/  EINVAL ; 
 int FFMAX (int,int) ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAW_SAMPLES ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_2__*,int) ; 

int ff_pcm_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVCodecParameters *par = s->streams[0]->codecpar;
    int ret, size;

    if (par->block_align <= 0)
        return AVERROR(EINVAL);

    /*
     * Compute read size to complete a read every 62ms.
     * Clamp to RAW_SAMPLES if larger.
     */
    size = FFMAX(par->sample_rate/25, 1);
    size = FFMIN(size, RAW_SAMPLES) * par->block_align;

    ret = av_get_packet(s->pb, pkt, size);

    pkt->flags &= ~AV_PKT_FLAG_CORRUPT;
    pkt->stream_index = 0;

    return ret;
}