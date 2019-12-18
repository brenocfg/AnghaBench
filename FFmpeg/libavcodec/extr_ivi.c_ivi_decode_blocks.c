#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  ivi_mc_func ;
typedef  int /*<<< orphan*/  ivi_mc_avg_func ;
typedef  scalar_t__ int32_t ;
struct TYPE_15__ {scalar_t__ codec_id; } ;
struct TYPE_14__ {int blk_size; int mb_size; size_t glob_quant; size_t* intra_scale; size_t* inter_scale; int is_halfpel; scalar_t__ pitch; scalar_t__ aheight; } ;
struct TYPE_13__ {int type; size_t cbp; size_t buf_offs; size_t q_delta; int mv_x; int mv_y; int b_mv_x; int b_mv_y; scalar_t__ xpos; scalar_t__ ypos; } ;
struct TYPE_12__ {int num_MBs; TYPE_2__* mbs; } ;
typedef  TYPE_1__ IVITile ;
typedef  TYPE_2__ IVIMbInfo ;
typedef  TYPE_3__ IVIBandDesc ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_INDEO4 ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 size_t av_clip (size_t,int /*<<< orphan*/ ,int) ; 
 size_t av_clip_uintp2 (size_t,int) ; 
 int /*<<< orphan*/  ff_ivi_mc_4x4_delta ; 
 int /*<<< orphan*/  ff_ivi_mc_4x4_no_delta ; 
 int /*<<< orphan*/  ff_ivi_mc_8x8_delta ; 
 int /*<<< orphan*/  ff_ivi_mc_8x8_no_delta ; 
 int /*<<< orphan*/  ff_ivi_mc_avg_4x4_delta ; 
 int /*<<< orphan*/  ff_ivi_mc_avg_4x4_no_delta ; 
 int /*<<< orphan*/  ff_ivi_mc_avg_8x8_delta ; 
 int /*<<< orphan*/  ff_ivi_mc_avg_8x8_no_delta ; 
 int ivi_dc_transform (TYPE_3__ const*,scalar_t__*,size_t,int) ; 
 int ivi_decode_coded_blocks (int /*<<< orphan*/ *,TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,scalar_t__*,int,int,int,size_t,size_t,TYPE_4__*) ; 
 int ivi_mc (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int,int,int,int,int,int) ; 

__attribute__((used)) static int ivi_decode_blocks(GetBitContext *gb, const IVIBandDesc *band,
                             IVITile *tile, AVCodecContext *avctx)
{
    int mbn, blk, num_blocks, blk_size, ret, is_intra;
    int mc_type = 0, mc_type2 = -1;
    int mv_x = 0, mv_y = 0, mv_x2 = 0, mv_y2 = 0;
    int32_t prev_dc;
    uint32_t cbp, quant, buf_offs;
    IVIMbInfo *mb;
    ivi_mc_func mc_with_delta_func, mc_no_delta_func;
    ivi_mc_avg_func mc_avg_with_delta_func, mc_avg_no_delta_func;
    const uint8_t *scale_tab;

    /* init intra prediction for the DC coefficient */
    prev_dc    = 0;
    blk_size   = band->blk_size;
    /* number of blocks per mb */
    num_blocks = (band->mb_size != blk_size) ? 4 : 1;
    if (blk_size == 8) {
        mc_with_delta_func     = ff_ivi_mc_8x8_delta;
        mc_no_delta_func       = ff_ivi_mc_8x8_no_delta;
        mc_avg_with_delta_func = ff_ivi_mc_avg_8x8_delta;
        mc_avg_no_delta_func   = ff_ivi_mc_avg_8x8_no_delta;
    } else {
        mc_with_delta_func     = ff_ivi_mc_4x4_delta;
        mc_no_delta_func       = ff_ivi_mc_4x4_no_delta;
        mc_avg_with_delta_func = ff_ivi_mc_avg_4x4_delta;
        mc_avg_no_delta_func   = ff_ivi_mc_avg_4x4_no_delta;
    }

    for (mbn = 0, mb = tile->mbs; mbn < tile->num_MBs; mb++, mbn++) {
        is_intra = !mb->type;
        cbp      = mb->cbp;
        buf_offs = mb->buf_offs;

        quant = band->glob_quant + mb->q_delta;
        if (avctx->codec_id == AV_CODEC_ID_INDEO4)
            quant = av_clip_uintp2(quant, 5);
        else
            quant = av_clip(quant, 0, 23);

        scale_tab = is_intra ? band->intra_scale : band->inter_scale;
        if (scale_tab)
            quant = scale_tab[quant];

        if (!is_intra) {
            mv_x  = mb->mv_x;
            mv_y  = mb->mv_y;
            mv_x2 = mb->b_mv_x;
            mv_y2 = mb->b_mv_y;
            if (band->is_halfpel) {
                mc_type  = ((mv_y  & 1) << 1) | (mv_x  & 1);
                mc_type2 = ((mv_y2 & 1) << 1) | (mv_x2 & 1);
                mv_x  >>= 1;
                mv_y  >>= 1;
                mv_x2 >>= 1;
                mv_y2 >>= 1; /* convert halfpel vectors into fullpel ones */
            }
            if (mb->type == 2)
                mc_type = -1;
            if (mb->type != 2 && mb->type != 3)
                mc_type2 = -1;
            if (mb->type) {
                int dmv_x, dmv_y, cx, cy;

                dmv_x = mb->mv_x >> band->is_halfpel;
                dmv_y = mb->mv_y >> band->is_halfpel;
                cx    = mb->mv_x &  band->is_halfpel;
                cy    = mb->mv_y &  band->is_halfpel;

                if (mb->xpos + dmv_x < 0 ||
                    mb->xpos + dmv_x + band->mb_size + cx > band->pitch ||
                    mb->ypos + dmv_y < 0 ||
                    mb->ypos + dmv_y + band->mb_size + cy > band->aheight) {
                    return AVERROR_INVALIDDATA;
                }
            }
            if (mb->type == 2 || mb->type == 3) {
                int dmv_x, dmv_y, cx, cy;

                dmv_x = mb->b_mv_x >> band->is_halfpel;
                dmv_y = mb->b_mv_y >> band->is_halfpel;
                cx    = mb->b_mv_x &  band->is_halfpel;
                cy    = mb->b_mv_y &  band->is_halfpel;

                if (mb->xpos + dmv_x < 0 ||
                    mb->xpos + dmv_x + band->mb_size + cx > band->pitch ||
                    mb->ypos + dmv_y < 0 ||
                    mb->ypos + dmv_y + band->mb_size + cy > band->aheight) {
                    return AVERROR_INVALIDDATA;
                }
            }
        }

        for (blk = 0; blk < num_blocks; blk++) {
            /* adjust block position in the buffer according to its number */
            if (blk & 1) {
                buf_offs += blk_size;
            } else if (blk == 2) {
                buf_offs -= blk_size;
                buf_offs += blk_size * band->pitch;
            }

            if (cbp & 1) { /* block coded ? */
                ret = ivi_decode_coded_blocks(gb, band, mc_with_delta_func,
                                              mc_avg_with_delta_func,
                                              mv_x, mv_y, mv_x2, mv_y2,
                                              &prev_dc, is_intra,
                                              mc_type, mc_type2, quant,
                                              buf_offs, avctx);
                if (ret < 0)
                    return ret;
            } else {
                int buf_size = band->pitch * band->aheight - buf_offs;
                int min_size = (blk_size - 1) * band->pitch + blk_size;

                if (min_size > buf_size)
                    return AVERROR_INVALIDDATA;
                /* block not coded */
                /* for intra blocks apply the dc slant transform */
                /* for inter - perform the motion compensation without delta */
                if (is_intra) {
                    ret = ivi_dc_transform(band, &prev_dc, buf_offs, blk_size);
                    if (ret < 0)
                        return ret;
                } else {
                    ret = ivi_mc(band, mc_no_delta_func, mc_avg_no_delta_func,
                                 buf_offs, mv_x, mv_y, mv_x2, mv_y2,
                                 mc_type, mc_type2);
                    if (ret < 0)
                        return ret;
                }
            }

            cbp >>= 1;
        }// for blk
    }// for mbn

    align_get_bits(gb);

    return 0;
}