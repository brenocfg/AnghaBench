#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  av_init_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int avcodec_receive_packet (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int avcodec_send_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int encode_frame(AVCodecContext *c, AVFrame *frame)
{
    AVPacket pkt = { 0 };
    int ret;
    int size = 0;

    av_init_packet(&pkt);

    ret = avcodec_send_frame(c, frame);
    if (ret < 0)
        return ret;

    do {
        ret = avcodec_receive_packet(c, &pkt);
        if (ret >= 0) {
            size += pkt.size;
            av_packet_unref(&pkt);
        } else if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
            return ret;
    } while (ret >= 0);

    return size;
}