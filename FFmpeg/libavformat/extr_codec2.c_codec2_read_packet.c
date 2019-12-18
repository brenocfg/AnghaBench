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
struct TYPE_13__ {int /*<<< orphan*/  pb; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_12__ {int duration; } ;
struct TYPE_11__ {TYPE_1__* codecpar; } ;
struct TYPE_10__ {int frames_per_packet; } ;
struct TYPE_9__ {int block_align; int frame_size; } ;
typedef  TYPE_2__ Codec2Context ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_4__*,int) ; 

__attribute__((used)) static int codec2_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    Codec2Context *c2 = s->priv_data;
    AVStream *st = s->streams[0];
    int ret, size, n, block_align, frame_size;

    block_align = st->codecpar->block_align;
    frame_size  = st->codecpar->frame_size;

    if (block_align <= 0 || frame_size <= 0 || c2->frames_per_packet <= 0) {
        return AVERROR(EINVAL);
    }

    //try to read desired number of frames, compute n from to actual number of bytes read
    size = c2->frames_per_packet * block_align;
    ret = av_get_packet(s->pb, pkt, size);
    if (ret < 0) {
        return ret;
    }

    //only set duration - compute_pkt_fields() and ff_pcm_read_seek() takes care of everything else
    //tested by spamming the seek functionality in ffplay
    n = ret / block_align;
    pkt->duration = n * frame_size;

    return ret;
}