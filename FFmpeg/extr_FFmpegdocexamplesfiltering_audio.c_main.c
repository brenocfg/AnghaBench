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
struct TYPE_5__ {scalar_t__ stream_index; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_BUFFERSRC_FLAG_KEEP_REF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ audio_stream_index ; 
 int av_buffersink_get_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ av_buffersrc_add_frame_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* av_err2str (int) ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int av_read_frame (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ *) ; 
 int avcodec_receive_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int avcodec_send_packet (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  avfilter_graph_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_close_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffersink_ctx ; 
 int /*<<< orphan*/  buffersrc_ctx ; 
 int /*<<< orphan*/  dec_ctx ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  filter_descr ; 
 int /*<<< orphan*/  filter_graph ; 
 int /*<<< orphan*/  fmt_ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int init_filters (int /*<<< orphan*/ ) ; 
 int open_input_file (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* player ; 
 int /*<<< orphan*/  print_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
    int ret;
    AVPacket packet;
    AVFrame *frame = av_frame_alloc();
    AVFrame *filt_frame = av_frame_alloc();

    if (!frame || !filt_frame) {
        perror("Could not allocate frame");
        exit(1);
    }
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file | %s\n", argv[0], player);
        exit(1);
    }

    if ((ret = open_input_file(argv[1])) < 0)
        goto end;
    if ((ret = init_filters(filter_descr)) < 0)
        goto end;

    /* read all packets */
    while (1) {
        if ((ret = av_read_frame(fmt_ctx, &packet)) < 0)
            break;

        if (packet.stream_index == audio_stream_index) {
            ret = avcodec_send_packet(dec_ctx, &packet);
            if (ret < 0) {
                av_log(NULL, AV_LOG_ERROR, "Error while sending a packet to the decoder\n");
                break;
            }

            while (ret >= 0) {
                ret = avcodec_receive_frame(dec_ctx, frame);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                    break;
                } else if (ret < 0) {
                    av_log(NULL, AV_LOG_ERROR, "Error while receiving a frame from the decoder\n");
                    goto end;
                }

                if (ret >= 0) {
                    /* push the audio data from decoded frame into the filtergraph */
                    if (av_buffersrc_add_frame_flags(buffersrc_ctx, frame, AV_BUFFERSRC_FLAG_KEEP_REF) < 0) {
                        av_log(NULL, AV_LOG_ERROR, "Error while feeding the audio filtergraph\n");
                        break;
                    }

                    /* pull filtered audio from the filtergraph */
                    while (1) {
                        ret = av_buffersink_get_frame(buffersink_ctx, filt_frame);
                        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                            break;
                        if (ret < 0)
                            goto end;
                        print_frame(filt_frame);
                        av_frame_unref(filt_frame);
                    }
                    av_frame_unref(frame);
                }
            }
        }
        av_packet_unref(&packet);
    }
end:
    avfilter_graph_free(&filter_graph);
    avcodec_free_context(&dec_ctx);
    avformat_close_input(&fmt_ctx);
    av_frame_free(&frame);
    av_frame_free(&filt_frame);

    if (ret < 0 && ret != AVERROR_EOF) {
        fprintf(stderr, "Error occurred: %s\n", av_err2str(ret));
        exit(1);
    }

    exit(0);
}