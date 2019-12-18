#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ogg_stream {int /*<<< orphan*/  psize; scalar_t__ pstart; scalar_t__ buf; } ;
struct ogg {struct ogg_stream* streams; } ;
struct TYPE_19__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_18__ {scalar_t__ sample_rate; } ;
struct TYPE_17__ {int /*<<< orphan*/  flags; } ;
struct TYPE_16__ {TYPE_1__** streams; struct ogg* priv_data; } ;
struct TYPE_15__ {TYPE_8__* codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVCodecParserContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_FLAC ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  PARSER_FLAG_COMPLETE_FRAMES ; 
 int /*<<< orphan*/  av_parser_close (TYPE_3__*) ; 
 TYPE_3__* av_parser_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_parser_parse2 (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ **,int*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avcodec_free_context (TYPE_4__**) ; 
 int avcodec_parameters_to_context (TYPE_4__*,TYPE_8__*) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,scalar_t__) ; 

__attribute__((used)) static int
old_flac_header (AVFormatContext * s, int idx)
{
    struct ogg *ogg = s->priv_data;
    AVStream *st = s->streams[idx];
    struct ogg_stream *os = ogg->streams + idx;
    AVCodecParserContext *parser = av_parser_init(AV_CODEC_ID_FLAC);
    AVCodecContext *avctx;
    int size, ret;
    uint8_t *data;

    if (!parser)
        return -1;

    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id = AV_CODEC_ID_FLAC;

    avctx = avcodec_alloc_context3(NULL);
    if (!avctx) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    ret = avcodec_parameters_to_context(avctx, st->codecpar);
    if (ret < 0)
        goto fail;

    parser->flags = PARSER_FLAG_COMPLETE_FRAMES;
    av_parser_parse2(parser, avctx,
                     &data, &size, os->buf + os->pstart, os->psize,
                     AV_NOPTS_VALUE, AV_NOPTS_VALUE, -1);

    av_parser_close(parser);

    if (avctx->sample_rate) {
        avpriv_set_pts_info(st, 64, 1, avctx->sample_rate);
        avcodec_free_context(&avctx);
        return 0;
    }

    avcodec_free_context(&avctx);
    return 1;
fail:
    av_parser_close(parser);
    avcodec_free_context(&avctx);
    return ret;
}