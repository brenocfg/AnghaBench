#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  (* vc1_inv_trans_8x8 ) (int*) ;} ;
struct TYPE_21__ {int* qscale_table; int /*<<< orphan*/ * mb_type; scalar_t__*** motion_val; } ;
struct TYPE_23__ {int mb_x; int mb_y; int mb_stride; int* mbskip_table; int mb_intra; size_t* block_index; int linesize; size_t* block_wrap; int uvlinesize; TYPE_4__ current_picture; scalar_t__** dc_val; TYPE_3__* avctx; scalar_t__* dest; int /*<<< orphan*/  first_slice_line; void* ac_pred; int /*<<< orphan*/  gb; } ;
struct TYPE_22__ {int ttfrm; int pq; int* mv_type_mb_plane; int** mb_type; size_t tt_index; int a_avail; int c_avail; int*** block; size_t cur_blk_idx; int* cbp; int* ttblk; int* is_intra; scalar_t__ overlap; int /*<<< orphan*/  range_y; int /*<<< orphan*/  range_x; int /*<<< orphan*/  ttmbf; scalar_t__ rangeredfrm; TYPE_2__ vc1dsp; int /*<<< orphan*/  codingset; int /*<<< orphan*/  codingset2; TYPE_1__* cbpcy_vlc; TYPE_6__ s; scalar_t__ skip_is_raw; scalar_t__ mv_type_is_raw; } ;
typedef  TYPE_5__ VC1Context ;
struct TYPE_20__ {int flags; } ;
struct TYPE_18__ {int /*<<< orphan*/  table; } ;
struct TYPE_17__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_6__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 scalar_t__ CONFIG_GRAY ; 
 int /*<<< orphan*/  GET_MQUANT () ; 
 int /*<<< orphan*/  GET_MVDATA (int,int) ; 
 int /*<<< orphan*/  MB_TYPE_16x16 ; 
 int /*<<< orphan*/  MB_TYPE_INTRA ; 
 int /*<<< orphan*/  MB_TYPE_SKIP ; 
 int /*<<< orphan*/  VC1_CBPCY_P_VLC_BITS ; 
 int /*<<< orphan*/  VC1_TTMB_VLC_BITS ; 
 size_t* block_map ; 
 int /*<<< orphan*/  ff_vc1_mc_1mv (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_vc1_mc_4mv_chroma (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_vc1_mc_4mv_luma (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_vc1_p_overlap_filter (TYPE_5__*) ; 
 int /*<<< orphan*/  ff_vc1_pred_mv (TYPE_5__*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_11__* ff_vc1_ttmb_vlc ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int*) ; 
 int /*<<< orphan*/  stub2 (int*) ; 
 int /*<<< orphan*/  vc1_decode_intra_block (TYPE_5__*,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int vc1_decode_p_block (TYPE_5__*,int*,int,int,int,int,scalar_t__,int,int,int*) ; 
 int /*<<< orphan*/  vc1_put_blocks_clamped (TYPE_5__*,int) ; 

__attribute__((used)) static int vc1_decode_p_mb(VC1Context *v)
{
    MpegEncContext *s = &v->s;
    GetBitContext *gb = &s->gb;
    int i, j;
    int mb_pos = s->mb_x + s->mb_y * s->mb_stride;
    int cbp; /* cbp decoding stuff */
    int mqdiff, mquant; /* MB quantization */
    int ttmb = v->ttfrm; /* MB Transform type */

    int mb_has_coeffs = 1; /* last_flag */
    int dmv_x, dmv_y; /* Differential MV components */
    int index, index1; /* LUT indexes */
    int val, sign; /* temp values */
    int first_block = 1;
    int dst_idx, off;
    int skipped, fourmv;
    int block_cbp = 0, pat, block_tt = 0, block_intra = 0;

    mquant = v->pq; /* lossy initialization */

    if (v->mv_type_is_raw)
        fourmv = get_bits1(gb);
    else
        fourmv = v->mv_type_mb_plane[mb_pos];
    if (v->skip_is_raw)
        skipped = get_bits1(gb);
    else
        skipped = v->s.mbskip_table[mb_pos];

    if (!fourmv) { /* 1MV mode */
        if (!skipped) {
            GET_MVDATA(dmv_x, dmv_y);

            if (s->mb_intra) {
                s->current_picture.motion_val[1][s->block_index[0]][0] = 0;
                s->current_picture.motion_val[1][s->block_index[0]][1] = 0;
            }
            s->current_picture.mb_type[mb_pos] = s->mb_intra ? MB_TYPE_INTRA : MB_TYPE_16x16;
            ff_vc1_pred_mv(v, 0, dmv_x, dmv_y, 1, v->range_x, v->range_y, v->mb_type[0], 0, 0);

            /* FIXME Set DC val for inter block ? */
            if (s->mb_intra && !mb_has_coeffs) {
                GET_MQUANT();
                s->ac_pred = get_bits1(gb);
                cbp        = 0;
            } else if (mb_has_coeffs) {
                if (s->mb_intra)
                    s->ac_pred = get_bits1(gb);
                cbp = get_vlc2(&v->s.gb, v->cbpcy_vlc->table, VC1_CBPCY_P_VLC_BITS, 2);
                GET_MQUANT();
            } else {
                mquant = v->pq;
                cbp    = 0;
            }
            s->current_picture.qscale_table[mb_pos] = mquant;

            if (!v->ttmbf && !s->mb_intra && mb_has_coeffs)
                ttmb = get_vlc2(gb, ff_vc1_ttmb_vlc[v->tt_index].table,
                                VC1_TTMB_VLC_BITS, 2);
            if (!s->mb_intra) ff_vc1_mc_1mv(v, 0);
            dst_idx = 0;
            for (i = 0; i < 6; i++) {
                s->dc_val[0][s->block_index[i]] = 0;
                dst_idx += i >> 2;
                val = ((cbp >> (5 - i)) & 1);
                off = (i & 4) ? 0 : ((i & 1) * 8 + (i & 2) * 4 * s->linesize);
                v->mb_type[0][s->block_index[i]] = s->mb_intra;
                if (s->mb_intra) {
                    /* check if prediction blocks A and C are available */
                    v->a_avail = v->c_avail = 0;
                    if (i == 2 || i == 3 || !s->first_slice_line)
                        v->a_avail = v->mb_type[0][s->block_index[i] - s->block_wrap[i]];
                    if (i == 1 || i == 3 || s->mb_x)
                        v->c_avail = v->mb_type[0][s->block_index[i] - 1];

                    vc1_decode_intra_block(v, v->block[v->cur_blk_idx][block_map[i]], i, val, mquant,
                                           (i & 4) ? v->codingset2 : v->codingset);
                    if (CONFIG_GRAY && (i > 3) && (s->avctx->flags & AV_CODEC_FLAG_GRAY))
                        continue;
                    v->vc1dsp.vc1_inv_trans_8x8(v->block[v->cur_blk_idx][block_map[i]]);
                    if (v->rangeredfrm)
                        for (j = 0; j < 64; j++)
                            v->block[v->cur_blk_idx][block_map[i]][j] <<= 1;
                    block_cbp   |= 0xF << (i << 2);
                    block_intra |= 1 << i;
                } else if (val) {
                    pat = vc1_decode_p_block(v, v->block[v->cur_blk_idx][block_map[i]], i, mquant, ttmb, first_block,
                                             s->dest[dst_idx] + off, (i & 4) ? s->uvlinesize : s->linesize,
                                             CONFIG_GRAY && (i & 4) && (s->avctx->flags & AV_CODEC_FLAG_GRAY), &block_tt);
                    block_cbp |= pat << (i << 2);
                    if (!v->ttmbf && ttmb < 8)
                        ttmb = -1;
                    first_block = 0;
                }
            }
        } else { // skipped
            s->mb_intra = 0;
            for (i = 0; i < 6; i++) {
                v->mb_type[0][s->block_index[i]] = 0;
                s->dc_val[0][s->block_index[i]]  = 0;
            }
            s->current_picture.mb_type[mb_pos]      = MB_TYPE_SKIP;
            s->current_picture.qscale_table[mb_pos] = 0;
            ff_vc1_pred_mv(v, 0, 0, 0, 1, v->range_x, v->range_y, v->mb_type[0], 0, 0);
            ff_vc1_mc_1mv(v, 0);
        }
    } else { // 4MV mode
        if (!skipped /* unskipped MB */) {
            int intra_count = 0, coded_inter = 0;
            int is_intra[6], is_coded[6];
            /* Get CBPCY */
            cbp = get_vlc2(&v->s.gb, v->cbpcy_vlc->table, VC1_CBPCY_P_VLC_BITS, 2);
            for (i = 0; i < 6; i++) {
                val = ((cbp >> (5 - i)) & 1);
                s->dc_val[0][s->block_index[i]] = 0;
                s->mb_intra                     = 0;
                if (i < 4) {
                    dmv_x = dmv_y = 0;
                    s->mb_intra   = 0;
                    mb_has_coeffs = 0;
                    if (val) {
                        GET_MVDATA(dmv_x, dmv_y);
                    }
                    ff_vc1_pred_mv(v, i, dmv_x, dmv_y, 0, v->range_x, v->range_y, v->mb_type[0], 0, 0);
                    if (!s->mb_intra)
                        ff_vc1_mc_4mv_luma(v, i, 0, 0);
                    intra_count += s->mb_intra;
                    is_intra[i]  = s->mb_intra;
                    is_coded[i]  = mb_has_coeffs;
                }
                if (i & 4) {
                    is_intra[i] = (intra_count >= 3);
                    is_coded[i] = val;
                }
                if (i == 4)
                    ff_vc1_mc_4mv_chroma(v, 0);
                v->mb_type[0][s->block_index[i]] = is_intra[i];
                if (!coded_inter)
                    coded_inter = !is_intra[i] & is_coded[i];
            }
            // if there are no coded blocks then don't do anything more
            dst_idx = 0;
            if (!intra_count && !coded_inter)
                goto end;
            GET_MQUANT();
            s->current_picture.qscale_table[mb_pos] = mquant;
            /* test if block is intra and has pred */
            {
                int intrapred = 0;
                for (i = 0; i < 6; i++)
                    if (is_intra[i]) {
                        if (((!s->first_slice_line || (i == 2 || i == 3)) && v->mb_type[0][s->block_index[i] - s->block_wrap[i]])
                            || ((s->mb_x || (i == 1 || i == 3)) && v->mb_type[0][s->block_index[i] - 1])) {
                            intrapred = 1;
                            break;
                        }
                    }
                if (intrapred)
                    s->ac_pred = get_bits1(gb);
                else
                    s->ac_pred = 0;
            }
            if (!v->ttmbf && coded_inter)
                ttmb = get_vlc2(gb, ff_vc1_ttmb_vlc[v->tt_index].table, VC1_TTMB_VLC_BITS, 2);
            for (i = 0; i < 6; i++) {
                dst_idx    += i >> 2;
                off         = (i & 4) ? 0 : ((i & 1) * 8 + (i & 2) * 4 * s->linesize);
                s->mb_intra = is_intra[i];
                if (is_intra[i]) {
                    /* check if prediction blocks A and C are available */
                    v->a_avail = v->c_avail = 0;
                    if (i == 2 || i == 3 || !s->first_slice_line)
                        v->a_avail = v->mb_type[0][s->block_index[i] - s->block_wrap[i]];
                    if (i == 1 || i == 3 || s->mb_x)
                        v->c_avail = v->mb_type[0][s->block_index[i] - 1];

                    vc1_decode_intra_block(v, v->block[v->cur_blk_idx][block_map[i]], i, is_coded[i], mquant,
                                           (i & 4) ? v->codingset2 : v->codingset);
                    if (CONFIG_GRAY && (i > 3) && (s->avctx->flags & AV_CODEC_FLAG_GRAY))
                        continue;
                    v->vc1dsp.vc1_inv_trans_8x8(v->block[v->cur_blk_idx][block_map[i]]);
                    if (v->rangeredfrm)
                        for (j = 0; j < 64; j++)
                            v->block[v->cur_blk_idx][block_map[i]][j] <<= 1;
                    block_cbp   |= 0xF << (i << 2);
                    block_intra |= 1 << i;
                } else if (is_coded[i]) {
                    pat = vc1_decode_p_block(v, v->block[v->cur_blk_idx][block_map[i]], i, mquant, ttmb,
                                             first_block, s->dest[dst_idx] + off,
                                             (i & 4) ? s->uvlinesize : s->linesize,
                                             CONFIG_GRAY && (i & 4) && (s->avctx->flags & AV_CODEC_FLAG_GRAY),
                                             &block_tt);
                    block_cbp |= pat << (i << 2);
                    if (!v->ttmbf && ttmb < 8)
                        ttmb = -1;
                    first_block = 0;
                }
            }
        } else { // skipped MB
            s->mb_intra                               = 0;
            s->current_picture.qscale_table[mb_pos] = 0;
            for (i = 0; i < 6; i++) {
                v->mb_type[0][s->block_index[i]] = 0;
                s->dc_val[0][s->block_index[i]]  = 0;
            }
            for (i = 0; i < 4; i++) {
                ff_vc1_pred_mv(v, i, 0, 0, 0, v->range_x, v->range_y, v->mb_type[0], 0, 0);
                ff_vc1_mc_4mv_luma(v, i, 0, 0);
            }
            ff_vc1_mc_4mv_chroma(v, 0);
            s->current_picture.qscale_table[mb_pos] = 0;
        }
    }
end:
    if (v->overlap && v->pq >= 9)
        ff_vc1_p_overlap_filter(v);
    vc1_put_blocks_clamped(v, 1);

    v->cbp[s->mb_x]      = block_cbp;
    v->ttblk[s->mb_x]    = block_tt;
    v->is_intra[s->mb_x] = block_intra;

    return 0;
}