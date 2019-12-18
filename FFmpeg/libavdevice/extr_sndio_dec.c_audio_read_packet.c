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
typedef  int int64_t ;
struct TYPE_10__ {TYPE_1__* priv_data; } ;
struct TYPE_9__ {int size; int pts; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int softpos; int hwpos; int bps; int channels; int sample_rate; int /*<<< orphan*/  hdl; int /*<<< orphan*/  buffer_size; } ;
typedef  TYPE_1__ SndioData ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int av_gettime () ; 
 int av_new_packet (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 scalar_t__ sio_eof (int /*<<< orphan*/ ) ; 
 int sio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int audio_read_packet(AVFormatContext *s1, AVPacket *pkt)
{
    SndioData *s = s1->priv_data;
    int64_t bdelay, cur_time;
    int ret;

    if ((ret = av_new_packet(pkt, s->buffer_size)) < 0)
        return ret;

    ret = sio_read(s->hdl, pkt->data, pkt->size);
    if (ret == 0 || sio_eof(s->hdl)) {
        av_packet_unref(pkt);
        return AVERROR_EOF;
    }

    pkt->size   = ret;
    s->softpos += ret;

    /* compute pts of the start of the packet */
    cur_time = av_gettime();

    bdelay = ret + s->hwpos - s->softpos;

    /* convert to pts */
    pkt->pts = cur_time - ((bdelay * 1000000) /
        (s->bps * s->channels * s->sample_rate));

    return 0;
}