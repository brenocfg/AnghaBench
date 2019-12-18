#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_10__ {int data; int size; int stream_index; int /*<<< orphan*/  pts; } ;
struct TYPE_9__ {int /*<<< orphan*/  audio_pts; int /*<<< orphan*/  video_pts; } ;
typedef  TYPE_1__ MmDemuxContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 unsigned int AV_RL16 (unsigned char*) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MM_PREAMBLE_SIZE ; 
#define  MM_TYPE_AUDIO 135 
#define  MM_TYPE_INTER 134 
#define  MM_TYPE_INTER_HH 133 
#define  MM_TYPE_INTER_HHV 132 
#define  MM_TYPE_INTRA 131 
#define  MM_TYPE_INTRA_HH 130 
#define  MM_TYPE_INTRA_HHV 129 
#define  MM_TYPE_PALETTE 128 
 int /*<<< orphan*/  av_get_packet (int /*<<< orphan*/ *,TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  av_new_packet (TYPE_2__*,int) ; 
 unsigned int avio_read (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int,unsigned char*,int) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s,
                           AVPacket *pkt)
{
    MmDemuxContext *mm = s->priv_data;
    AVIOContext *pb = s->pb;
    unsigned char preamble[MM_PREAMBLE_SIZE];
    unsigned int type, length;

    while(1) {

        if (avio_read(pb, preamble, MM_PREAMBLE_SIZE) != MM_PREAMBLE_SIZE) {
            return AVERROR(EIO);
        }

        type = AV_RL16(&preamble[0]);
        length = AV_RL16(&preamble[2]);

        switch(type) {
        case MM_TYPE_PALETTE :
        case MM_TYPE_INTER :
        case MM_TYPE_INTRA :
        case MM_TYPE_INTRA_HH :
        case MM_TYPE_INTER_HH :
        case MM_TYPE_INTRA_HHV :
        case MM_TYPE_INTER_HHV :
            /* output preamble + data */
            if (av_new_packet(pkt, length + MM_PREAMBLE_SIZE))
                return AVERROR(ENOMEM);
            memcpy(pkt->data, preamble, MM_PREAMBLE_SIZE);
            if (avio_read(pb, pkt->data + MM_PREAMBLE_SIZE, length) != length)
                return AVERROR(EIO);
            pkt->size = length + MM_PREAMBLE_SIZE;
            pkt->stream_index = 0;
            pkt->pts = mm->video_pts;
            if (type!=MM_TYPE_PALETTE)
                mm->video_pts++;
            return 0;

        case MM_TYPE_AUDIO :
            if (av_get_packet(s->pb, pkt, length)<0)
                return AVERROR(ENOMEM);
            pkt->stream_index = 1;
            pkt->pts = mm->audio_pts++;
            return 0;

        default :
            av_log(s, AV_LOG_INFO, "unknown chunk type 0x%x\n", type);
            avio_skip(pb, length);
        }
    }
}