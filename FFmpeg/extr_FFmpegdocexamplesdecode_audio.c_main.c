#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {scalar_t__ size; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  TYPE_2__ AVCodec ;

/* Variables and functions */
 int AUDIO_INBUF_SIZE ; 
 size_t AUDIO_REFILL_THRESH ; 
 int /*<<< orphan*/  AV_CODEC_ID_MP2 ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* av_packet_alloc () ; 
 int /*<<< orphan*/  av_packet_free (TYPE_1__**) ; 
 int /*<<< orphan*/  av_parser_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_parser_init (int /*<<< orphan*/ ) ; 
 int av_parser_parse2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * avcodec_alloc_context3 (TYPE_2__ const*) ; 
 TYPE_2__* avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ **) ; 
 scalar_t__ avcodec_open2 (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 void* fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
    const char *outfilename, *filename;
    const AVCodec *codec;
    AVCodecContext *c= NULL;
    AVCodecParserContext *parser = NULL;
    int len, ret;
    FILE *f, *outfile;
    uint8_t inbuf[AUDIO_INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    uint8_t *data;
    size_t   data_size;
    AVPacket *pkt;
    AVFrame *decoded_frame = NULL;

    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(0);
    }
    filename    = argv[1];
    outfilename = argv[2];

    pkt = av_packet_alloc();

    /* find the MPEG audio decoder */
    codec = avcodec_find_decoder(AV_CODEC_ID_MP2);
    if (!codec) {
        fprintf(stderr, "Codec not found\n");
        exit(1);
    }

    parser = av_parser_init(codec->id);
    if (!parser) {
        fprintf(stderr, "Parser not found\n");
        exit(1);
    }

    c = avcodec_alloc_context3(codec);
    if (!c) {
        fprintf(stderr, "Could not allocate audio codec context\n");
        exit(1);
    }

    /* open it */
    if (avcodec_open2(c, codec, NULL) < 0) {
        fprintf(stderr, "Could not open codec\n");
        exit(1);
    }

    f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "Could not open %s\n", filename);
        exit(1);
    }
    outfile = fopen(outfilename, "wb");
    if (!outfile) {
        av_free(c);
        exit(1);
    }

    /* decode until eof */
    data      = inbuf;
    data_size = fread(inbuf, 1, AUDIO_INBUF_SIZE, f);

    while (data_size > 0) {
        if (!decoded_frame) {
            if (!(decoded_frame = av_frame_alloc())) {
                fprintf(stderr, "Could not allocate audio frame\n");
                exit(1);
            }
        }

        ret = av_parser_parse2(parser, c, &pkt->data, &pkt->size,
                               data, data_size,
                               AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
        if (ret < 0) {
            fprintf(stderr, "Error while parsing\n");
            exit(1);
        }
        data      += ret;
        data_size -= ret;

        if (pkt->size)
            decode(c, pkt, decoded_frame, outfile);

        if (data_size < AUDIO_REFILL_THRESH) {
            memmove(inbuf, data, data_size);
            data = inbuf;
            len = fread(data + data_size, 1,
                        AUDIO_INBUF_SIZE - data_size, f);
            if (len > 0)
                data_size += len;
        }
    }

    /* flush the decoder */
    pkt->data = NULL;
    pkt->size = 0;
    decode(c, pkt, decoded_frame, outfile);

    fclose(outfile);
    fclose(f);

    avcodec_free_context(&c);
    av_parser_close(parser);
    av_frame_free(&decoded_frame);
    av_packet_free(&pkt);

    return 0;
}