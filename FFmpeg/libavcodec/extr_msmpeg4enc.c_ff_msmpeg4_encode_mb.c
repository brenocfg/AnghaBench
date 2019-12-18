#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_10__ {int* block_last_index; int msmpeg4_version; scalar_t__ pict_type; size_t h263_aic_dir; int /*<<< orphan*/  i_count; int /*<<< orphan*/  i_tex_bits; scalar_t__ misc_bits; int /*<<< orphan*/  pb; scalar_t__ inter_intra_pred; scalar_t__ use_skip_mb_code; int /*<<< orphan*/  p_tex_bits; int /*<<< orphan*/  mv_bits; int /*<<< orphan*/  skip_count; int /*<<< orphan*/  last_bits; int /*<<< orphan*/  mb_intra; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int** ff_h263_cbpy_tab ; 
 int /*<<< orphan*/  ff_h263_pred_motion (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int** ff_msmp4_mb_i_table ; 
 int ff_msmpeg4_coded_block_pred (TYPE_1__*,int,int**) ; 
 int /*<<< orphan*/  ff_msmpeg4_encode_block (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_msmpeg4_encode_motion (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ff_msmpeg4_handle_slices (TYPE_1__*) ; 
 int** ff_table_inter_intra ; 
 int** ff_table_mb_non_intra ; 
 int** ff_v2_intra_cbpc ; 
 int** ff_v2_mb_type ; 
 scalar_t__ get_bits_diff (TYPE_1__*) ; 
 int /*<<< orphan*/  msmpeg4v2_encode_motion (TYPE_1__*,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

void ff_msmpeg4_encode_mb(MpegEncContext * s,
                          int16_t block[6][64],
                          int motion_x, int motion_y)
{
    int cbp, coded_cbp, i;
    int pred_x, pred_y;
    uint8_t *coded_block;

    ff_msmpeg4_handle_slices(s);

    if (!s->mb_intra) {
        /* compute cbp */
        cbp = 0;
        for (i = 0; i < 6; i++) {
            if (s->block_last_index[i] >= 0)
                cbp |= 1 << (5 - i);
        }
        if (s->use_skip_mb_code && (cbp | motion_x | motion_y) == 0) {
            /* skip macroblock */
            put_bits(&s->pb, 1, 1);
            s->last_bits++;
            s->misc_bits++;
            s->skip_count++;

            return;
        }
        if (s->use_skip_mb_code)
            put_bits(&s->pb, 1, 0);     /* mb coded */

        if(s->msmpeg4_version<=2){
            put_bits(&s->pb,
                     ff_v2_mb_type[cbp&3][1],
                     ff_v2_mb_type[cbp&3][0]);
            if((cbp&3) != 3) coded_cbp= cbp ^ 0x3C;
            else             coded_cbp= cbp;

            put_bits(&s->pb,
                     ff_h263_cbpy_tab[coded_cbp>>2][1],
                     ff_h263_cbpy_tab[coded_cbp>>2][0]);

            s->misc_bits += get_bits_diff(s);

            ff_h263_pred_motion(s, 0, 0, &pred_x, &pred_y);
            msmpeg4v2_encode_motion(s, motion_x - pred_x);
            msmpeg4v2_encode_motion(s, motion_y - pred_y);
        }else{
            put_bits(&s->pb,
                     ff_table_mb_non_intra[cbp + 64][1],
                     ff_table_mb_non_intra[cbp + 64][0]);

            s->misc_bits += get_bits_diff(s);

            /* motion vector */
            ff_h263_pred_motion(s, 0, 0, &pred_x, &pred_y);
            ff_msmpeg4_encode_motion(s, motion_x - pred_x,
                                  motion_y - pred_y);
        }

        s->mv_bits += get_bits_diff(s);

        for (i = 0; i < 6; i++) {
            ff_msmpeg4_encode_block(s, block[i], i);
        }
        s->p_tex_bits += get_bits_diff(s);
    } else {
        /* compute cbp */
        cbp = 0;
        coded_cbp = 0;
        for (i = 0; i < 6; i++) {
            int val, pred;
            val = (s->block_last_index[i] >= 1);
            cbp |= val << (5 - i);
            if (i < 4) {
                /* predict value for close blocks only for luma */
                pred = ff_msmpeg4_coded_block_pred(s, i, &coded_block);
                *coded_block = val;
                val = val ^ pred;
            }
            coded_cbp |= val << (5 - i);
        }

        if(s->msmpeg4_version<=2){
            if (s->pict_type == AV_PICTURE_TYPE_I) {
                put_bits(&s->pb,
                         ff_v2_intra_cbpc[cbp&3][1], ff_v2_intra_cbpc[cbp&3][0]);
            } else {
                if (s->use_skip_mb_code)
                    put_bits(&s->pb, 1, 0);     /* mb coded */
                put_bits(&s->pb,
                         ff_v2_mb_type[(cbp&3) + 4][1],
                         ff_v2_mb_type[(cbp&3) + 4][0]);
            }
            put_bits(&s->pb, 1, 0);             /* no AC prediction yet */
            put_bits(&s->pb,
                     ff_h263_cbpy_tab[cbp>>2][1],
                     ff_h263_cbpy_tab[cbp>>2][0]);
        }else{
            if (s->pict_type == AV_PICTURE_TYPE_I) {
                put_bits(&s->pb,
                         ff_msmp4_mb_i_table[coded_cbp][1], ff_msmp4_mb_i_table[coded_cbp][0]);
            } else {
                if (s->use_skip_mb_code)
                    put_bits(&s->pb, 1, 0);     /* mb coded */
                put_bits(&s->pb,
                         ff_table_mb_non_intra[cbp][1],
                         ff_table_mb_non_intra[cbp][0]);
            }
            put_bits(&s->pb, 1, 0);             /* no AC prediction yet */
            if(s->inter_intra_pred){
                s->h263_aic_dir=0;
                put_bits(&s->pb, ff_table_inter_intra[s->h263_aic_dir][1], ff_table_inter_intra[s->h263_aic_dir][0]);
            }
        }
        s->misc_bits += get_bits_diff(s);

        for (i = 0; i < 6; i++) {
            ff_msmpeg4_encode_block(s, block[i], i);
        }
        s->i_tex_bits += get_bits_diff(s);
        s->i_count++;
    }
}