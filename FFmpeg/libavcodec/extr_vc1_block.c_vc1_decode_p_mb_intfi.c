#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;

/* Type definitions */
struct TYPE_25__ {int* qscale_table; int /*<<< orphan*/ * mb_type; scalar_t__*** motion_val; } ;
struct TYPE_28__ {int mb_x; int mb_y; int mb_stride; int mb_intra; size_t* block_index; size_t* block_wrap; int linesize; int uvlinesize; TYPE_6__* avctx; scalar_t__* dest; scalar_t__** dc_val; TYPE_5__ current_picture; int /*<<< orphan*/  gb; int /*<<< orphan*/  first_slice_line; int /*<<< orphan*/  ac_pred; int /*<<< orphan*/ * c_dc_scale_table; int /*<<< orphan*/  c_dc_scale; int /*<<< orphan*/ * y_dc_scale_table; int /*<<< orphan*/  y_dc_scale; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* vc1_inv_trans_8x8 ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_27__ {int ttfrm; int pq; int* is_intra; size_t blocks_off; int mb_off; int a_avail; int c_avail; int** mb_type; size_t cur_blk_idx; int fourmvbp; size_t tt_index; int* cbp; int* ttblk; scalar_t__ overlap; int /*<<< orphan*/  ttmbf; int /*<<< orphan*/ ** block; TYPE_4__* cbpcy_vlc; TYPE_8__ s; int /*<<< orphan*/  range_y; int /*<<< orphan*/  range_x; TYPE_3__* fourmvbp_vlc; TYPE_2__ vc1dsp; int /*<<< orphan*/  codingset; int /*<<< orphan*/  codingset2; int /*<<< orphan*/ * acpred_plane; TYPE_1__* mbmode_vlc; } ;
typedef  TYPE_7__ VC1Context ;
struct TYPE_26__ {int flags; } ;
struct TYPE_24__ {int /*<<< orphan*/  table; } ;
struct TYPE_23__ {int /*<<< orphan*/  table; } ;
struct TYPE_21__ {int /*<<< orphan*/  table; } ;
struct TYPE_20__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_8__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 scalar_t__ CONFIG_GRAY ; 
 size_t FFABS (int) ; 
 int /*<<< orphan*/  GET_MQUANT () ; 
 int /*<<< orphan*/  MB_TYPE_16x16 ; 
 int /*<<< orphan*/  MB_TYPE_INTRA ; 
 int /*<<< orphan*/  VC1_4MV_BLOCK_PATTERN_VLC_BITS ; 
 int /*<<< orphan*/  VC1_CBPCY_P_VLC_BITS ; 
 int /*<<< orphan*/  VC1_ICBPCY_VLC_BITS ; 
 int /*<<< orphan*/  VC1_IF_MBMODE_VLC_BITS ; 
 int /*<<< orphan*/  VC1_TTMB_VLC_BITS ; 
 size_t* block_map ; 
 int /*<<< orphan*/  ff_vc1_mc_1mv (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_vc1_mc_4mv_chroma (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_vc1_mc_4mv_luma (TYPE_7__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_vc1_p_overlap_filter (TYPE_7__*) ; 
 int /*<<< orphan*/  ff_vc1_pred_mv (TYPE_7__*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 TYPE_14__* ff_vc1_ttmb_vlc ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mvdata_interlaced (TYPE_7__*,int*,int*,int*) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc1_decode_intra_block (TYPE_7__*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int vc1_decode_p_block (TYPE_7__*,int /*<<< orphan*/ ,int,int,int,int,scalar_t__,int,int,int*) ; 
 int /*<<< orphan*/  vc1_put_blocks_clamped (TYPE_7__*,int) ; 

__attribute__((used)) static int vc1_decode_p_mb_intfi(VC1Context *v)
{
    MpegEncContext *s = &v->s;
    GetBitContext *gb = &s->gb;
    int i;
    int mb_pos = s->mb_x + s->mb_y * s->mb_stride;
    int cbp = 0; /* cbp decoding stuff */
    int mqdiff, mquant; /* MB quantization */
    int ttmb = v->ttfrm; /* MB Transform type */

    int mb_has_coeffs = 1; /* last_flag */
    int dmv_x, dmv_y; /* Differential MV components */
    int val; /* temp values */
    int first_block = 1;
    int dst_idx, off;
    int pred_flag = 0;
    int block_cbp = 0, pat, block_tt = 0;
    int idx_mbmode = 0;

    mquant = v->pq; /* Lossy initialization */

    idx_mbmode = get_vlc2(gb, v->mbmode_vlc->table, VC1_IF_MBMODE_VLC_BITS, 2);
    if (idx_mbmode <= 1) { // intra MB
        v->is_intra[s->mb_x] = 0x3f; // Set the bitfield to all 1.
        s->mb_intra          = 1;
        s->current_picture.motion_val[1][s->block_index[0] + v->blocks_off][0] = 0;
        s->current_picture.motion_val[1][s->block_index[0] + v->blocks_off][1] = 0;
        s->current_picture.mb_type[mb_pos + v->mb_off] = MB_TYPE_INTRA;
        GET_MQUANT();
        s->current_picture.qscale_table[mb_pos] = mquant;
        /* Set DC scale - y and c use the same (not sure if necessary here) */
        s->y_dc_scale = s->y_dc_scale_table[FFABS(mquant)];
        s->c_dc_scale = s->c_dc_scale_table[FFABS(mquant)];
        v->s.ac_pred  = v->acpred_plane[mb_pos] = get_bits1(gb);
        mb_has_coeffs = idx_mbmode & 1;
        if (mb_has_coeffs)
            cbp = 1 + get_vlc2(&v->s.gb, v->cbpcy_vlc->table, VC1_ICBPCY_VLC_BITS, 2);
        dst_idx = 0;
        for (i = 0; i < 6; i++) {
            v->a_avail = v->c_avail          = 0;
            v->mb_type[0][s->block_index[i]] = 1;
            s->dc_val[0][s->block_index[i]]  = 0;
            dst_idx += i >> 2;
            val = ((cbp >> (5 - i)) & 1);
            if (i == 2 || i == 3 || !s->first_slice_line)
                v->a_avail = v->mb_type[0][s->block_index[i] - s->block_wrap[i]];
            if (i == 1 || i == 3 || s->mb_x)
                v->c_avail = v->mb_type[0][s->block_index[i] - 1];

            vc1_decode_intra_block(v, v->block[v->cur_blk_idx][block_map[i]], i, val, mquant,
                                   (i & 4) ? v->codingset2 : v->codingset);
            if (CONFIG_GRAY && (i > 3) && (s->avctx->flags & AV_CODEC_FLAG_GRAY))
                continue;
            v->vc1dsp.vc1_inv_trans_8x8(v->block[v->cur_blk_idx][block_map[i]]);
            off  = (i & 4) ? 0 : ((i & 1) * 8 + (i & 2) * 4 * s->linesize);
            block_cbp |= 0xf << (i << 2);
        }
    } else {
        s->mb_intra = v->is_intra[s->mb_x] = 0;
        s->current_picture.mb_type[mb_pos + v->mb_off] = MB_TYPE_16x16;
        for (i = 0; i < 6; i++)
            v->mb_type[0][s->block_index[i]] = 0;
        if (idx_mbmode <= 5) { // 1-MV
            dmv_x = dmv_y = pred_flag = 0;
            if (idx_mbmode & 1) {
                get_mvdata_interlaced(v, &dmv_x, &dmv_y, &pred_flag);
            }
            ff_vc1_pred_mv(v, 0, dmv_x, dmv_y, 1, v->range_x, v->range_y, v->mb_type[0], pred_flag, 0);
            ff_vc1_mc_1mv(v, 0);
            mb_has_coeffs = !(idx_mbmode & 2);
        } else { // 4-MV
            v->fourmvbp = get_vlc2(gb, v->fourmvbp_vlc->table, VC1_4MV_BLOCK_PATTERN_VLC_BITS, 1);
            for (i = 0; i < 4; i++) {
                dmv_x = dmv_y = pred_flag = 0;
                if (v->fourmvbp & (8 >> i))
                    get_mvdata_interlaced(v, &dmv_x, &dmv_y, &pred_flag);
                ff_vc1_pred_mv(v, i, dmv_x, dmv_y, 0, v->range_x, v->range_y, v->mb_type[0], pred_flag, 0);
                ff_vc1_mc_4mv_luma(v, i, 0, 0);
            }
            ff_vc1_mc_4mv_chroma(v, 0);
            mb_has_coeffs = idx_mbmode & 1;
        }
        if (mb_has_coeffs)
            cbp = 1 + get_vlc2(&v->s.gb, v->cbpcy_vlc->table, VC1_CBPCY_P_VLC_BITS, 2);
        if (cbp) {
            GET_MQUANT();
        }
        s->current_picture.qscale_table[mb_pos] = mquant;
        if (!v->ttmbf && cbp) {
            ttmb = get_vlc2(gb, ff_vc1_ttmb_vlc[v->tt_index].table, VC1_TTMB_VLC_BITS, 2);
        }
        dst_idx = 0;
        for (i = 0; i < 6; i++) {
            s->dc_val[0][s->block_index[i]] = 0;
            dst_idx += i >> 2;
            val = ((cbp >> (5 - i)) & 1);
            off = (i & 4) ? 0 : (i & 1) * 8 + (i & 2) * 4 * s->linesize;
            if (val) {
                pat = vc1_decode_p_block(v, v->block[v->cur_blk_idx][block_map[i]], i, mquant, ttmb,
                                         first_block, s->dest[dst_idx] + off,
                                         (i & 4) ? s->uvlinesize : s->linesize,
                                         CONFIG_GRAY && (i & 4) && (s->avctx->flags & AV_CODEC_FLAG_GRAY),
                                         &block_tt);
                if (pat < 0)
                    return pat;
                block_cbp |= pat << (i << 2);
                if (!v->ttmbf && ttmb < 8)
                    ttmb = -1;
                first_block = 0;
            }
        }
    }
    if (v->overlap && v->pq >= 9)
        ff_vc1_p_overlap_filter(v);
    vc1_put_blocks_clamped(v, 1);

    v->cbp[s->mb_x]      = block_cbp;
    v->ttblk[s->mb_x]    = block_tt;

    return 0;
}