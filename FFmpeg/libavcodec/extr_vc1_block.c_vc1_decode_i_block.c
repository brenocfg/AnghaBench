#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int int16_t ;
struct TYPE_9__ {size_t dc_table_index; int y_dc_scale; int c_dc_scale; int*** ac_val; size_t* block_index; int* block_wrap; int* block_last_index; scalar_t__ ac_pred; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; } ;
struct TYPE_8__ {int pq; int halfpq; size_t** zz_8x8; int left_blk_sh; int top_blk_sh; int /*<<< orphan*/  pquantizer; TYPE_2__ s; int /*<<< orphan*/  overlap; } ;
typedef  TYPE_1__ VC1Context ;
struct TYPE_11__ {int /*<<< orphan*/  table; } ;
struct TYPE_10__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  DC_VLC_BITS ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_7__* ff_msmp4_dc_chroma_vlc ; 
 TYPE_6__* ff_msmp4_dc_luma_vlc ; 
 int get_bits (int /*<<< orphan*/ *,int const) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int vc1_decode_ac_coeff (TYPE_1__*,int*,int*,int*,int) ; 
 scalar_t__ vc1_i_pred_dc (TYPE_2__*,int /*<<< orphan*/ ,int,int,int**,int*) ; 

__attribute__((used)) static int vc1_decode_i_block(VC1Context *v, int16_t block[64], int n,
                              int coded, int codingset)
{
    GetBitContext *gb = &v->s.gb;
    MpegEncContext *s = &v->s;
    int dc_pred_dir = 0; /* Direction of the DC prediction used */
    int i;
    int16_t *dc_val;
    int16_t *ac_val, *ac_val2;
    int dcdiff, scale;

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
        const int m = (v->pq == 1 || v->pq == 2) ? 3 - v->pq : 0;
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
    dcdiff += vc1_i_pred_dc(&v->s, v->overlap, v->pq, n, &dc_val, &dc_pred_dir);
    *dc_val = dcdiff;

    /* Store the quantized DC coeff, used for prediction */
    if (n < 4)
        scale = s->y_dc_scale;
    else
        scale = s->c_dc_scale;
    block[0] = dcdiff * scale;

    ac_val  = s->ac_val[0][s->block_index[n]];
    ac_val2 = ac_val;
    if (dc_pred_dir) // left
        ac_val -= 16;
    else // top
        ac_val -= 16 * s->block_wrap[n];

    scale = v->pq * 2 + v->halfpq;

    //AC Decoding
    i = !!coded;

    if (coded) {
        int last = 0, skip, value;
        const uint8_t *zz_table;
        int k;

        if (v->s.ac_pred) {
            if (!dc_pred_dir)
                zz_table = v->zz_8x8[2];
            else
                zz_table = v->zz_8x8[3];
        } else
            zz_table = v->zz_8x8[1];

        while (!last) {
            int ret = vc1_decode_ac_coeff(v, &last, &skip, &value, codingset);
            if (ret < 0)
                return ret;
            i += skip;
            if (i > 63)
                break;
            block[zz_table[i++]] = value;
        }

        /* apply AC prediction if needed */
        if (s->ac_pred) {
            int sh;
            if (dc_pred_dir) { // left
                sh = v->left_blk_sh;
            } else { // top
                sh = v->top_blk_sh;
                ac_val += 8;
            }
            for (k = 1; k < 8; k++)
                block[k << sh] += ac_val[k];
        }
        /* save AC coeffs for further prediction */
        for (k = 1; k < 8; k++) {
            ac_val2[k]     = block[k << v->left_blk_sh];
            ac_val2[k + 8] = block[k << v->top_blk_sh];
        }

        /* scale AC coeffs */
        for (k = 1; k < 64; k++)
            if (block[k]) {
                block[k] *= scale;
                if (!v->pquantizer)
                    block[k] += (block[k] < 0) ? -v->pq : v->pq;
            }

    } else {
        int k;

        memset(ac_val2, 0, 16 * 2);

        /* apply AC prediction if needed */
        if (s->ac_pred) {
            int sh;
            if (dc_pred_dir) { //left
                sh = v->left_blk_sh;
            } else { // top
                sh = v->top_blk_sh;
                ac_val  += 8;
                ac_val2 += 8;
            }
            memcpy(ac_val2, ac_val, 8 * 2);
            for (k = 1; k < 8; k++) {
                block[k << sh] = ac_val[k] * scale;
                if (!v->pquantizer && block[k << sh])
                    block[k << sh] += (block[k << sh] < 0) ? -v->pq : v->pq;
            }
        }
    }
    if (s->ac_pred) i = 63;
    s->block_last_index[n] = i;

    return 0;
}