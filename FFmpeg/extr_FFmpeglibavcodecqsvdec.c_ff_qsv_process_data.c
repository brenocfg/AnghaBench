#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_17__ ;
typedef  struct TYPE_21__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_27__ {int pix_fmt; scalar_t__ coded_height; scalar_t__ coded_width; int /*<<< orphan*/  profile; int /*<<< orphan*/  level; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  field_order; int /*<<< orphan*/  codec_id; } ;
struct TYPE_26__ {int /*<<< orphan*/  member_0; int /*<<< orphan*/  pos; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_25__ {TYPE_1__* comp; } ;
struct TYPE_24__ {int orig_pix_fmt; int reinit_flag; TYPE_17__* parser; TYPE_15__* avctx_internal; int /*<<< orphan*/  fourcc; scalar_t__ buffered_count; } ;
struct TYPE_23__ {int depth; } ;
struct TYPE_22__ {scalar_t__ format; scalar_t__ coded_height; scalar_t__ coded_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  field_order; int /*<<< orphan*/  flags; } ;
struct TYPE_21__ {int /*<<< orphan*/  profile; int /*<<< orphan*/  level; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_2__ QSVContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_QSV ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 scalar_t__ FFALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  PARSER_FLAG_COMPLETE_FRAMES ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_17__* av_parser_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_parser_parse2 (TYPE_17__*,TYPE_15__*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* av_pix_fmt_desc_get (int) ; 
 TYPE_15__* avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int ff_get_format (TYPE_5__*,int*) ; 
 int ff_qsv_map_pixfmt (scalar_t__,int /*<<< orphan*/ *) ; 
 int qsv_decode (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ *,int*,TYPE_4__*) ; 
 int qsv_decode_init (TYPE_5__*,TYPE_2__*) ; 

int ff_qsv_process_data(AVCodecContext *avctx, QSVContext *q,
                        AVFrame *frame, int *got_frame, AVPacket *pkt)
{
    uint8_t *dummy_data;
    int dummy_size;
    int ret;
    const AVPixFmtDescriptor *desc;

    if (!q->avctx_internal) {
        q->avctx_internal = avcodec_alloc_context3(NULL);
        if (!q->avctx_internal)
            return AVERROR(ENOMEM);

        q->avctx_internal->codec_id = avctx->codec_id;

        q->parser = av_parser_init(avctx->codec_id);
        if (!q->parser)
            return AVERROR(ENOMEM);

        q->parser->flags |= PARSER_FLAG_COMPLETE_FRAMES;
        q->orig_pix_fmt   = AV_PIX_FMT_NONE;
    }

    if (!pkt->size)
        return qsv_decode(avctx, q, frame, got_frame, pkt);

    /* we assume the packets are already split properly and want
     * just the codec parameters here */
    av_parser_parse2(q->parser, q->avctx_internal,
                     &dummy_data, &dummy_size,
                     pkt->data, pkt->size, pkt->pts, pkt->dts,
                     pkt->pos);

    avctx->field_order  = q->parser->field_order;
    /* TODO: flush delayed frames on reinit */
    if (q->parser->format       != q->orig_pix_fmt    ||
        FFALIGN(q->parser->coded_width, 16)  != FFALIGN(avctx->coded_width, 16) ||
        FFALIGN(q->parser->coded_height, 16) != FFALIGN(avctx->coded_height, 16)) {
        enum AVPixelFormat pix_fmts[3] = { AV_PIX_FMT_QSV,
                                           AV_PIX_FMT_NONE,
                                           AV_PIX_FMT_NONE };
        enum AVPixelFormat qsv_format;
        AVPacket zero_pkt = {0};

        if (q->buffered_count) {
            q->reinit_flag = 1;
            /* decode zero-size pkt to flush the buffered pkt before reinit */
            q->buffered_count--;
            return qsv_decode(avctx, q, frame, got_frame, &zero_pkt);
        }

        q->reinit_flag = 0;

        qsv_format = ff_qsv_map_pixfmt(q->parser->format, &q->fourcc);
        if (qsv_format < 0) {
            av_log(avctx, AV_LOG_ERROR,
                   "Decoding pixel format '%s' is not supported\n",
                   av_get_pix_fmt_name(q->parser->format));
            ret = AVERROR(ENOSYS);
            goto reinit_fail;
        }

        q->orig_pix_fmt     = q->parser->format;
        avctx->pix_fmt      = pix_fmts[1] = qsv_format;
        avctx->width        = q->parser->width;
        avctx->height       = q->parser->height;
        avctx->coded_width  = FFALIGN(q->parser->coded_width, 16);
        avctx->coded_height = FFALIGN(q->parser->coded_height, 16);
        avctx->level        = q->avctx_internal->level;
        avctx->profile      = q->avctx_internal->profile;

        ret = ff_get_format(avctx, pix_fmts);
        if (ret < 0)
            goto reinit_fail;

        avctx->pix_fmt = ret;

        desc = av_pix_fmt_desc_get(avctx->pix_fmt);
        if (!desc)
            goto reinit_fail;

         if (desc->comp[0].depth > 8) {
            avctx->coded_width =  FFALIGN(q->parser->coded_width, 32);
            avctx->coded_height = FFALIGN(q->parser->coded_height, 32);
        }

        ret = qsv_decode_init(avctx, q);
        if (ret < 0)
            goto reinit_fail;
    }

    return qsv_decode(avctx, q, frame, got_frame, pkt);

reinit_fail:
    q->orig_pix_fmt = q->parser->format = avctx->pix_fmt = AV_PIX_FMT_NONE;
    return ret;
}