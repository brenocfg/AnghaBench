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
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/ * data; scalar_t__ stream_index; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAGAIN ; 
 char* av_err2str (int) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int avcodec_receive_packet (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int avcodec_send_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int fwrite (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int encode_write(AVCodecContext *avctx, AVFrame *frame, FILE *fout)
{
    int ret = 0;
    AVPacket enc_pkt;

    av_init_packet(&enc_pkt);
    enc_pkt.data = NULL;
    enc_pkt.size = 0;

    if ((ret = avcodec_send_frame(avctx, frame)) < 0) {
        fprintf(stderr, "Error code: %s\n", av_err2str(ret));
        goto end;
    }
    while (1) {
        ret = avcodec_receive_packet(avctx, &enc_pkt);
        if (ret)
            break;

        enc_pkt.stream_index = 0;
        ret = fwrite(enc_pkt.data, enc_pkt.size, 1, fout);
        av_packet_unref(&enc_pkt);
    }

end:
    ret = ((ret == AVERROR(EAGAIN)) ? 0 : -1);
    return ret;
}