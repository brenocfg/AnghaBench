#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {int mb_width; int mb_height; scalar_t__ mb_num; int /*<<< orphan*/  qscale; scalar_t__ mb_y; scalar_t__ mb_x; int /*<<< orphan*/  gb; } ;
struct TYPE_7__ {scalar_t__ shape; TYPE_1__ m; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ Mpeg4DecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ BIN_ONLY_SHAPE ; 
 scalar_t__ SLICE_START_CODE ; 
 int av_log2 (int) ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpeg_get_qscale (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_studio_dc_predictors (TYPE_1__*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

int ff_mpeg4_decode_studio_slice_header(Mpeg4DecContext *ctx)
{
    MpegEncContext *s = &ctx->m;
    GetBitContext *gb = &s->gb;
    unsigned vlc_len;
    uint16_t mb_num;

    if (get_bits_left(gb) >= 32 && get_bits_long(gb, 32) == SLICE_START_CODE) {
        vlc_len = av_log2(s->mb_width * s->mb_height) + 1;
        mb_num = get_bits(gb, vlc_len);

        if (mb_num >= s->mb_num)
            return AVERROR_INVALIDDATA;

        s->mb_x = mb_num % s->mb_width;
        s->mb_y = mb_num / s->mb_width;

        if (ctx->shape != BIN_ONLY_SHAPE)
            s->qscale = mpeg_get_qscale(s);

        if (get_bits1(gb)) {  /* slice_extension_flag */
            skip_bits1(gb);   /* intra_slice */
            skip_bits1(gb);   /* slice_VOP_id_enable */
            skip_bits(gb, 6); /* slice_VOP_id */
            while (get_bits1(gb)) /* extra_bit_slice */
                skip_bits(gb, 8); /* extra_information_slice */
        }

        reset_studio_dc_predictors(s);
    }
    else {
        return AVERROR_INVALIDDATA;
    }

    return 0;
}