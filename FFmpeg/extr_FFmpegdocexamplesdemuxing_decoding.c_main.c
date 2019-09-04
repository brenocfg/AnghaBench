#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_19__ {scalar_t__* streams; } ;
struct TYPE_18__ {int width; int height; int sample_fmt; int channels; int sample_rate; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_17__ {scalar_t__ size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* audio_dec_ctx ; 
 scalar_t__ audio_dst_file ; 
 char* audio_dst_filename ; 
 scalar_t__ audio_stream ; 
 size_t audio_stream_idx ; 
 int /*<<< orphan*/  av_dump_format (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 
 int av_get_packed_sample_fmt (int) ; 
 char* av_get_pix_fmt_name (int /*<<< orphan*/ ) ; 
 char* av_get_sample_fmt_name (int) ; 
 int av_image_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 scalar_t__ av_read_frame (TYPE_5__*,TYPE_1__*) ; 
 scalar_t__ av_sample_fmt_is_planar (int) ; 
 int /*<<< orphan*/  avcodec_free_context (TYPE_2__**) ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_5__**) ; 
 scalar_t__ avformat_find_stream_info (TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avformat_open_input (TYPE_5__**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_packet (int*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 TYPE_5__* fmt_ctx ; 
 scalar_t__ fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  frame ; 
 int get_format_from_sample_fmt (char const**,int) ; 
 int height ; 
 scalar_t__ open_codec_context (size_t*,TYPE_2__**,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pix_fmt ; 
 TYPE_1__ pkt ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int refcount ; 
 char* src_filename ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 TYPE_2__* video_dec_ctx ; 
 int video_dst_bufsize ; 
 int /*<<< orphan*/ * video_dst_data ; 
 scalar_t__ video_dst_file ; 
 char* video_dst_filename ; 
 int /*<<< orphan*/  video_dst_linesize ; 
 scalar_t__ video_stream ; 
 size_t video_stream_idx ; 
 int width ; 

int main (int argc, char **argv)
{
    int ret = 0, got_frame;

    if (argc != 4 && argc != 5) {
        fprintf(stderr, "usage: %s [-refcount] input_file video_output_file audio_output_file\n"
                "API example program to show how to read frames from an input file.\n"
                "This program reads frames from a file, decodes them, and writes decoded\n"
                "video frames to a rawvideo file named video_output_file, and decoded\n"
                "audio frames to a rawaudio file named audio_output_file.\n\n"
                "If the -refcount option is specified, the program use the\n"
                "reference counting frame system which allows keeping a copy of\n"
                "the data for longer than one decode call.\n"
                "\n", argv[0]);
        exit(1);
    }
    if (argc == 5 && !strcmp(argv[1], "-refcount")) {
        refcount = 1;
        argv++;
    }
    src_filename = argv[1];
    video_dst_filename = argv[2];
    audio_dst_filename = argv[3];

    /* open input file, and allocate format context */
    if (avformat_open_input(&fmt_ctx, src_filename, NULL, NULL) < 0) {
        fprintf(stderr, "Could not open source file %s\n", src_filename);
        exit(1);
    }

    /* retrieve stream information */
    if (avformat_find_stream_info(fmt_ctx, NULL) < 0) {
        fprintf(stderr, "Could not find stream information\n");
        exit(1);
    }

    if (open_codec_context(&video_stream_idx, &video_dec_ctx, fmt_ctx, AVMEDIA_TYPE_VIDEO) >= 0) {
        video_stream = fmt_ctx->streams[video_stream_idx];

        video_dst_file = fopen(video_dst_filename, "wb");
        if (!video_dst_file) {
            fprintf(stderr, "Could not open destination file %s\n", video_dst_filename);
            ret = 1;
            goto end;
        }

        /* allocate image where the decoded image will be put */
        width = video_dec_ctx->width;
        height = video_dec_ctx->height;
        pix_fmt = video_dec_ctx->pix_fmt;
        ret = av_image_alloc(video_dst_data, video_dst_linesize,
                             width, height, pix_fmt, 1);
        if (ret < 0) {
            fprintf(stderr, "Could not allocate raw video buffer\n");
            goto end;
        }
        video_dst_bufsize = ret;
    }

    if (open_codec_context(&audio_stream_idx, &audio_dec_ctx, fmt_ctx, AVMEDIA_TYPE_AUDIO) >= 0) {
        audio_stream = fmt_ctx->streams[audio_stream_idx];
        audio_dst_file = fopen(audio_dst_filename, "wb");
        if (!audio_dst_file) {
            fprintf(stderr, "Could not open destination file %s\n", audio_dst_filename);
            ret = 1;
            goto end;
        }
    }

    /* dump input information to stderr */
    av_dump_format(fmt_ctx, 0, src_filename, 0);

    if (!audio_stream && !video_stream) {
        fprintf(stderr, "Could not find audio or video stream in the input, aborting\n");
        ret = 1;
        goto end;
    }

    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate frame\n");
        ret = AVERROR(ENOMEM);
        goto end;
    }

    /* initialize packet, set data to NULL, let the demuxer fill it */
    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;

    if (video_stream)
        printf("Demuxing video from file '%s' into '%s'\n", src_filename, video_dst_filename);
    if (audio_stream)
        printf("Demuxing audio from file '%s' into '%s'\n", src_filename, audio_dst_filename);

    /* read frames from the file */
    while (av_read_frame(fmt_ctx, &pkt) >= 0) {
        AVPacket orig_pkt = pkt;
        do {
            ret = decode_packet(&got_frame, 0);
            if (ret < 0)
                break;
            pkt.data += ret;
            pkt.size -= ret;
        } while (pkt.size > 0);
        av_packet_unref(&orig_pkt);
    }

    /* flush cached frames */
    pkt.data = NULL;
    pkt.size = 0;
    do {
        decode_packet(&got_frame, 1);
    } while (got_frame);

    printf("Demuxing succeeded.\n");

    if (video_stream) {
        printf("Play the output video file with the command:\n"
               "ffplay -f rawvideo -pix_fmt %s -video_size %dx%d %s\n",
               av_get_pix_fmt_name(pix_fmt), width, height,
               video_dst_filename);
    }

    if (audio_stream) {
        enum AVSampleFormat sfmt = audio_dec_ctx->sample_fmt;
        int n_channels = audio_dec_ctx->channels;
        const char *fmt;

        if (av_sample_fmt_is_planar(sfmt)) {
            const char *packed = av_get_sample_fmt_name(sfmt);
            printf("Warning: the sample format the decoder produced is planar "
                   "(%s). This example will output the first channel only.\n",
                   packed ? packed : "?");
            sfmt = av_get_packed_sample_fmt(sfmt);
            n_channels = 1;
        }

        if ((ret = get_format_from_sample_fmt(&fmt, sfmt)) < 0)
            goto end;

        printf("Play the output audio file with the command:\n"
               "ffplay -f %s -ac %d -ar %d %s\n",
               fmt, n_channels, audio_dec_ctx->sample_rate,
               audio_dst_filename);
    }

end:
    avcodec_free_context(&video_dec_ctx);
    avcodec_free_context(&audio_dec_ctx);
    avformat_close_input(&fmt_ctx);
    if (video_dst_file)
        fclose(video_dst_file);
    if (audio_dst_file)
        fclose(audio_dst_file);
    av_frame_free(&frame);
    av_free(video_dst_data[0]);

    return ret < 0;
}