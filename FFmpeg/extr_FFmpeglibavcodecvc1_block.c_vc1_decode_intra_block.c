#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_11__ {int* qscale_table; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* clear_block ) (int*) ;} ;
struct TYPE_13__ {int mb_x; int mb_y; int mb_stride; int ac_pred; int y_dc_scale; int* y_dc_scale_table; int c_dc_scale; int* c_dc_scale_table; size_t dc_table_index; int*** ac_val; size_t* block_index; int* block_wrap; int* block_last_index; TYPE_2__ current_picture; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; TYPE_1__ bdsp; } ;
struct TYPE_12__ {int a_avail; int c_avail; int halfpq; scalar_t__ fcm; size_t** zz_8x8; size_t* zzi_8x8; int left_blk_sh; int top_blk_sh; int /*<<< orphan*/  pquantizer; int /*<<< orphan*/  overlap; TYPE_4__ s; } ;
typedef  TYPE_3__ VC1Context ;
struct TYPE_15__ {int /*<<< orphan*/  table; } ;
struct TYPE_14__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_4__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  DC_VLC_BITS ; 
 int FFABS (int) ; 
 scalar_t__ ILACE_FRAME ; 
 scalar_t__ PROGRESSIVE ; 
 int av_clip_uintp2 (int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_9__* ff_msmp4_dc_chroma_vlc ; 
 TYPE_8__* ff_msmp4_dc_luma_vlc ; 
 int* ff_vc1_dqscale ; 
 scalar_t__ ff_vc1_pred_dc (TYPE_4__*,int /*<<< orphan*/ ,int,int,int,int,int**,int*) ; 
 int get_bits (int /*<<< orphan*/ *,int const) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int*) ; 
 int /*<<< orphan*/  vc1_decode_ac_coeff (TYPE_3__*,int*,int*,int*,int) ; 

__attribute__((used)) static int vc1_decode_intra_block(VC1Context *v, int16_t block[64], int n,
                                  int coded, int mquant, int codingset)
{
    GetBitContext *gb = &v->s.gb;
    MpegEncContext *s = &v->s;
    int dc_pred_dir = 0; /* Direction of the DC prediction used */
    int i;
    int16_t *dc_val = NULL;
    int16_t *ac_val, *ac_val2;
    int dcdiff;
    int mb_pos = s->mb_x + s->mb_y * s->mb_stride;
    int a_avail = v->a_avail, c_avail = v->c_avail;
    int use_pred = s->ac_pred;
    int scale;
    int q1, q2 = 0;
    int quant = FFABS(mquant);

    s->bdsp.clear_block(block);

    /* XXX: Guard against dumb values of mquant */
    quant = av_clip_uintp2(quant, 5);

    /* Set DC scale - y and c use the same */
    s->y_dc_scale = s->y_dc_scale_table[quant];
    s->c_dc_scale = s->c_dc_scale_table[quant];

    /* Get DC differential */
    if (n < 4) {
        dcdiff = get_vlc2(&s->gb, ff_msmp4_dc_luma_vlc[s->dc_table_index].table, DC_VLC_BITS, 3);
    } else {
        dcdiff = get_vlc2(&s->gb, ff_msmp4_dc_chroma_vlc[s->dc_table_index].table, DC_VLC_BITS, 3);
    }
    if (dcdiff < 0) {
        av_log(s->avctx, AV_LOG_ERROR, "Illegal DC VLC\n");
        return -1;
    }
    if (dcdiff) {
        const int m = (quant == 1 || quant == 2) ? 3 - quant : 0;
        if (dcdiff == 119 /* ESC index value */) {
            dcdiff = get_bits(gb, 8 + m);
        } else {
            if (m)
                dcdiff = (dcdiff << m) + get_bits(gb, m) - ((1 << m) - 1);
        }
        if (get_bits1(gb))
            dcdiff = -dcdiff;
    }

    /* Prediction */
    dcdiff += ff_vc1_pred_dc(&v->s, v->overlap, quant, n, a_avail, c_avail, &dc_val, &dc_pred_dir);
    *dc_val = dcdiff;

    /* Store the quantized DC coeff, used for prediction */

    if (n < 4) {
        block[0] = dcdiff * s->y_dc_scale;
    } else {
        block[0] = dcdiff * s->c_dc_scale;
    }

    //AC Decoding
    i = 1;

    /* check if AC is needed at all and adjust direction if needed */
    if (!a_avail) dc_pred_dir = 1;
    if (!c_avail) dc_pred_dir = 0;
    if (!a_avail && !c_avail) use_pred = 0;
    ac_val = s->ac_val[0][s->block_index[n]];
    ac_val2 = ac_val;

    scale = quant * 2 + ((mquant < 0) ? 0 : v->halfpq);

    if (dc_pred_dir) //left
        ac_val -= 16;
    else //top
        ac_val -= 16 * s->block_wrap[n];

    q1 = s->current_picture.qscale_table[mb_pos];
    if (dc_pred_dir && c_avail && mb_pos)
        q2 = s->current_picture.qscale_table[mb_pos - 1];
    if (!dc_pred_dir && a_avail && mb_pos >= s->mb_stride)
        q2 = s->current_picture.qscale_table[mb_pos - s->mb_stride];
    if (dc_pred_dir && n == 1)
        q2 = q1;
    if (!dc_pred_dir && n == 2)
        q2 = q1;
    if (n == 3) q2 = q1;

    if (coded) {
        int last = 0, skip, value;
        int k;

        while (!last) {
            vc1_decode_ac_coeff(v, &last, &skip, &value, codingset);
            i += skip;
            if (i > 63)
                break;
            if (v->fcm == PROGRESSIVE)
                block[v->zz_8x8[0][i++]] = value;
            else {
                if (use_pred && (v->fcm == ILACE_FRAME)) {
                    if (!dc_pred_dir) // top
                        block[v->zz_8x8[2][i++]] = value;
                    else // left
                        block[v->zz_8x8[3][i++]] = value;
                } else {
                    block[v->zzi_8x8[i++]] = value;
                }
            }
        }

        /* apply AC prediction if needed */
        if (use_pred) {
            /* scale predictors if needed*/
            q1 = FFABS(q1) * 2 + ((q1 < 0) ? 0 : v->halfpq) - 1;
            if (q1 < 1)
                return AVERROR_INVALIDDATA;
            if (q2)
                q2 = FFABS(q2) * 2 + ((q2 < 0) ? 0 : v->halfpq) - 1;
            if (q2 && q1 != q2) {
                if (dc_pred_dir) { // left
                    for (k = 1; k < 8; k++)
                        block[k << v->left_blk_sh] += (ac_val[k] * q2 * ff_vc1_dqscale[q1 - 1] + 0x20000) >> 18;
                } else { //top
                    for (k = 1; k < 8; k++)
                        block[k << v->top_blk_sh] += (ac_val[k + 8] * q2 * ff_vc1_dqscale[q1 - 1] + 0x20000) >> 18;
                }
            } else {
                if (dc_pred_dir) { // left
                    for (k = 1; k < 8; k++)
                        block[k << v->left_blk_sh] += ac_val[k];
                } else { // top
                    for (k = 1; k < 8; k++)
                        block[k << v->top_blk_sh] += ac_val[k + 8];
                }
            }
        }
        /* save AC coeffs for further prediction */
        for (k = 1; k < 8; k++) {
            ac_val2[k    ] = block[k << v->left_blk_sh];
            ac_val2[k + 8] = block[k << v->top_blk_sh];
        }

        /* scale AC coeffs */
        for (k = 1; k < 64; k++)
            if (block[k]) {
                block[k] *= scale;
                if (!v->pquantizer)
                    block[k] += (block[k] < 0) ? -quant : quant;
            }

        if (use_pred) i = 63;
    } else { // no AC coeffs
        int k;

        memset(ac_val2, 0, 16 * 2);
        if (dc_pred_dir) { // left
            if (use_pred) {
                memcpy(ac_val2, ac_val, 8 * 2);
                q1 = FFABS(q1) * 2 + ((q1 < 0) ? 0 : v->halfpq) - 1;
                if (q1 < 1)
                    return AVERROR_INVALIDDATA;
                if (q2)
                    q2 = FFABS(q2) * 2 + ((q2 < 0) ? 0 : v->halfpq) - 1;
                if (q2 && q1 != q2) {
                    for (k = 1; k < 8; k++)
                        ac_val2[k] = (ac_val2[k] * q2 * ff_vc1_dqscale[q1 - 1] + 0x20000) >> 18;
                }
            }
        } else { // top
            if (use_pred) {
                memcpy(ac_val2 + 8, ac_val + 8, 8 * 2);
                q1 = FFABS(q1) * 2 + ((q1 < 0) ? 0 : v->halfpq) - 1;
                if (q1 < 1)
                    return AVERROR_INVALIDDATA;
                if (q2)
                    q2 = FFABS(q2) * 2 + ((q2 < 0) ? 0 : v->halfpq) - 1;
                if (q2 && q1 != q2) {
                    for (k = 1; k < 8; k++)
                        ac_val2[k + 8] = (ac_val2[k + 8] * q2 * ff_vc1_dqscale[q1 - 1] + 0x20000) >> 18;
                }
            }
        }

        /* apply AC prediction if needed */
        if (use_pred) {
            if (dc_pred_dir) { // left
                for (k = 1; k < 8; k++) {
                    block[k << v->left_blk_sh] = ac_val2[k] * scale;
                    if (!v->pquantizer && block[k << v->left_blk_sh])
                        block[k << v->left_blk_sh] += (block[k << v->left_blk_sh] < 0) ? -quant : quant;
                }
            } else { // top
                for (k = 1; k < 8; k++) {
                    block[k << v->top_blk_sh] = ac_val2[k + 8] * scale;
                    if (!v->pquantizer && block[k << v->top_blk_sh])
                        block[k << v->top_blk_sh] += (block[k << v->top_blk_sh] < 0) ? -quant : quant;
                }
            }
            i = 63;
        }
    }
    s->block_last_index[n] = i;

    return 0;
}