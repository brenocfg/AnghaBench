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
struct TYPE_10__ {int* data; int /*<<< orphan*/  stream_index; int /*<<< orphan*/  pts; } ;
struct TYPE_9__ {int audio_buffer_full; int current_pal_data_size; scalar_t__ current_video_data_size; scalar_t__ current_frame_offs; scalar_t__ current_pal_data_offs; scalar_t__ current_audio_data_offs; int /*<<< orphan*/  current_frame_pts; int /*<<< orphan*/  audio_stream_index; int /*<<< orphan*/  current_audio_data_size; int /*<<< orphan*/  video_stream_index; int /*<<< orphan*/  current_video_data_ptr; } ;
typedef  TYPE_1__ SeqDemuxContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ av_new_packet (TYPE_2__*,scalar_t__) ; 
 int avio_read (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int seq_parse_frame_data (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int seq_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int rc;
    SeqDemuxContext *seq = s->priv_data;
    AVIOContext *pb = s->pb;

    if (!seq->audio_buffer_full) {
        rc = seq_parse_frame_data(seq, pb);
        if (rc)
            return rc;

        /* video packet */
        if (seq->current_pal_data_size + seq->current_video_data_size != 0) {
            if (av_new_packet(pkt, 1 + seq->current_pal_data_size + seq->current_video_data_size))
                return AVERROR(ENOMEM);

            pkt->data[0] = 0;
            if (seq->current_pal_data_size) {
                pkt->data[0] |= 1;
                avio_seek(pb, seq->current_frame_offs + seq->current_pal_data_offs, SEEK_SET);
                if (avio_read(pb, &pkt->data[1], seq->current_pal_data_size) != seq->current_pal_data_size)
                    return AVERROR(EIO);
            }
            if (seq->current_video_data_size) {
                pkt->data[0] |= 2;
                memcpy(&pkt->data[1 + seq->current_pal_data_size],
                  seq->current_video_data_ptr,
                  seq->current_video_data_size);
            }
            pkt->stream_index = seq->video_stream_index;
            pkt->pts = seq->current_frame_pts;

            /* sound buffer will be processed on next read_packet() call */
            seq->audio_buffer_full = 1;
            return 0;
       }
    }

    /* audio packet */
    if (seq->current_audio_data_offs == 0) /* end of data reached */
        return AVERROR(EIO);

    avio_seek(pb, seq->current_frame_offs + seq->current_audio_data_offs, SEEK_SET);
    rc = av_get_packet(pb, pkt, seq->current_audio_data_size);
    if (rc < 0)
        return rc;

    pkt->stream_index = seq->audio_stream_index;
    seq->current_frame_pts++;

    seq->audio_buffer_full = 0;
    return 0;
}