#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ type; int nb_refs; int is_reference; int /*<<< orphan*/ * ref_count; scalar_t__ force_idr; scalar_t__ encode_issued; struct TYPE_18__* next; int /*<<< orphan*/  b_depth; TYPE_1__** refs; } ;
typedef  TYPE_2__ VAAPIEncodePicture ;
struct TYPE_19__ {int idr_counter; int gop_per_idr; int b_per_p; int gop_counter; int gop_size; scalar_t__ input_order; scalar_t__ decode_delay; TYPE_2__* next_prev; scalar_t__ end_of_stream; TYPE_2__* pic_end; TYPE_2__* pic_start; scalar_t__ closed_gop; } ;
typedef  TYPE_3__ VAAPIEncodeContext ;
struct TYPE_20__ {TYPE_3__* priv_data; } ;
struct TYPE_17__ {int /*<<< orphan*/  encode_issued; } ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ PICTURE_TYPE_B ; 
 scalar_t__ PICTURE_TYPE_I ; 
 scalar_t__ PICTURE_TYPE_IDR ; 
 scalar_t__ PICTURE_TYPE_P ; 
 int /*<<< orphan*/  av_assert0 (TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  vaapi_encode_add_ref (TYPE_4__*,TYPE_2__*,TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  vaapi_encode_set_b_pictures (TYPE_4__*,TYPE_2__*,TYPE_2__*,TYPE_2__*,int,TYPE_2__**) ; 

__attribute__((used)) static int vaapi_encode_pick_next(AVCodecContext *avctx,
                                  VAAPIEncodePicture **pic_out)
{
    VAAPIEncodeContext *ctx = avctx->priv_data;
    VAAPIEncodePicture *pic = NULL, *next, *start;
    int i, b_counter, closed_gop_end;

    // If there are any B-frames already queued, the next one to encode
    // is the earliest not-yet-issued frame for which all references are
    // available.
    for (pic = ctx->pic_start; pic; pic = pic->next) {
        if (pic->encode_issued)
            continue;
        if (pic->type != PICTURE_TYPE_B)
            continue;
        for (i = 0; i < pic->nb_refs; i++) {
            if (!pic->refs[i]->encode_issued)
                break;
        }
        if (i == pic->nb_refs)
            break;
    }

    if (pic) {
        av_log(avctx, AV_LOG_DEBUG, "Pick B-picture at depth %d to "
               "encode next.\n", pic->b_depth);
        *pic_out = pic;
        return 0;
    }

    // Find the B-per-Pth available picture to become the next picture
    // on the top layer.
    start = NULL;
    b_counter = 0;
    closed_gop_end = ctx->closed_gop ||
                     ctx->idr_counter == ctx->gop_per_idr;
    for (pic = ctx->pic_start; pic; pic = next) {
        next = pic->next;
        if (pic->encode_issued) {
            start = pic;
            continue;
        }
        // If the next available picture is force-IDR, encode it to start
        // a new GOP immediately.
        if (pic->force_idr)
            break;
        if (b_counter == ctx->b_per_p)
            break;
        // If this picture ends a closed GOP or starts a new GOP then it
        // needs to be in the top layer.
        if (ctx->gop_counter + b_counter + closed_gop_end >= ctx->gop_size)
            break;
        // If the picture after this one is force-IDR, we need to encode
        // this one in the top layer.
        if (next && next->force_idr)
            break;
        ++b_counter;
    }

    // At the end of the stream the last picture must be in the top layer.
    if (!pic && ctx->end_of_stream) {
        --b_counter;
        pic = ctx->pic_end;
        if (pic->encode_issued)
            return AVERROR_EOF;
    }

    if (!pic) {
        av_log(avctx, AV_LOG_DEBUG, "Pick nothing to encode next - "
               "need more input for reference pictures.\n");
        return AVERROR(EAGAIN);
    }
    if (ctx->input_order <= ctx->decode_delay && !ctx->end_of_stream) {
        av_log(avctx, AV_LOG_DEBUG, "Pick nothing to encode next - "
               "need more input for timestamps.\n");
        return AVERROR(EAGAIN);
    }

    if (pic->force_idr) {
        av_log(avctx, AV_LOG_DEBUG, "Pick forced IDR-picture to "
               "encode next.\n");
        pic->type = PICTURE_TYPE_IDR;
        ctx->idr_counter = 1;
        ctx->gop_counter = 1;

    } else if (ctx->gop_counter + b_counter >= ctx->gop_size) {
        if (ctx->idr_counter == ctx->gop_per_idr) {
            av_log(avctx, AV_LOG_DEBUG, "Pick new-GOP IDR-picture to "
                   "encode next.\n");
            pic->type = PICTURE_TYPE_IDR;
            ctx->idr_counter = 1;
        } else {
            av_log(avctx, AV_LOG_DEBUG, "Pick new-GOP I-picture to "
                   "encode next.\n");
            pic->type = PICTURE_TYPE_I;
            ++ctx->idr_counter;
        }
        ctx->gop_counter = 1;

    } else {
        if (ctx->gop_counter + b_counter + closed_gop_end == ctx->gop_size) {
            av_log(avctx, AV_LOG_DEBUG, "Pick group-end P-picture to "
                   "encode next.\n");
        } else {
            av_log(avctx, AV_LOG_DEBUG, "Pick normal P-picture to "
                   "encode next.\n");
        }
        pic->type = PICTURE_TYPE_P;
        av_assert0(start);
        ctx->gop_counter += 1 + b_counter;
    }
    pic->is_reference = 1;
    *pic_out = pic;

    vaapi_encode_add_ref(avctx, pic, pic, 0, 1, 0);
    if (pic->type != PICTURE_TYPE_IDR) {
        vaapi_encode_add_ref(avctx, pic, start,
                             pic->type == PICTURE_TYPE_P,
                             b_counter > 0, 0);
        vaapi_encode_add_ref(avctx, pic, ctx->next_prev, 0, 0, 1);
    }
    if (ctx->next_prev)
        --ctx->next_prev->ref_count[0];

    if (b_counter > 0) {
        vaapi_encode_set_b_pictures(avctx, start, pic, pic, 1,
                                    &ctx->next_prev);
    } else {
        ctx->next_prev = pic;
    }
    ++ctx->next_prev->ref_count[0];
    return 0;
}