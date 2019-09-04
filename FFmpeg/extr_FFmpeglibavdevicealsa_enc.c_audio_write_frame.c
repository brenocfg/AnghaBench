#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__** streams; TYPE_3__* priv_data; } ;
struct TYPE_15__ {int nb_samples; int /*<<< orphan*/  pkt_duration; int /*<<< orphan*/  pkt_dts; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/  duration; int /*<<< orphan*/  dts; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {int frame_size; } ;
struct TYPE_12__ {TYPE_1__* codecpar; } ;
struct TYPE_11__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_3__ AlsaData ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 unsigned int AV_WRITE_UNCODED_FRAME_QUERY ; 
 int /*<<< orphan*/  EINVAL ; 
 int audio_write_packet (TYPE_6__*,TYPE_4__*) ; 
 scalar_t__ av_sample_fmt_is_planar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audio_write_frame(AVFormatContext *s1, int stream_index,
                             AVFrame **frame, unsigned flags)
{
    AlsaData *s = s1->priv_data;
    AVPacket pkt;

    /* ff_alsa_open() should have accepted only supported formats */
    if ((flags & AV_WRITE_UNCODED_FRAME_QUERY))
        return av_sample_fmt_is_planar(s1->streams[stream_index]->codecpar->format) ?
               AVERROR(EINVAL) : 0;
    /* set only used fields */
    pkt.data     = (*frame)->data[0];
    pkt.size     = (*frame)->nb_samples * s->frame_size;
    pkt.dts      = (*frame)->pkt_dts;
    pkt.duration = (*frame)->pkt_duration;
    return audio_write_packet(s1, &pkt);
}