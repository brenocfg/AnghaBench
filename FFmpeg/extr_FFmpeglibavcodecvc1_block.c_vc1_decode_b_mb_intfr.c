#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_22__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_16__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct TYPE_35__ {int* qscale_table; void**** motion_val; int /*<<< orphan*/ * mb_type; } ;
struct TYPE_31__ {int /*<<< orphan*/ *** motion_val; } ;
struct TYPE_29__ {int /*<<< orphan*/  (* put_signed_pixels_clamped ) (int /*<<< orphan*/ ,scalar_t__,int) ;} ;
struct TYPE_24__ {int mb_x; int mb_y; int mb_stride; int mb_intra; int* mbskip_table; size_t* block_index; size_t* block_wrap; int linesize; int uvlinesize; TYPE_9__ current_picture; void**** mv; scalar_t__** dc_val; TYPE_22__* avctx; scalar_t__* dest; int /*<<< orphan*/ * block; int /*<<< orphan*/  gb; int /*<<< orphan*/  quarter_sample; TYPE_5__ next_picture; TYPE_4__* next_picture_ptr; TYPE_3__ idsp; int /*<<< orphan*/  first_slice_line; int /*<<< orphan*/ * c_dc_scale_table; int /*<<< orphan*/  c_dc_scale; int /*<<< orphan*/ * y_dc_scale_table; int /*<<< orphan*/  y_dc_scale; void* ac_pred; } ;
struct TYPE_28__ {int /*<<< orphan*/  (* vc1_inv_trans_8x8 ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_23__ {int ttfrm; int pq; int* blk_mv_type; int* is_intra; int* fieldtx_plane; int a_avail; int c_avail; int** mb_type; int* direct_mb_plane; int bfraction; int fourmvbp; int twomvbp; size_t tt_index; int* cbp; int* ttblk; int /*<<< orphan*/  range_y; int /*<<< orphan*/  range_x; int /*<<< orphan*/  ttmbf; TYPE_8__* twomvbp_vlc; TYPE_7__* fourmvbp_vlc; TYPE_6__* cbpcy_vlc; TYPE_11__ s; scalar_t__ dmb_is_raw; TYPE_2__ vc1dsp; int /*<<< orphan*/  codingset; int /*<<< orphan*/  codingset2; void** acpred_plane; TYPE_1__* mbmode_vlc; scalar_t__ skip_is_raw; } ;
typedef  TYPE_10__ VC1Context ;
struct TYPE_34__ {int /*<<< orphan*/  table; } ;
struct TYPE_33__ {int /*<<< orphan*/  table; } ;
struct TYPE_32__ {int /*<<< orphan*/  table; } ;
struct TYPE_30__ {scalar_t__ field_picture; } ;
struct TYPE_27__ {int flags; } ;
struct TYPE_26__ {int /*<<< orphan*/  table; } ;
struct TYPE_25__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_11__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int BMV_TYPE_BACKWARD ; 
 int BMV_TYPE_FORWARD ; 
 int BMV_TYPE_INTERPOLATED ; 
 int B_FRACTION_DEN ; 
 scalar_t__ CONFIG_GRAY ; 
 size_t FFABS (int) ; 
 int /*<<< orphan*/  GET_MQUANT () ; 
 int /*<<< orphan*/  MB_TYPE_INTRA ; 
 int /*<<< orphan*/  MB_TYPE_SKIP ; 
 void* MV_PMODE_INTFR_2MV_FIELD ; 
 void* MV_PMODE_INTFR_INTRA ; 
 int /*<<< orphan*/  VC1_2MV_BLOCK_PATTERN_VLC_BITS ; 
 int /*<<< orphan*/  VC1_4MV_BLOCK_PATTERN_VLC_BITS ; 
 int /*<<< orphan*/  VC1_CBPCY_P_VLC_BITS ; 
 int /*<<< orphan*/  VC1_INTFR_NON4MV_MBMODE_VLC_BITS ; 
 int /*<<< orphan*/  VC1_TTMB_VLC_BITS ; 
 int /*<<< orphan*/  av_log (TYPE_22__*,int /*<<< orphan*/ ,char*) ; 
 int decode012 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_vc1_interp_mc (TYPE_10__*) ; 
 void**** ff_vc1_mbmode_intfrp ; 
 int /*<<< orphan*/  ff_vc1_mc_1mv (TYPE_10__*,int) ; 
 int /*<<< orphan*/  ff_vc1_mc_4mv_chroma4 (TYPE_10__*,int,int,int) ; 
 int /*<<< orphan*/  ff_vc1_mc_4mv_luma (TYPE_10__*,int,int,int) ; 
 int /*<<< orphan*/  ff_vc1_pred_mv_intfr (TYPE_10__*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 TYPE_16__* ff_vc1_ttmb_vlc ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mvdata_interlaced (TYPE_10__*,int*,int*,int /*<<< orphan*/ ) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* scale_mv (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  vc1_decode_intra_block (TYPE_10__*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int vc1_decode_p_block (TYPE_10__*,int /*<<< orphan*/ ,int,int,int,int,scalar_t__,int,int,int*) ; 

__attribute__((used)) static int vc1_decode_b_mb_intfr(VC1Context *v)
{
    MpegEncContext *s = &v->s;
    GetBitContext *gb = &s->gb;
    int i, j;
    int mb_pos = s->mb_x + s->mb_y * s->mb_stride;
    int cbp = 0; /* cbp decoding stuff */
    int mqdiff, mquant; /* MB quantization */
    int ttmb = v->ttfrm; /* MB Transform type */
    int mvsw = 0; /* motion vector switch */
    int mb_has_coeffs = 1; /* last_flag */
    int dmv_x, dmv_y; /* Differential MV components */
    int val; /* temp value */
    int first_block = 1;
    int dst_idx, off;
    int skipped, direct, twomv = 0;
    int block_cbp = 0, pat, block_tt = 0;
    int idx_mbmode = 0, mvbp;
    int stride_y, fieldtx;
    int bmvtype = BMV_TYPE_BACKWARD;
    int dir, dir2;

    mquant = v->pq; /* Lossy initialization */
    s->mb_intra = 0;
    if (v->skip_is_raw)
        skipped = get_bits1(gb);
    else
        skipped = v->s.mbskip_table[mb_pos];

    if (!skipped) {
        idx_mbmode = get_vlc2(gb, v->mbmode_vlc->table, VC1_INTFR_NON4MV_MBMODE_VLC_BITS, 2);
        if (ff_vc1_mbmode_intfrp[0][idx_mbmode][0] == MV_PMODE_INTFR_2MV_FIELD) {
            twomv = 1;
            v->blk_mv_type[s->block_index[0]] = 1;
            v->blk_mv_type[s->block_index[1]] = 1;
            v->blk_mv_type[s->block_index[2]] = 1;
            v->blk_mv_type[s->block_index[3]] = 1;
        } else {
            v->blk_mv_type[s->block_index[0]] = 0;
            v->blk_mv_type[s->block_index[1]] = 0;
            v->blk_mv_type[s->block_index[2]] = 0;
            v->blk_mv_type[s->block_index[3]] = 0;
        }
    }

    if (ff_vc1_mbmode_intfrp[0][idx_mbmode][0] == MV_PMODE_INTFR_INTRA) { // intra MB
        for (i = 0; i < 4; i++) {
            s->mv[0][i][0] = s->current_picture.motion_val[0][s->block_index[i]][0] = 0;
            s->mv[0][i][1] = s->current_picture.motion_val[0][s->block_index[i]][1] = 0;
            s->mv[1][i][0] = s->current_picture.motion_val[1][s->block_index[i]][0] = 0;
            s->mv[1][i][1] = s->current_picture.motion_val[1][s->block_index[i]][1] = 0;
        }
        v->is_intra[s->mb_x] = 0x3f; // Set the bitfield to all 1.
        s->mb_intra          = 1;
        s->current_picture.mb_type[mb_pos] = MB_TYPE_INTRA;
        fieldtx = v->fieldtx_plane[mb_pos] = get_bits1(gb);
        mb_has_coeffs = get_bits1(gb);
        if (mb_has_coeffs)
            cbp = 1 + get_vlc2(&v->s.gb, v->cbpcy_vlc->table, VC1_CBPCY_P_VLC_BITS, 2);
        v->s.ac_pred = v->acpred_plane[mb_pos] = get_bits1(gb);
        GET_MQUANT();
        s->current_picture.qscale_table[mb_pos] = mquant;
        /* Set DC scale - y and c use the same (not sure if necessary here) */
        s->y_dc_scale = s->y_dc_scale_table[FFABS(mquant)];
        s->c_dc_scale = s->c_dc_scale_table[FFABS(mquant)];
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
            if (CONFIG_GRAY && i > 3 && (s->avctx->flags & AV_CODEC_FLAG_GRAY))
                continue;
            v->vc1dsp.vc1_inv_trans_8x8(s->block[i]);
            if (i < 4) {
                stride_y = s->linesize << fieldtx;
                off = (fieldtx) ? ((i & 1) * 8) + ((i & 2) >> 1) * s->linesize : (i & 1) * 8 + 4 * (i & 2) * s->linesize;
            } else {
                stride_y = s->uvlinesize;
                off = 0;
            }
            s->idsp.put_signed_pixels_clamped(s->block[i],
                                              s->dest[dst_idx] + off,
                                              stride_y);
        }
    } else {
        s->mb_intra = v->is_intra[s->mb_x] = 0;

        if (v->dmb_is_raw)
            direct = get_bits1(gb);
        else
            direct = v->direct_mb_plane[mb_pos];

        if (direct) {
            if (s->next_picture_ptr->field_picture)
                av_log(s->avctx, AV_LOG_WARNING, "Mixed frame/field direct mode not supported\n");
            s->mv[0][0][0] = s->current_picture.motion_val[0][s->block_index[0]][0] = scale_mv(s->next_picture.motion_val[1][s->block_index[0]][0], v->bfraction, 0, s->quarter_sample);
            s->mv[0][0][1] = s->current_picture.motion_val[0][s->block_index[0]][1] = scale_mv(s->next_picture.motion_val[1][s->block_index[0]][1], v->bfraction, 0, s->quarter_sample);
            s->mv[1][0][0] = s->current_picture.motion_val[1][s->block_index[0]][0] = scale_mv(s->next_picture.motion_val[1][s->block_index[0]][0], v->bfraction, 1, s->quarter_sample);
            s->mv[1][0][1] = s->current_picture.motion_val[1][s->block_index[0]][1] = scale_mv(s->next_picture.motion_val[1][s->block_index[0]][1], v->bfraction, 1, s->quarter_sample);

            if (twomv) {
                s->mv[0][2][0] = s->current_picture.motion_val[0][s->block_index[2]][0] = scale_mv(s->next_picture.motion_val[1][s->block_index[2]][0], v->bfraction, 0, s->quarter_sample);
                s->mv[0][2][1] = s->current_picture.motion_val[0][s->block_index[2]][1] = scale_mv(s->next_picture.motion_val[1][s->block_index[2]][1], v->bfraction, 0, s->quarter_sample);
                s->mv[1][2][0] = s->current_picture.motion_val[1][s->block_index[2]][0] = scale_mv(s->next_picture.motion_val[1][s->block_index[2]][0], v->bfraction, 1, s->quarter_sample);
                s->mv[1][2][1] = s->current_picture.motion_val[1][s->block_index[2]][1] = scale_mv(s->next_picture.motion_val[1][s->block_index[2]][1], v->bfraction, 1, s->quarter_sample);

                for (i = 1; i < 4; i += 2) {
                    s->mv[0][i][0] = s->current_picture.motion_val[0][s->block_index[i]][0] = s->mv[0][i-1][0];
                    s->mv[0][i][1] = s->current_picture.motion_val[0][s->block_index[i]][1] = s->mv[0][i-1][1];
                    s->mv[1][i][0] = s->current_picture.motion_val[1][s->block_index[i]][0] = s->mv[1][i-1][0];
                    s->mv[1][i][1] = s->current_picture.motion_val[1][s->block_index[i]][1] = s->mv[1][i-1][1];
                }
            } else {
                for (i = 1; i < 4; i++) {
                    s->mv[0][i][0] = s->current_picture.motion_val[0][s->block_index[i]][0] = s->mv[0][0][0];
                    s->mv[0][i][1] = s->current_picture.motion_val[0][s->block_index[i]][1] = s->mv[0][0][1];
                    s->mv[1][i][0] = s->current_picture.motion_val[1][s->block_index[i]][0] = s->mv[1][0][0];
                    s->mv[1][i][1] = s->current_picture.motion_val[1][s->block_index[i]][1] = s->mv[1][0][1];
                }
            }
        }

        if (!direct) {
            if (skipped || !s->mb_intra) {
                bmvtype = decode012(gb);
                switch (bmvtype) {
                case 0:
                    bmvtype = (v->bfraction >= (B_FRACTION_DEN/2)) ? BMV_TYPE_BACKWARD : BMV_TYPE_FORWARD;
                    break;
                case 1:
                    bmvtype = (v->bfraction >= (B_FRACTION_DEN/2)) ? BMV_TYPE_FORWARD : BMV_TYPE_BACKWARD;
                    break;
                case 2:
                    bmvtype  = BMV_TYPE_INTERPOLATED;
                }
            }

            if (twomv && bmvtype != BMV_TYPE_INTERPOLATED)
                mvsw = get_bits1(gb);
        }

        if (!skipped) { // inter MB
            mb_has_coeffs = ff_vc1_mbmode_intfrp[0][idx_mbmode][3];
            if (mb_has_coeffs)
                cbp = 1 + get_vlc2(&v->s.gb, v->cbpcy_vlc->table, VC1_CBPCY_P_VLC_BITS, 2);
            if (!direct) {
                if (bmvtype == BMV_TYPE_INTERPOLATED && twomv) {
                    v->fourmvbp = get_vlc2(gb, v->fourmvbp_vlc->table, VC1_4MV_BLOCK_PATTERN_VLC_BITS, 1);
                } else if (bmvtype == BMV_TYPE_INTERPOLATED || twomv) {
                    v->twomvbp = get_vlc2(gb, v->twomvbp_vlc->table, VC1_2MV_BLOCK_PATTERN_VLC_BITS, 1);
                }
            }

            for (i = 0; i < 6; i++)
                v->mb_type[0][s->block_index[i]] = 0;
            fieldtx = v->fieldtx_plane[mb_pos] = ff_vc1_mbmode_intfrp[0][idx_mbmode][1];
            /* for all motion vector read MVDATA and motion compensate each block */
            dst_idx = 0;
            if (direct) {
                if (twomv) {
                    for (i = 0; i < 4; i++) {
                        ff_vc1_mc_4mv_luma(v, i, 0, 0);
                        ff_vc1_mc_4mv_luma(v, i, 1, 1);
                    }
                    ff_vc1_mc_4mv_chroma4(v, 0, 0, 0);
                    ff_vc1_mc_4mv_chroma4(v, 1, 1, 1);
                } else {
                    ff_vc1_mc_1mv(v, 0);
                    ff_vc1_interp_mc(v);
                }
            } else if (twomv && bmvtype == BMV_TYPE_INTERPOLATED) {
                mvbp = v->fourmvbp;
                for (i = 0; i < 4; i++) {
                    dir = i==1 || i==3;
                    dmv_x = dmv_y = 0;
                    val = ((mvbp >> (3 - i)) & 1);
                    if (val)
                        get_mvdata_interlaced(v, &dmv_x, &dmv_y, 0);
                    j = i > 1 ? 2 : 0;
                    ff_vc1_pred_mv_intfr(v, j, dmv_x, dmv_y, 2, v->range_x, v->range_y, v->mb_type[0], dir);
                    ff_vc1_mc_4mv_luma(v, j, dir, dir);
                    ff_vc1_mc_4mv_luma(v, j+1, dir, dir);
                }

                ff_vc1_mc_4mv_chroma4(v, 0, 0, 0);
                ff_vc1_mc_4mv_chroma4(v, 1, 1, 1);
            } else if (bmvtype == BMV_TYPE_INTERPOLATED) {
                mvbp = v->twomvbp;
                dmv_x = dmv_y = 0;
                if (mvbp & 2)
                    get_mvdata_interlaced(v, &dmv_x, &dmv_y, 0);

                ff_vc1_pred_mv_intfr(v, 0, dmv_x, dmv_y, 1, v->range_x, v->range_y, v->mb_type[0], 0);
                ff_vc1_mc_1mv(v, 0);

                dmv_x = dmv_y = 0;
                if (mvbp & 1)
                    get_mvdata_interlaced(v, &dmv_x, &dmv_y, 0);

                ff_vc1_pred_mv_intfr(v, 0, dmv_x, dmv_y, 1, v->range_x, v->range_y, v->mb_type[0], 1);
                ff_vc1_interp_mc(v);
            } else if (twomv) {
                dir = bmvtype == BMV_TYPE_BACKWARD;
                dir2 = dir;
                if (mvsw)
                    dir2 = !dir;
                mvbp = v->twomvbp;
                dmv_x = dmv_y = 0;
                if (mvbp & 2)
                    get_mvdata_interlaced(v, &dmv_x, &dmv_y, 0);
                ff_vc1_pred_mv_intfr(v, 0, dmv_x, dmv_y, 2, v->range_x, v->range_y, v->mb_type[0], dir);

                dmv_x = dmv_y = 0;
                if (mvbp & 1)
                    get_mvdata_interlaced(v, &dmv_x, &dmv_y, 0);
                ff_vc1_pred_mv_intfr(v, 2, dmv_x, dmv_y, 2, v->range_x, v->range_y, v->mb_type[0], dir2);

                if (mvsw) {
                    for (i = 0; i < 2; i++) {
                        s->mv[dir][i+2][0] = s->mv[dir][i][0] = s->current_picture.motion_val[dir][s->block_index[i+2]][0] = s->current_picture.motion_val[dir][s->block_index[i]][0];
                        s->mv[dir][i+2][1] = s->mv[dir][i][1] = s->current_picture.motion_val[dir][s->block_index[i+2]][1] = s->current_picture.motion_val[dir][s->block_index[i]][1];
                        s->mv[dir2][i+2][0] = s->mv[dir2][i][0] = s->current_picture.motion_val[dir2][s->block_index[i]][0] = s->current_picture.motion_val[dir2][s->block_index[i+2]][0];
                        s->mv[dir2][i+2][1] = s->mv[dir2][i][1] = s->current_picture.motion_val[dir2][s->block_index[i]][1] = s->current_picture.motion_val[dir2][s->block_index[i+2]][1];
                    }
                } else {
                    ff_vc1_pred_mv_intfr(v, 0, 0, 0, 2, v->range_x, v->range_y, v->mb_type[0], !dir);
                    ff_vc1_pred_mv_intfr(v, 2, 0, 0, 2, v->range_x, v->range_y, v->mb_type[0], !dir);
                }

                ff_vc1_mc_4mv_luma(v, 0, dir, 0);
                ff_vc1_mc_4mv_luma(v, 1, dir, 0);
                ff_vc1_mc_4mv_luma(v, 2, dir2, 0);
                ff_vc1_mc_4mv_luma(v, 3, dir2, 0);
                ff_vc1_mc_4mv_chroma4(v, dir, dir2, 0);
            } else {
                dir = bmvtype == BMV_TYPE_BACKWARD;

                mvbp = ff_vc1_mbmode_intfrp[0][idx_mbmode][2];
                dmv_x = dmv_y = 0;
                if (mvbp)
                    get_mvdata_interlaced(v, &dmv_x, &dmv_y, 0);

                ff_vc1_pred_mv_intfr(v, 0, dmv_x, dmv_y, 1, v->range_x, v->range_y, v->mb_type[0], dir);
                v->blk_mv_type[s->block_index[0]] = 1;
                v->blk_mv_type[s->block_index[1]] = 1;
                v->blk_mv_type[s->block_index[2]] = 1;
                v->blk_mv_type[s->block_index[3]] = 1;
                ff_vc1_pred_mv_intfr(v, 0, 0, 0, 2, v->range_x, v->range_y, 0, !dir);
                for (i = 0; i < 2; i++) {
                    s->mv[!dir][i+2][0] = s->mv[!dir][i][0] = s->current_picture.motion_val[!dir][s->block_index[i+2]][0] = s->current_picture.motion_val[!dir][s->block_index[i]][0];
                    s->mv[!dir][i+2][1] = s->mv[!dir][i][1] = s->current_picture.motion_val[!dir][s->block_index[i+2]][1] = s->current_picture.motion_val[!dir][s->block_index[i]][1];
                }
                ff_vc1_mc_1mv(v, dir);
            }

            if (cbp)
                GET_MQUANT();  // p. 227
            s->current_picture.qscale_table[mb_pos] = mquant;
            if (!v->ttmbf && cbp)
                ttmb = get_vlc2(gb, ff_vc1_ttmb_vlc[v->tt_index].table, VC1_TTMB_VLC_BITS, 2);
            for (i = 0; i < 6; i++) {
                s->dc_val[0][s->block_index[i]] = 0;
                dst_idx += i >> 2;
                val = ((cbp >> (5 - i)) & 1);
                if (!fieldtx)
                    off = (i & 4) ? 0 : ((i & 1) * 8 + (i & 2) * 4 * s->linesize);
                else
                    off = (i & 4) ? 0 : ((i & 1) * 8 + ((i > 1) * s->linesize));
                if (val) {
                    pat = vc1_decode_p_block(v, s->block[i], i, mquant, ttmb,
                                             first_block, s->dest[dst_idx] + off,
                                             (i & 4) ? s->uvlinesize : (s->linesize << fieldtx),
                                             CONFIG_GRAY && (i & 4) && (s->avctx->flags & AV_CODEC_FLAG_GRAY), &block_tt);
                    block_cbp |= pat << (i << 2);
                    if (!v->ttmbf && ttmb < 8)
                        ttmb = -1;
                    first_block = 0;
                }
            }

        } else { // skipped
            dir = 0;
            for (i = 0; i < 6; i++) {
                v->mb_type[0][s->block_index[i]] = 0;
                s->dc_val[0][s->block_index[i]] = 0;
            }
            s->current_picture.mb_type[mb_pos]      = MB_TYPE_SKIP;
            s->current_picture.qscale_table[mb_pos] = 0;
            v->blk_mv_type[s->block_index[0]] = 0;
            v->blk_mv_type[s->block_index[1]] = 0;
            v->blk_mv_type[s->block_index[2]] = 0;
            v->blk_mv_type[s->block_index[3]] = 0;

            if (!direct) {
                if (bmvtype == BMV_TYPE_INTERPOLATED) {
                    ff_vc1_pred_mv_intfr(v, 0, 0, 0, 1, v->range_x, v->range_y, v->mb_type[0], 0);
                    ff_vc1_pred_mv_intfr(v, 0, 0, 0, 1, v->range_x, v->range_y, v->mb_type[0], 1);
                } else {
                    dir = bmvtype == BMV_TYPE_BACKWARD;
                    ff_vc1_pred_mv_intfr(v, 0, 0, 0, 1, v->range_x, v->range_y, v->mb_type[0], dir);
                    if (mvsw) {
                        int dir2 = dir;
                        if (mvsw)
                            dir2 = !dir;
                        for (i = 0; i < 2; i++) {
                            s->mv[dir][i+2][0] = s->mv[dir][i][0] = s->current_picture.motion_val[dir][s->block_index[i+2]][0] = s->current_picture.motion_val[dir][s->block_index[i]][0];
                            s->mv[dir][i+2][1] = s->mv[dir][i][1] = s->current_picture.motion_val[dir][s->block_index[i+2]][1] = s->current_picture.motion_val[dir][s->block_index[i]][1];
                            s->mv[dir2][i+2][0] = s->mv[dir2][i][0] = s->current_picture.motion_val[dir2][s->block_index[i]][0] = s->current_picture.motion_val[dir2][s->block_index[i+2]][0];
                            s->mv[dir2][i+2][1] = s->mv[dir2][i][1] = s->current_picture.motion_val[dir2][s->block_index[i]][1] = s->current_picture.motion_val[dir2][s->block_index[i+2]][1];
                        }
                    } else {
                        v->blk_mv_type[s->block_index[0]] = 1;
                        v->blk_mv_type[s->block_index[1]] = 1;
                        v->blk_mv_type[s->block_index[2]] = 1;
                        v->blk_mv_type[s->block_index[3]] = 1;
                        ff_vc1_pred_mv_intfr(v, 0, 0, 0, 2, v->range_x, v->range_y, 0, !dir);
                        for (i = 0; i < 2; i++) {
                            s->mv[!dir][i+2][0] = s->mv[!dir][i][0] = s->current_picture.motion_val[!dir][s->block_index[i+2]][0] = s->current_picture.motion_val[!dir][s->block_index[i]][0];
                            s->mv[!dir][i+2][1] = s->mv[!dir][i][1] = s->current_picture.motion_val[!dir][s->block_index[i+2]][1] = s->current_picture.motion_val[!dir][s->block_index[i]][1];
                        }
                    }
                }
            }

            ff_vc1_mc_1mv(v, dir);
            if (direct || bmvtype == BMV_TYPE_INTERPOLATED) {
                ff_vc1_interp_mc(v);
            }
            v->fieldtx_plane[mb_pos] = 0;
        }
    }
    v->cbp[s->mb_x]      = block_cbp;
    v->ttblk[s->mb_x]    = block_tt;

    return 0;
}