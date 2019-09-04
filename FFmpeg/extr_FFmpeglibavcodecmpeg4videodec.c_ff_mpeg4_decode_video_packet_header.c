#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int size_in_bits; } ;
struct TYPE_14__ {int mb_num; int mb_x; int mb_width; int mb_y; int quant_precision; int chroma_qscale; int qscale; scalar_t__ pict_type; TYPE_3__ gb; int /*<<< orphan*/  avctx; } ;
struct TYPE_15__ {scalar_t__ shape; int time_increment_bits; scalar_t__ vol_sprite_usage; scalar_t__ new_pred; TYPE_1__ m; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ Mpeg4DecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PICTURE_TYPE_S ; 
 scalar_t__ BIN_ONLY_SHAPE ; 
 scalar_t__ GMC_SPRITE ; 
 scalar_t__ RECT_SHAPE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int av_log2 (int) ; 
 int /*<<< orphan*/  check_marker (int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  decode_new_pred (TYPE_2__*,TYPE_3__*) ; 
 int ff_mpeg4_get_video_packet_prefix_length (TYPE_1__*) ; 
 int get_bits (TYPE_3__*,int) ; 
 int get_bits1 (TYPE_3__*) ; 
 int get_bits_count (TYPE_3__*) ; 
 scalar_t__ mpeg4_decode_sprite_trajectory (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  skip_bits (TYPE_3__*,int) ; 

int ff_mpeg4_decode_video_packet_header(Mpeg4DecContext *ctx)
{
    MpegEncContext *s = &ctx->m;

    int mb_num_bits      = av_log2(s->mb_num - 1) + 1;
    int header_extension = 0, mb_num, len;

    /* is there enough space left for a video packet + header */
    if (get_bits_count(&s->gb) > s->gb.size_in_bits - 20)
        return AVERROR_INVALIDDATA;

    for (len = 0; len < 32; len++)
        if (get_bits1(&s->gb))
            break;

    if (len != ff_mpeg4_get_video_packet_prefix_length(s)) {
        av_log(s->avctx, AV_LOG_ERROR, "marker does not match f_code\n");
        return AVERROR_INVALIDDATA;
    }

    if (ctx->shape != RECT_SHAPE) {
        header_extension = get_bits1(&s->gb);
        // FIXME more stuff here
    }

    mb_num = get_bits(&s->gb, mb_num_bits);
    if (mb_num >= s->mb_num || !mb_num) {
        av_log(s->avctx, AV_LOG_ERROR,
               "illegal mb_num in video packet (%d %d) \n", mb_num, s->mb_num);
        return AVERROR_INVALIDDATA;
    }

    s->mb_x = mb_num % s->mb_width;
    s->mb_y = mb_num / s->mb_width;

    if (ctx->shape != BIN_ONLY_SHAPE) {
        int qscale = get_bits(&s->gb, s->quant_precision);
        if (qscale)
            s->chroma_qscale = s->qscale = qscale;
    }

    if (ctx->shape == RECT_SHAPE)
        header_extension = get_bits1(&s->gb);

    if (header_extension) {
        int time_incr = 0;

        while (get_bits1(&s->gb) != 0)
            time_incr++;

        check_marker(s->avctx, &s->gb, "before time_increment in video packed header");
        skip_bits(&s->gb, ctx->time_increment_bits);      /* time_increment */
        check_marker(s->avctx, &s->gb, "before vop_coding_type in video packed header");

        skip_bits(&s->gb, 2); /* vop coding type */
        // FIXME not rect stuff here

        if (ctx->shape != BIN_ONLY_SHAPE) {
            skip_bits(&s->gb, 3); /* intra dc vlc threshold */
            // FIXME don't just ignore everything
            if (s->pict_type == AV_PICTURE_TYPE_S &&
                ctx->vol_sprite_usage == GMC_SPRITE) {
                if (mpeg4_decode_sprite_trajectory(ctx, &s->gb) < 0)
                    return AVERROR_INVALIDDATA;
                av_log(s->avctx, AV_LOG_ERROR, "untested\n");
            }

            // FIXME reduced res stuff here

            if (s->pict_type != AV_PICTURE_TYPE_I) {
                int f_code = get_bits(&s->gb, 3);       /* fcode_for */
                if (f_code == 0)
                    av_log(s->avctx, AV_LOG_ERROR,
                           "Error, video packet header damaged (f_code=0)\n");
            }
            if (s->pict_type == AV_PICTURE_TYPE_B) {
                int b_code = get_bits(&s->gb, 3);
                if (b_code == 0)
                    av_log(s->avctx, AV_LOG_ERROR,
                           "Error, video packet header damaged (b_code=0)\n");
            }
        }
    }
    if (ctx->new_pred)
        decode_new_pred(ctx, &s->gb);

    return 0;
}