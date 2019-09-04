#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__** streams; } ;
struct TYPE_14__ {TYPE_2__** streams; } ;
struct TYPE_13__ {scalar_t__ stream_index; scalar_t__ size; int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_11__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EAGAIN ; 
 char* av_err2str (int) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_3__*) ; 
 int av_interleaved_write_frame (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_rescale_ts (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avcodec_receive_packet (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int avcodec_send_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encoder_ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_5__* ifmt_ctx ; 
 TYPE_4__* ofmt_ctx ; 
 int /*<<< orphan*/  stderr ; 
 size_t video_stream ; 

__attribute__((used)) static int encode_write(AVFrame *frame)
{
    int ret = 0;
    AVPacket enc_pkt;

    av_init_packet(&enc_pkt);
    enc_pkt.data = NULL;
    enc_pkt.size = 0;

    if ((ret = avcodec_send_frame(encoder_ctx, frame)) < 0) {
        fprintf(stderr, "Error during encoding. Error code: %s\n", av_err2str(ret));
        goto end;
    }
    while (1) {
        ret = avcodec_receive_packet(encoder_ctx, &enc_pkt);
        if (ret)
            break;

        enc_pkt.stream_index = 0;
        av_packet_rescale_ts(&enc_pkt, ifmt_ctx->streams[video_stream]->time_base,
                             ofmt_ctx->streams[0]->time_base);
        ret = av_interleaved_write_frame(ofmt_ctx, &enc_pkt);
        if (ret < 0) {
            fprintf(stderr, "Error during writing data to output file. "
                    "Error code: %s\n", av_err2str(ret));
            return -1;
        }
    }

end:
    if (ret == AVERROR_EOF)
        return 0;
    ret = ((ret == AVERROR(EAGAIN)) ? 0:-1);
    return ret;
}