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
struct TYPE_5__ {scalar_t__ stream_index; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dump_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 scalar_t__ av_read_frame (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_close_input (int /*<<< orphan*/ *) ; 
 scalar_t__ avformat_find_stream_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ avformat_open_input (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fmt_ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  frame ; 
 int /*<<< orphan*/  open_codec_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* src_filename ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  video_dec_ctx ; 
 int /*<<< orphan*/  video_stream ; 
 scalar_t__ video_stream_idx ; 

int main(int argc, char **argv)
{
    int ret = 0;
    AVPacket pkt = { 0 };

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <video>\n", argv[0]);
        exit(1);
    }
    src_filename = argv[1];

    if (avformat_open_input(&fmt_ctx, src_filename, NULL, NULL) < 0) {
        fprintf(stderr, "Could not open source file %s\n", src_filename);
        exit(1);
    }

    if (avformat_find_stream_info(fmt_ctx, NULL) < 0) {
        fprintf(stderr, "Could not find stream information\n");
        exit(1);
    }

    open_codec_context(fmt_ctx, AVMEDIA_TYPE_VIDEO);

    av_dump_format(fmt_ctx, 0, src_filename, 0);

    if (!video_stream) {
        fprintf(stderr, "Could not find video stream in the input, aborting\n");
        ret = 1;
        goto end;
    }

    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate frame\n");
        ret = AVERROR(ENOMEM);
        goto end;
    }

    printf("framenum,source,blockw,blockh,srcx,srcy,dstx,dsty,flags\n");

    /* read frames from the file */
    while (av_read_frame(fmt_ctx, &pkt) >= 0) {
        if (pkt.stream_index == video_stream_idx)
            ret = decode_packet(&pkt);
        av_packet_unref(&pkt);
        if (ret < 0)
            break;
    }

    /* flush cached frames */
    decode_packet(NULL);

end:
    avcodec_free_context(&video_dec_ctx);
    avformat_close_input(&fmt_ctx);
    av_frame_free(&frame);
    return ret < 0;
}