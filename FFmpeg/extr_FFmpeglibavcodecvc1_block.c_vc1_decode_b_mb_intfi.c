#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_19__ ;
typedef  struct TYPE_20__   TYPE_15__ ;

/* Type definitions */
struct TYPE_28__ {int* qscale_table; int /*<<< orphan*/ * mb_type; scalar_t__*** motion_val; } ;
struct TYPE_24__ {int /*<<< orphan*/  (* put_signed_pixels_clamped ) (int*,scalar_t__,int) ;} ;
struct TYPE_30__ {int mb_x; int mb_y; int mb_stride; int mb_intra; size_t* block_index; size_t* block_wrap; int** block; int linesize; int uvlinesize; TYPE_19__* avctx; scalar_t__* dest; scalar_t__** dc_val; TYPE_7__ current_picture; int /*<<< orphan*/  gb; TYPE_4__* next_picture_ptr; TYPE_3__ idsp; int /*<<< orphan*/  first_slice_line; void* ac_pred; int /*<<< orphan*/ * c_dc_scale_table; int /*<<< orphan*/  c_dc_scale; int /*<<< orphan*/ * y_dc_scale_table; int /*<<< orphan*/  y_dc_scale; } ;
struct TYPE_23__ {int /*<<< orphan*/  (* vc1_inv_trans_8x8 ) (int*) ;} ;
struct TYPE_29__ {int ttfrm; int pq; int* is_intra; int mb_off; int a_avail; int c_avail; int** mb_type; int* forward_mb_plane; int bmvtype; int fourmvbp; size_t tt_index; int* cbp; int* ttblk; int /*<<< orphan*/  ttmbf; TYPE_6__* cbpcy_vlc; TYPE_9__ s; TYPE_5__* fourmvbp_vlc; scalar_t__ fmb_is_raw; scalar_t__ rangeredfrm; TYPE_2__ vc1dsp; int /*<<< orphan*/  codingset; int /*<<< orphan*/  codingset2; void** acpred_plane; TYPE_1__* mbmode_vlc; } ;
typedef  TYPE_8__ VC1Context ;
struct TYPE_27__ {int /*<<< orphan*/  table; } ;
struct TYPE_26__ {int /*<<< orphan*/  table; } ;
struct TYPE_25__ {int /*<<< orphan*/  field_picture; } ;
struct TYPE_22__ {int /*<<< orphan*/  table; } ;
struct TYPE_21__ {int flags; } ;
struct TYPE_20__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_9__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int BMV_TYPE_BACKWARD ; 
 int BMV_TYPE_DIRECT ; 
 int BMV_TYPE_FORWARD ; 
 int BMV_TYPE_INTERPOLATED ; 
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
 int /*<<< orphan*/  av_log (TYPE_19__*,int /*<<< orphan*/ ,char*) ; 
 int decode012 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_vc1_mc_4mv_chroma (TYPE_8__*,int) ; 
 int /*<<< orphan*/  ff_vc1_mc_4mv_luma (TYPE_8__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_vc1_pred_b_mv_intfi (TYPE_8__*,int,int*,int*,int,int*) ; 
 TYPE_15__* ff_vc1_ttmb_vlc ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mvdata_interlaced (TYPE_8__*,int*,int*,int*) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int*) ; 
 int /*<<< orphan*/  stub2 (int*,scalar_t__,int) ; 
 int /*<<< orphan*/  vc1_b_mc (TYPE_8__*,int*,int*,int,int) ; 
 int /*<<< orphan*/  vc1_decode_intra_block (TYPE_8__*,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int vc1_decode_p_block (TYPE_8__*,int*,int,int,int,int,scalar_t__,int,int,int*) ; 

__attribute__((used)) static void vc1_decode_b_mb_intfi(VC1Context *v)
{
    MpegEncContext *s = &v->s;
    GetBitContext *gb = &s->gb;
    int i, j;
    int mb_pos = s->mb_x + s->mb_y * s->mb_stride;
    int cbp = 0; /* cbp decoding stuff */
    int mqdiff, mquant; /* MB quantization */
    int ttmb = v->ttfrm; /* MB Transform type */
    int mb_has_coeffs = 0; /* last_flag */
    int val; /* temp value */
    int first_block = 1;
    int dst_idx, off;
    int fwd;
    int dmv_x[2], dmv_y[2], pred_flag[2];
    int bmvtype = BMV_TYPE_BACKWARD;
    int block_cbp = 0, pat, block_tt = 0;
    int idx_mbmode;

    mquant      = v->pq; /* Lossy initialization */
    s->mb_intra = 0;

    idx_mbmode = get_vlc2(gb, v->mbmode_vlc->table, VC1_IF_MBMODE_VLC_BITS, 2);
    if (idx_mbmode <= 1) { // intra MB
        v->is_intra[s->mb_x] = 0x3f; // Set the bitfield to all 1.
        s->mb_intra          = 1;
        s->current_picture.motion_val[1][s->block_index[0]][0] = 0;
        s->current_picture.motion_val[1][s->block_index[0]][1] = 0;
        s->current_picture.mb_type[mb_pos + v->mb_off]         = MB_TYPE_INTRA;
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

            vc1_decode_intra_block(v, s->block[i], i, val, mquant,
                                   (i & 4) ? v->codingset2 : v->codingset);
            if (CONFIG_GRAY && (i > 3) && (s->avctx->flags & AV_CODEC_FLAG_GRAY))
                continue;
            v->vc1dsp.vc1_inv_trans_8x8(s->block[i]);
            if (v->rangeredfrm)
                for (j = 0; j < 64; j++)
                    s->block[i][j] <<= 1;
            off  = (i & 4) ? 0 : ((i & 1) * 8 + (i & 2) * 4 * s->linesize);
            s->idsp.put_signed_pixels_clamped(s->block[i],
                                              s->dest[dst_idx] + off,
                                              (i & 4) ? s->uvlinesize
                                                      : s->linesize);
        }
    } else {
        s->mb_intra = v->is_intra[s->mb_x] = 0;
        s->current_picture.mb_type[mb_pos + v->mb_off] = MB_TYPE_16x16;
        for (i = 0; i < 6; i++)
            v->mb_type[0][s->block_index[i]] = 0;
        if (v->fmb_is_raw)
            fwd = v->forward_mb_plane[mb_pos] = get_bits1(gb);
        else
            fwd = v->forward_mb_plane[mb_pos];
        if (idx_mbmode <= 5) { // 1-MV
            int interpmvp = 0;
            dmv_x[0]     = dmv_x[1] = dmv_y[0] = dmv_y[1] = 0;
            pred_flag[0] = pred_flag[1] = 0;
            if (fwd)
                bmvtype = BMV_TYPE_FORWARD;
            else {
                bmvtype = decode012(gb);
                switch (bmvtype) {
                case 0:
                    bmvtype = BMV_TYPE_BACKWARD;
                    break;
                case 1:
                    bmvtype = BMV_TYPE_DIRECT;
                    break;
                case 2:
                    bmvtype   = BMV_TYPE_INTERPOLATED;
                    interpmvp = get_bits1(gb);
                }
            }
            v->bmvtype = bmvtype;
            if (bmvtype != BMV_TYPE_DIRECT && idx_mbmode & 1) {
                get_mvdata_interlaced(v, &dmv_x[bmvtype == BMV_TYPE_BACKWARD], &dmv_y[bmvtype == BMV_TYPE_BACKWARD], &pred_flag[bmvtype == BMV_TYPE_BACKWARD]);
            }
            if (interpmvp) {
                get_mvdata_interlaced(v, &dmv_x[1], &dmv_y[1], &pred_flag[1]);
            }
            if (bmvtype == BMV_TYPE_DIRECT) {
                dmv_x[0] = dmv_y[0] = pred_flag[0] = 0;
                dmv_x[1] = dmv_y[1] = pred_flag[0] = 0;
                if (!s->next_picture_ptr->field_picture) {
                    av_log(s->avctx, AV_LOG_ERROR, "Mixed field/frame direct mode not supported\n");
                    return;
                }
            }
            ff_vc1_pred_b_mv_intfi(v, 0, dmv_x, dmv_y, 1, pred_flag);
            vc1_b_mc(v, dmv_x, dmv_y, (bmvtype == BMV_TYPE_DIRECT), bmvtype);
            mb_has_coeffs = !(idx_mbmode & 2);
        } else { // 4-MV
            if (fwd)
                bmvtype = BMV_TYPE_FORWARD;
            v->bmvtype  = bmvtype;
            v->fourmvbp = get_vlc2(gb, v->fourmvbp_vlc->table, VC1_4MV_BLOCK_PATTERN_VLC_BITS, 1);
            for (i = 0; i < 4; i++) {
                dmv_x[0] = dmv_y[0] = pred_flag[0] = 0;
                dmv_x[1] = dmv_y[1] = pred_flag[1] = 0;
                if (v->fourmvbp & (8 >> i)) {
                    get_mvdata_interlaced(v, &dmv_x[bmvtype == BMV_TYPE_BACKWARD],
                                             &dmv_y[bmvtype == BMV_TYPE_BACKWARD],
                                         &pred_flag[bmvtype == BMV_TYPE_BACKWARD]);
                }
                ff_vc1_pred_b_mv_intfi(v, i, dmv_x, dmv_y, 0, pred_flag);
                ff_vc1_mc_4mv_luma(v, i, bmvtype == BMV_TYPE_BACKWARD, 0);
            }
            ff_vc1_mc_4mv_chroma(v, bmvtype == BMV_TYPE_BACKWARD);
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
                pat = vc1_decode_p_block(v, s->block[i], i, mquant, ttmb,
                                         first_block, s->dest[dst_idx] + off,
                                         (i & 4) ? s->uvlinesize : s->linesize,
                                         CONFIG_GRAY && (i & 4) && (s->avctx->flags & AV_CODEC_FLAG_GRAY), &block_tt);
                block_cbp |= pat << (i << 2);
                if (!v->ttmbf && ttmb < 8)
                    ttmb = -1;
                first_block = 0;
            }
        }
    }
    v->cbp[s->mb_x]      = block_cbp;
    v->ttblk[s->mb_x]    = block_tt;
}