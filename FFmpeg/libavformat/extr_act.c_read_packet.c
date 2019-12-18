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
struct TYPE_13__ {int second_packet; int bytes_left_in_chunk; int /*<<< orphan*/ * audio_buffer; } ;
struct TYPE_12__ {TYPE_2__** streams; int /*<<< orphan*/ * pb; TYPE_5__* priv_data; } ;
struct TYPE_11__ {int duration; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {int sample_rate; } ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ ACTContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int CHUNK_SIZE ; 
 int /*<<< orphan*/  EIO ; 
 int av_new_packet (TYPE_3__*,int) ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s,
                          AVPacket *pkt)
{
    ACTContext *ctx = s->priv_data;
    AVIOContext *pb = s->pb;
    int ret;
    int frame_size=s->streams[0]->codecpar->sample_rate==8000?10:22;


    if(s->streams[0]->codecpar->sample_rate==8000)
        ret=av_new_packet(pkt, 10);
    else
        ret=av_new_packet(pkt, 11);

    if(ret)
        return ret;

    if(s->streams[0]->codecpar->sample_rate==4400 && !ctx->second_packet)
    {
        ret = avio_read(pb, ctx->audio_buffer, frame_size);

        if(ret<0)
            return ret;
        if(ret!=frame_size)
            return AVERROR(EIO);

        pkt->data[0]=ctx->audio_buffer[11];
        pkt->data[1]=ctx->audio_buffer[0];
        pkt->data[2]=ctx->audio_buffer[12];
        pkt->data[3]=ctx->audio_buffer[1];
        pkt->data[4]=ctx->audio_buffer[13];
        pkt->data[5]=ctx->audio_buffer[2];
        pkt->data[6]=ctx->audio_buffer[14];
        pkt->data[7]=ctx->audio_buffer[3];
        pkt->data[8]=ctx->audio_buffer[15];
        pkt->data[9]=ctx->audio_buffer[4];
        pkt->data[10]=ctx->audio_buffer[16];

        ctx->second_packet=1;
    }
    else if(s->streams[0]->codecpar->sample_rate==4400 && ctx->second_packet)
    {
        pkt->data[0]=ctx->audio_buffer[5];
        pkt->data[1]=ctx->audio_buffer[17];
        pkt->data[2]=ctx->audio_buffer[6];
        pkt->data[3]=ctx->audio_buffer[18];
        pkt->data[4]=ctx->audio_buffer[7];
        pkt->data[5]=ctx->audio_buffer[19];
        pkt->data[6]=ctx->audio_buffer[8];
        pkt->data[7]=ctx->audio_buffer[20];
        pkt->data[8]=ctx->audio_buffer[9];
        pkt->data[9]=ctx->audio_buffer[21];
        pkt->data[10]=ctx->audio_buffer[10];

        ctx->second_packet=0;
    }
    else // 8000 Hz
    {
        ret = avio_read(pb, ctx->audio_buffer, frame_size);

        if(ret<0)
            return ret;
        if(ret!=frame_size)
            return AVERROR(EIO);

        pkt->data[0]=ctx->audio_buffer[5];
        pkt->data[1]=ctx->audio_buffer[0];
        pkt->data[2]=ctx->audio_buffer[6];
        pkt->data[3]=ctx->audio_buffer[1];
        pkt->data[4]=ctx->audio_buffer[7];
        pkt->data[5]=ctx->audio_buffer[2];
        pkt->data[6]=ctx->audio_buffer[8];
        pkt->data[7]=ctx->audio_buffer[3];
        pkt->data[8]=ctx->audio_buffer[9];
        pkt->data[9]=ctx->audio_buffer[4];
    }

    ctx->bytes_left_in_chunk -= frame_size;

    if(ctx->bytes_left_in_chunk < frame_size)
    {
        avio_skip(pb, ctx->bytes_left_in_chunk);
        ctx->bytes_left_in_chunk=CHUNK_SIZE;
    }

    pkt->duration=1;

    return ret;
}