#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct TYPE_18__ {int handler_ret; int lines_processed; int nb_pages; TYPE_1__* pages; int /*<<< orphan*/  sub_duration; int /*<<< orphan*/  format_id; scalar_t__ pts; int /*<<< orphan*/  sliced; int /*<<< orphan*/ * vbi; } ;
typedef  TYPE_2__ TeletextContext ;
struct TYPE_22__ {scalar_t__ type; } ;
struct TYPE_16__ {scalar_t__ num; } ;
struct TYPE_21__ {TYPE_13__ pkt_timebase; TYPE_2__* priv_data; } ;
struct TYPE_20__ {scalar_t__ pts; int size; int /*<<< orphan*/ * data; } ;
struct TYPE_19__ {int format; int num_rects; TYPE_9__** rects; int /*<<< orphan*/  pts; int /*<<< orphan*/  end_display_time; scalar_t__ start_display_time; } ;
struct TYPE_17__ {TYPE_9__* sub_rect; int /*<<< orphan*/  pts; } ;
typedef  TYPE_3__ AVSubtitle ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ SUBTITLE_NONE ; 
 int /*<<< orphan*/  VBI_EVENT_TTX_PAGE ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_9__** av_malloc (int) ; 
 scalar_t__ av_rescale_q (scalar_t__,TYPE_13__,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_data_identifier_is_teletext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_5__*,char*,TYPE_2__*,int,int,double) ; 
 int /*<<< orphan*/  handler ; 
 int slice_to_vbi_lines (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  subtitle_rect_free (TYPE_9__**) ; 
 int /*<<< orphan*/  vbi_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,double) ; 
 int /*<<< orphan*/  vbi_decoder_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vbi_decoder_new () ; 
 int /*<<< orphan*/  vbi_event_handler_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int teletext_decode_frame(AVCodecContext *avctx, void *data, int *data_size, AVPacket *pkt)
{
    TeletextContext *ctx = avctx->priv_data;
    AVSubtitle      *sub = data;
    int             ret = 0;
    int j;

    if (!ctx->vbi) {
        if (!(ctx->vbi = vbi_decoder_new()))
            return AVERROR(ENOMEM);
        if (!vbi_event_handler_register(ctx->vbi, VBI_EVENT_TTX_PAGE, handler, ctx)) {
            vbi_decoder_delete(ctx->vbi);
            ctx->vbi = NULL;
            return AVERROR(ENOMEM);
        }
    }

    if (avctx->pkt_timebase.num && pkt->pts != AV_NOPTS_VALUE)
        ctx->pts = av_rescale_q(pkt->pts, avctx->pkt_timebase, AV_TIME_BASE_Q);

    if (pkt->size) {
        int lines;
        const int full_pes_size = pkt->size + 45; /* PES header is 45 bytes */

        // We allow unreasonably big packets, even if the standard only allows a max size of 1472
        if (full_pes_size < 184 || full_pes_size > 65504 || full_pes_size % 184 != 0)
            return AVERROR_INVALIDDATA;

        ctx->handler_ret = pkt->size;

        if (ff_data_identifier_is_teletext(*pkt->data)) {
            if ((lines = slice_to_vbi_lines(ctx, pkt->data + 1, pkt->size - 1)) < 0)
                return lines;
            ff_dlog(avctx, "ctx=%p buf_size=%d lines=%u pkt_pts=%7.3f\n",
                    ctx, pkt->size, lines, (double)pkt->pts/90000.0);
            if (lines > 0) {
                vbi_decode(ctx->vbi, ctx->sliced, lines, 0.0);
                ctx->lines_processed += lines;
            }
        }
        ctx->pts = AV_NOPTS_VALUE;
        ret = ctx->handler_ret;
    }

    if (ret < 0)
        return ret;

    // is there a subtitle to pass?
    if (ctx->nb_pages) {
        int i;
        sub->format = !!ctx->format_id;
        sub->start_display_time = 0;
        sub->end_display_time = ctx->sub_duration;
        sub->num_rects = 0;
        sub->pts = ctx->pages->pts;

        if (ctx->pages->sub_rect->type != SUBTITLE_NONE) {
            sub->rects = av_malloc(sizeof(*sub->rects));
            if (sub->rects) {
                sub->num_rects = 1;
                sub->rects[0] = ctx->pages->sub_rect;
#if FF_API_AVPICTURE
FF_DISABLE_DEPRECATION_WARNINGS
                for (j = 0; j < 4; j++) {
                    sub->rects[0]->pict.data[j] = sub->rects[0]->data[j];
                    sub->rects[0]->pict.linesize[j] = sub->rects[0]->linesize[j];
                }
FF_ENABLE_DEPRECATION_WARNINGS
#endif
            } else {
                ret = AVERROR(ENOMEM);
            }
        } else {
            av_log(avctx, AV_LOG_DEBUG, "sending empty sub\n");
            sub->rects = NULL;
        }
        if (!sub->rects) // no rect was passed
            subtitle_rect_free(&ctx->pages->sub_rect);

        for (i = 0; i < ctx->nb_pages - 1; i++)
            ctx->pages[i] = ctx->pages[i + 1];
        ctx->nb_pages--;

        if (ret >= 0)
            *data_size = 1;
    } else
        *data_size = 0;

    return ret;
}