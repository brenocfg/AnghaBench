#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  (* vc1_inv_trans_8x8 ) (int*) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  (* put_signed_pixels_clamped ) (int*,scalar_t__,int) ;} ;
struct TYPE_16__ {int* qscale_table; } ;
struct TYPE_21__ {int mb_x; int mb_y; int mb_stride; int* mbskip_table; size_t* block_index; int linesize; size_t* block_wrap; int** block; int uvlinesize; TYPE_5__* avctx; scalar_t__* dest; TYPE_4__ idsp; int /*<<< orphan*/  first_slice_line; scalar_t__ mb_intra; scalar_t__** dc_val; TYPE_2__ current_picture; int /*<<< orphan*/  gb; void* ac_pred; } ;
struct TYPE_20__ {int ttfrm; int pq; int* direct_mb_plane; int bfraction; size_t tt_index; int /*<<< orphan*/  ttmbf; scalar_t__ rangeredfrm; TYPE_3__ vc1dsp; int /*<<< orphan*/  codingset; int /*<<< orphan*/  codingset2; scalar_t__** mb_type; scalar_t__ c_avail; scalar_t__ a_avail; TYPE_1__* cbpcy_vlc; TYPE_7__ s; scalar_t__ skip_is_raw; scalar_t__ dmb_is_raw; } ;
typedef  TYPE_6__ VC1Context ;
struct TYPE_19__ {int flags; } ;
struct TYPE_15__ {int /*<<< orphan*/  table; } ;
struct TYPE_14__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_7__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int BMV_TYPE_BACKWARD ; 
 int BMV_TYPE_FORWARD ; 
 int BMV_TYPE_INTERPOLATED ; 
 int B_FRACTION_DEN ; 
 scalar_t__ CONFIG_GRAY ; 
 int /*<<< orphan*/  GET_MQUANT () ; 
 int /*<<< orphan*/  GET_MVDATA (int,int) ; 
 int /*<<< orphan*/  VC1_CBPCY_P_VLC_BITS ; 
 int /*<<< orphan*/  VC1_TTMB_VLC_BITS ; 
 int decode012 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_vc1_pred_b_mv (TYPE_6__*,int*,int*,int,int) ; 
 TYPE_12__* ff_vc1_ttmb_vlc ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int*) ; 
 int /*<<< orphan*/  stub2 (int*,scalar_t__,int) ; 
 int /*<<< orphan*/  vc1_b_mc (TYPE_6__*,int*,int*,int,int) ; 
 int /*<<< orphan*/  vc1_decode_intra_block (TYPE_6__*,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int vc1_decode_p_block (TYPE_6__*,int*,int,int,int,int,scalar_t__,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vc1_decode_b_mb(VC1Context *v)
{
    MpegEncContext *s = &v->s;
    GetBitContext *gb = &s->gb;
    int i, j;
    int mb_pos = s->mb_x + s->mb_y * s->mb_stride;
    int cbp = 0; /* cbp decoding stuff */
    int mqdiff, mquant; /* MB quantization */
    int ttmb = v->ttfrm; /* MB Transform type */
    int mb_has_coeffs = 0; /* last_flag */
    int index, index1; /* LUT indexes */
    int val, sign; /* temp values */
    int first_block = 1;
    int dst_idx, off;
    int skipped, direct;
    int dmv_x[2], dmv_y[2];
    int bmvtype = BMV_TYPE_BACKWARD;

    mquant      = v->pq; /* lossy initialization */
    s->mb_intra = 0;

    if (v->dmb_is_raw)
        direct = get_bits1(gb);
    else
        direct = v->direct_mb_plane[mb_pos];
    if (v->skip_is_raw)
        skipped = get_bits1(gb);
    else
        skipped = v->s.mbskip_table[mb_pos];

    dmv_x[0] = dmv_x[1] = dmv_y[0] = dmv_y[1] = 0;
    for (i = 0; i < 6; i++) {
        v->mb_type[0][s->block_index[i]] = 0;
        s->dc_val[0][s->block_index[i]]  = 0;
    }
    s->current_picture.qscale_table[mb_pos] = 0;

    if (!direct) {
        if (!skipped) {
            GET_MVDATA(dmv_x[0], dmv_y[0]);
            dmv_x[1] = dmv_x[0];
            dmv_y[1] = dmv_y[0];
        }
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
                dmv_x[0] = dmv_y[0] = 0;
            }
        }
    }
    for (i = 0; i < 6; i++)
        v->mb_type[0][s->block_index[i]] = s->mb_intra;

    if (skipped) {
        if (direct)
            bmvtype = BMV_TYPE_INTERPOLATED;
        ff_vc1_pred_b_mv(v, dmv_x, dmv_y, direct, bmvtype);
        vc1_b_mc(v, dmv_x, dmv_y, direct, bmvtype);
        return 0;
    }
    if (direct) {
        cbp = get_vlc2(&v->s.gb, v->cbpcy_vlc->table, VC1_CBPCY_P_VLC_BITS, 2);
        GET_MQUANT();
        s->mb_intra = 0;
        s->current_picture.qscale_table[mb_pos] = mquant;
        if (!v->ttmbf)
            ttmb = get_vlc2(gb, ff_vc1_ttmb_vlc[v->tt_index].table, VC1_TTMB_VLC_BITS, 2);
        dmv_x[0] = dmv_y[0] = dmv_x[1] = dmv_y[1] = 0;
        ff_vc1_pred_b_mv(v, dmv_x, dmv_y, direct, bmvtype);
        vc1_b_mc(v, dmv_x, dmv_y, direct, bmvtype);
    } else {
        if (!mb_has_coeffs && !s->mb_intra) {
            /* no coded blocks - effectively skipped */
            ff_vc1_pred_b_mv(v, dmv_x, dmv_y, direct, bmvtype);
            vc1_b_mc(v, dmv_x, dmv_y, direct, bmvtype);
            return 0;
        }
        if (s->mb_intra && !mb_has_coeffs) {
            GET_MQUANT();
            s->current_picture.qscale_table[mb_pos] = mquant;
            s->ac_pred = get_bits1(gb);
            cbp = 0;
            ff_vc1_pred_b_mv(v, dmv_x, dmv_y, direct, bmvtype);
        } else {
            if (bmvtype == BMV_TYPE_INTERPOLATED) {
                GET_MVDATA(dmv_x[0], dmv_y[0]);
                if (!mb_has_coeffs) {
                    /* interpolated skipped block */
                    ff_vc1_pred_b_mv(v, dmv_x, dmv_y, direct, bmvtype);
                    vc1_b_mc(v, dmv_x, dmv_y, direct, bmvtype);
                    return 0;
                }
            }
            ff_vc1_pred_b_mv(v, dmv_x, dmv_y, direct, bmvtype);
            if (!s->mb_intra) {
                vc1_b_mc(v, dmv_x, dmv_y, direct, bmvtype);
            }
            if (s->mb_intra)
                s->ac_pred = get_bits1(gb);
            cbp = get_vlc2(&v->s.gb, v->cbpcy_vlc->table, VC1_CBPCY_P_VLC_BITS, 2);
            GET_MQUANT();
            s->current_picture.qscale_table[mb_pos] = mquant;
            if (!v->ttmbf && !s->mb_intra && mb_has_coeffs)
                ttmb = get_vlc2(gb, ff_vc1_ttmb_vlc[v->tt_index].table, VC1_TTMB_VLC_BITS, 2);
        }
    }
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

            vc1_decode_intra_block(v, s->block[i], i, val, mquant,
                                   (i & 4) ? v->codingset2 : v->codingset);
            if (CONFIG_GRAY && (i > 3) && (s->avctx->flags & AV_CODEC_FLAG_GRAY))
                continue;
            v->vc1dsp.vc1_inv_trans_8x8(s->block[i]);
            if (v->rangeredfrm)
                for (j = 0; j < 64; j++)
                    s->block[i][j] *= 2;
            s->idsp.put_signed_pixels_clamped(s->block[i],
                                              s->dest[dst_idx] + off,
                                              i & 4 ? s->uvlinesize
                                                    : s->linesize);
        } else if (val) {
            int pat = vc1_decode_p_block(v, s->block[i], i, mquant, ttmb,
                                         first_block, s->dest[dst_idx] + off,
                                         (i & 4) ? s->uvlinesize : s->linesize,
                                         CONFIG_GRAY && (i & 4) && (s->avctx->flags & AV_CODEC_FLAG_GRAY), NULL);
            if (pat < 0)
                return pat;
            if (!v->ttmbf && ttmb < 8)
                ttmb = -1;
            first_block = 0;
        }
    }
    return 0;
}