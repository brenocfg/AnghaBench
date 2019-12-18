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
struct TYPE_11__ {TYPE_2__** streams; } ;
struct TYPE_10__ {int size; int stream_index; int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; int /*<<< orphan*/  dts; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  time_base; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int* samples; int sample_size; int* samples_per_frame; int /*<<< orphan*/  dts; int /*<<< orphan*/  time_base; int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ AudioInterleaveContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int av_fifo_size (int /*<<< orphan*/ ) ; 
 int av_new_packet (TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_rescale_q (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int interleave_new_audio_packet(AVFormatContext *s, AVPacket *pkt,
                                       int stream_index, int flush)
{
    AVStream *st = s->streams[stream_index];
    AudioInterleaveContext *aic = st->priv_data;
    int ret;
    int frame_size = *aic->samples * aic->sample_size;
    int size = FFMIN(av_fifo_size(aic->fifo), frame_size);
    if (!size || (!flush && size == av_fifo_size(aic->fifo)))
        return 0;

    ret = av_new_packet(pkt, frame_size);
    if (ret < 0)
        return ret;
    av_fifo_generic_read(aic->fifo, pkt->data, size, NULL);

    if (size < pkt->size)
        memset(pkt->data + size, 0, pkt->size - size);

    pkt->dts = pkt->pts = aic->dts;
    pkt->duration = av_rescale_q(*aic->samples, st->time_base, aic->time_base);
    pkt->stream_index = stream_index;
    aic->dts += pkt->duration;

    aic->samples++;
    if (!*aic->samples)
        aic->samples = aic->samples_per_frame;

    return pkt->size;
}