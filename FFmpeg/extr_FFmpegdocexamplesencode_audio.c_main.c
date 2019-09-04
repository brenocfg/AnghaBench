#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_13__ {int bit_rate; int sample_rate; int channels; int frame_size; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  sample_fmt; } ;
struct TYPE_12__ {int nb_samples; scalar_t__* data; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_MP2 ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S16 ; 
 int M_PI ; 
 TYPE_1__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_1__**) ; 
 int av_frame_get_buffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int av_frame_make_writable (TYPE_1__*) ; 
 int av_get_channel_layout_nb_channels (int /*<<< orphan*/ ) ; 
 char* av_get_sample_fmt_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_packet_alloc () ; 
 int /*<<< orphan*/  av_packet_free (int /*<<< orphan*/ **) ; 
 TYPE_2__* avcodec_alloc_context3 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * avcodec_find_encoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_free_context (TYPE_2__**) ; 
 scalar_t__ avcodec_open2 (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_sample_fmt (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  select_channel_layout (int /*<<< orphan*/  const*) ; 
 int select_sample_rate (int /*<<< orphan*/  const*) ; 
 int sin (float) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
    const char *filename;
    const AVCodec *codec;
    AVCodecContext *c= NULL;
    AVFrame *frame;
    AVPacket *pkt;
    int i, j, k, ret;
    FILE *f;
    uint16_t *samples;
    float t, tincr;

    if (argc <= 1) {
        fprintf(stderr, "Usage: %s <output file>\n", argv[0]);
        return 0;
    }
    filename = argv[1];

    /* find the MP2 encoder */
    codec = avcodec_find_encoder(AV_CODEC_ID_MP2);
    if (!codec) {
        fprintf(stderr, "Codec not found\n");
        exit(1);
    }

    c = avcodec_alloc_context3(codec);
    if (!c) {
        fprintf(stderr, "Could not allocate audio codec context\n");
        exit(1);
    }

    /* put sample parameters */
    c->bit_rate = 64000;

    /* check that the encoder supports s16 pcm input */
    c->sample_fmt = AV_SAMPLE_FMT_S16;
    if (!check_sample_fmt(codec, c->sample_fmt)) {
        fprintf(stderr, "Encoder does not support sample format %s",
                av_get_sample_fmt_name(c->sample_fmt));
        exit(1);
    }

    /* select other audio parameters supported by the encoder */
    c->sample_rate    = select_sample_rate(codec);
    c->channel_layout = select_channel_layout(codec);
    c->channels       = av_get_channel_layout_nb_channels(c->channel_layout);

    /* open it */
    if (avcodec_open2(c, codec, NULL) < 0) {
        fprintf(stderr, "Could not open codec\n");
        exit(1);
    }

    f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "Could not open %s\n", filename);
        exit(1);
    }

    /* packet for holding encoded output */
    pkt = av_packet_alloc();
    if (!pkt) {
        fprintf(stderr, "could not allocate the packet\n");
        exit(1);
    }

    /* frame containing input raw audio */
    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate audio frame\n");
        exit(1);
    }

    frame->nb_samples     = c->frame_size;
    frame->format         = c->sample_fmt;
    frame->channel_layout = c->channel_layout;

    /* allocate the data buffers */
    ret = av_frame_get_buffer(frame, 0);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate audio data buffers\n");
        exit(1);
    }

    /* encode a single tone sound */
    t = 0;
    tincr = 2 * M_PI * 440.0 / c->sample_rate;
    for (i = 0; i < 200; i++) {
        /* make sure the frame is writable -- makes a copy if the encoder
         * kept a reference internally */
        ret = av_frame_make_writable(frame);
        if (ret < 0)
            exit(1);
        samples = (uint16_t*)frame->data[0];

        for (j = 0; j < c->frame_size; j++) {
            samples[2*j] = (int)(sin(t) * 10000);

            for (k = 1; k < c->channels; k++)
                samples[2*j + k] = samples[2*j];
            t += tincr;
        }
        encode(c, frame, pkt, f);
    }

    /* flush the encoder */
    encode(c, NULL, pkt, f);

    fclose(f);

    av_frame_free(&frame);
    av_packet_free(&pkt);
    avcodec_free_context(&c);

    return 0;
}