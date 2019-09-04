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
struct TYPE_8__ {scalar_t__ stream; int sample_size; scalar_t__ pts; scalar_t__ keyframe; int /*<<< orphan*/  sample_offset; } ;
typedef  TYPE_1__ film_sample ;
struct TYPE_11__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_10__ {scalar_t__ stream_index; scalar_t__ duration; int /*<<< orphan*/  flags; scalar_t__ pts; scalar_t__ dts; } ;
struct TYPE_9__ {size_t current_sample; size_t sample_count; TYPE_1__* sample_table; } ;
typedef  TYPE_2__ FilmDemuxContext ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int film_read_packet(AVFormatContext *s,
                            AVPacket *pkt)
{
    FilmDemuxContext *film = s->priv_data;
    AVIOContext *pb = s->pb;
    film_sample *sample;
    film_sample *next_sample = NULL;
    int next_sample_id;
    int ret = 0;

    if (film->current_sample >= film->sample_count)
        return AVERROR_EOF;

    sample = &film->sample_table[film->current_sample];

    /* Find the next sample from the same stream, assuming there is one;
     * this is used to calculate the duration below */
    next_sample_id = film->current_sample + 1;
    while (next_sample == NULL) {
        if (next_sample_id >= film->sample_count)
            break;

        next_sample = &film->sample_table[next_sample_id];
        if (next_sample->stream != sample->stream) {
            next_sample = NULL;
            next_sample_id++;
        }
    }

    /* position the stream (will probably be there anyway) */
    avio_seek(pb, sample->sample_offset, SEEK_SET);

    ret = av_get_packet(pb, pkt, sample->sample_size);
    if (ret != sample->sample_size)
        ret = AVERROR(EIO);

    pkt->stream_index = sample->stream;
    pkt->dts = sample->pts;
    pkt->pts = sample->pts;
    pkt->flags |= sample->keyframe ? AV_PKT_FLAG_KEY : 0;
    if (next_sample != NULL)
        pkt->duration = next_sample->pts - sample->pts;

    film->current_sample++;

    return ret;
}