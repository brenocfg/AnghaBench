#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int stream_index; int* data; int size; int /*<<< orphan*/  pos; int /*<<< orphan*/  flags; int /*<<< orphan*/ * buf; } ;
struct TYPE_10__ {int frame_size; int audio_block_length; int palette_size; int odd_frame; TYPE_2__ video_packet; } ;
typedef  TYPE_1__ YopDecContext ;
struct TYPE_12__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int av_new_packet (TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  av_shrink_packet (TYPE_2__*,int) ; 
 int avio_read (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int yop_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    YopDecContext *yop = s->priv_data;
    AVIOContext *pb  = s->pb;

    int ret;
    int actual_video_data_size = yop->frame_size -
                                 yop->audio_block_length - yop->palette_size;

    yop->video_packet.stream_index = 1;

    if (yop->video_packet.data) {
        *pkt                   =  yop->video_packet;
        yop->video_packet.data =  NULL;
        yop->video_packet.buf  =  NULL;
        yop->video_packet.size =  0;
        pkt->data[0]           =  yop->odd_frame;
        pkt->flags             |= AV_PKT_FLAG_KEY;
        yop->odd_frame         ^= 1;
        return pkt->size;
    }
    ret = av_new_packet(&yop->video_packet,
                        yop->frame_size - yop->audio_block_length);
    if (ret < 0)
        return ret;

    yop->video_packet.pos = avio_tell(pb);

    ret = avio_read(pb, yop->video_packet.data, yop->palette_size);
    if (ret < 0) {
        goto err_out;
    }else if (ret < yop->palette_size) {
        ret = AVERROR_EOF;
        goto err_out;
    }

    ret = av_get_packet(pb, pkt, 920);
    if (ret < 0)
        goto err_out;

    // Set position to the start of the frame
    pkt->pos = yop->video_packet.pos;

    avio_skip(pb, yop->audio_block_length - ret);

    ret = avio_read(pb, yop->video_packet.data + yop->palette_size,
                     actual_video_data_size);
    if (ret < 0)
        goto err_out;
    else if (ret < actual_video_data_size)
        av_shrink_packet(&yop->video_packet, yop->palette_size + ret);

    // Arbitrarily return the audio data first
    return yop->audio_block_length;

err_out:
    av_packet_unref(&yop->video_packet);
    return ret;
}