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
struct TYPE_8__ {unsigned int audiosize; scalar_t__ frame; scalar_t__ framecnt; int /*<<< orphan*/  audio_stream_index; int /*<<< orphan*/  video_stream_index; scalar_t__ has_audio; void* next_framesz; int /*<<< orphan*/  next_frame; } ;
typedef  TYPE_1__ ThpDemuxContext ;
struct TYPE_10__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_9__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  duration; int /*<<< orphan*/  stream_index; } ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_RB32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ FFMAX (void*,int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 void* avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int thp_read_packet(AVFormatContext *s,
                            AVPacket *pkt)
{
    ThpDemuxContext *thp = s->priv_data;
    AVIOContext *pb = s->pb;
    unsigned int size;
    int ret;

    if (thp->audiosize == 0) {
        /* Terminate when last frame is reached.  */
        if (thp->frame >= thp->framecnt)
            return AVERROR_EOF;

        avio_seek(pb, thp->next_frame, SEEK_SET);

        /* Locate the next frame and read out its size.  */
        thp->next_frame += FFMAX(thp->next_framesz, 1);
        thp->next_framesz = avio_rb32(pb);

                        avio_rb32(pb); /* Previous total size.  */
        size          = avio_rb32(pb); /* Total size of this frame.  */

        /* Store the audiosize so the next time this function is called,
           the audio can be read.  */
        if (thp->has_audio)
            thp->audiosize = avio_rb32(pb); /* Audio size.  */
        else
            thp->frame++;

        ret = av_get_packet(pb, pkt, size);
        if (ret < 0)
            return ret;
        if (ret != size) {
            av_packet_unref(pkt);
            return AVERROR(EIO);
        }

        pkt->stream_index = thp->video_stream_index;
    } else {
        ret = av_get_packet(pb, pkt, thp->audiosize);
        if (ret < 0)
            return ret;
        if (ret != thp->audiosize) {
            av_packet_unref(pkt);
            return AVERROR(EIO);
        }

        pkt->stream_index = thp->audio_stream_index;
        if (thp->audiosize >= 8)
            pkt->duration = AV_RB32(&pkt->data[4]);

        thp->audiosize = 0;
        thp->frame++;
    }

    return 0;
}