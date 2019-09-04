#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ audio_stream_idx; TYPE_3__* pict_list; } ;
struct TYPE_17__ {TYPE_2__** streams; int /*<<< orphan*/ * pb; TYPE_6__* priv_data; } ;
struct TYPE_16__ {scalar_t__ stream_index; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {struct TYPE_15__* next; int /*<<< orphan*/  pkt; } ;
struct TYPE_14__ {int nb_frames; TYPE_1__* codecpar; } ;
struct TYPE_13__ {scalar_t__ codec_type; } ;
typedef  TYPE_3__ AVPacketList ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ AIFFOutputContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,size_t) ; 
 TYPE_3__* av_mallocz (int) ; 
 int av_packet_ref (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aiff_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    AIFFOutputContext *aiff = s->priv_data;
    AVIOContext *pb = s->pb;
    if (pkt->stream_index == aiff->audio_stream_idx)
        avio_write(pb, pkt->data, pkt->size);
    else {
        int ret;
        AVPacketList *pict_list, *last;

        if (s->streams[pkt->stream_index]->codecpar->codec_type != AVMEDIA_TYPE_VIDEO)
            return 0;

        /* warn only once for each stream */
        if (s->streams[pkt->stream_index]->nb_frames == 1) {
            av_log(s, AV_LOG_WARNING, "Got more than one picture in stream %d,"
                   " ignoring.\n", pkt->stream_index);
        }
        if (s->streams[pkt->stream_index]->nb_frames >= 1)
            return 0;

        pict_list = av_mallocz(sizeof(AVPacketList));
        if (!pict_list)
            return AVERROR(ENOMEM);

        ret = av_packet_ref(&pict_list->pkt, pkt);
        if (ret < 0) {
            av_freep(&pict_list);
            return ret;
        }

        if (!aiff->pict_list)
            aiff->pict_list = pict_list;
        else {
            last = aiff->pict_list;
            while (last->next)
                last = last->next;
            last->next = pict_list;
        }
    }

    return 0;
}