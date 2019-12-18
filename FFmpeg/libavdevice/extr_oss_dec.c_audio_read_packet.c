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
struct audio_buf_info {scalar_t__ bytes; } ;
typedef  int int64_t ;
struct TYPE_10__ {TYPE_1__* priv_data; } ;
struct TYPE_9__ {int size; int pts; scalar_t__ data; } ;
struct TYPE_8__ {int sample_rate; int channels; scalar_t__ flip_left; int /*<<< orphan*/  fd; int /*<<< orphan*/  frame_size; } ;
typedef  TYPE_1__ OSSAudioData ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  SNDCTL_DSP_GETISPACE ; 
 int av_gettime () ; 
 int av_new_packet (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct audio_buf_info*) ; 
 int read (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int audio_read_packet(AVFormatContext *s1, AVPacket *pkt)
{
    OSSAudioData *s = s1->priv_data;
    int ret, bdelay;
    int64_t cur_time;
    struct audio_buf_info abufi;

    if ((ret=av_new_packet(pkt, s->frame_size)) < 0)
        return ret;

    ret = read(s->fd, pkt->data, pkt->size);
    if (ret <= 0){
        av_packet_unref(pkt);
        pkt->size = 0;
        if (ret<0)  return AVERROR(errno);
        else        return AVERROR_EOF;
    }
    pkt->size = ret;

    /* compute pts of the start of the packet */
    cur_time = av_gettime();
    bdelay = ret;
    if (ioctl(s->fd, SNDCTL_DSP_GETISPACE, &abufi) == 0) {
        bdelay += abufi.bytes;
    }
    /* subtract time represented by the number of bytes in the audio fifo */
    cur_time -= (bdelay * 1000000LL) / (s->sample_rate * s->channels);

    /* convert to wanted units */
    pkt->pts = cur_time;

    if (s->flip_left && s->channels == 2) {
        int i;
        short *p = (short *) pkt->data;

        for (i = 0; i < ret; i += 4) {
            *p = ~*p;
            p += 2;
        }
    }
    return 0;
}