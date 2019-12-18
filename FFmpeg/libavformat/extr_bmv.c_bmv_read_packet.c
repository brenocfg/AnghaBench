#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ eof_reached; } ;
struct TYPE_13__ {TYPE_6__* pb; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int size; int stream_index; int pts; int duration; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int get_next; int size; int* packet; int audio_pos; } ;
typedef  TYPE_1__ BMVContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int BMV_AUDIO ; 
 int BMV_END ; 
 int BMV_NOP ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ av_new_packet (TYPE_2__*,int) ; 
 int av_reallocp (int**,int) ; 
 int avio_r8 (TYPE_6__*) ; 
 int avio_read (TYPE_6__*,int*,int) ; 
 int avio_rl24 (TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int bmv_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    BMVContext *c = s->priv_data;
    int type, err;

    while (c->get_next) {
        if (s->pb->eof_reached)
            return AVERROR_EOF;
        type = avio_r8(s->pb);
        if (type == BMV_NOP)
            continue;
        if (type == BMV_END)
            return AVERROR_EOF;
        c->size = avio_rl24(s->pb);
        if (!c->size)
            return AVERROR_INVALIDDATA;
        if ((err = av_reallocp(&c->packet, c->size + 1)) < 0)
            return err;
        c->packet[0] = type;
        if (avio_read(s->pb, c->packet + 1, c->size) != c->size)
            return AVERROR(EIO);
        if (type & BMV_AUDIO) {
            int audio_size = c->packet[1] * 65 + 1;
            if (audio_size >= c->size) {
                av_log(s, AV_LOG_ERROR, "Reported audio size %d is bigger than packet size (%d)\n",
                       audio_size, c->size);
                return AVERROR_INVALIDDATA;
            }
            if (av_new_packet(pkt, audio_size) < 0)
                return AVERROR(ENOMEM);
            memcpy(pkt->data, c->packet + 1, pkt->size);
            pkt->stream_index = 1;
            pkt->pts          = c->audio_pos;
            pkt->duration     = c->packet[1] * 32;
            c->audio_pos += pkt->duration;
            c->get_next   = 0;
            return pkt->size;
        } else
            break;
    }
    if (av_new_packet(pkt, c->size + 1) < 0)
        return AVERROR(ENOMEM);
    pkt->stream_index = 0;
    c->get_next = 1;
    memcpy(pkt->data, c->packet, pkt->size);
    return pkt->size;
}