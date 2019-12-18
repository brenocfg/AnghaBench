#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_8__ {int* coeff_index_to_pos; int /*<<< orphan*/ * coeff_index_to_idct_selector; } ;
typedef  TYPE_2__ VP56Model ;
struct TYPE_9__ {size_t* idct_scantable; int dequant_ac; int** block_coeff; int /*<<< orphan*/ * idct_selector; TYPE_4__*** ract_vlc; int /*<<< orphan*/  gb; void*** nb_null; TYPE_1__* runv_vlc; TYPE_4__* dccv_vlc; TYPE_2__* modelp; } ;
typedef  TYPE_3__ VP56Context ;
struct TYPE_10__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_4__ VLC ;
struct TYPE_7__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 size_t FFMIN (int,int) ; 
 int /*<<< orphan*/  FF_HUFFMAN_BITS ; 
 int* ff_vp56_coeff_bias ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* vp6_coeff_groups ; 
 void* vp6_get_nb_null (TYPE_3__*) ; 

__attribute__((used)) static int vp6_parse_coeff_huffman(VP56Context *s)
{
    VP56Model *model = s->modelp;
    uint8_t *permute = s->idct_scantable;
    VLC *vlc_coeff;
    int coeff, sign, coeff_idx;
    int b, cg, idx;
    int pt = 0;    /* plane type (0 for Y, 1 for U or V) */

    for (b=0; b<6; b++) {
        int ct = 0;    /* code type */
        if (b > 3) pt = 1;
        vlc_coeff = &s->dccv_vlc[pt];

        for (coeff_idx = 0;;) {
            int run = 1;
            if (coeff_idx<2 && s->nb_null[coeff_idx][pt]) {
                s->nb_null[coeff_idx][pt]--;
                if (coeff_idx)
                    break;
            } else {
                if (get_bits_left(&s->gb) <= 0)
                    return AVERROR_INVALIDDATA;
                coeff = get_vlc2(&s->gb, vlc_coeff->table, FF_HUFFMAN_BITS, 3);
                if (coeff == 0) {
                    if (coeff_idx) {
                        int pt = (coeff_idx >= 6);
                        run += get_vlc2(&s->gb, s->runv_vlc[pt].table, FF_HUFFMAN_BITS, 3);
                        if (run >= 9)
                            run += get_bits(&s->gb, 6);
                    } else
                        s->nb_null[0][pt] = vp6_get_nb_null(s);
                    ct = 0;
                } else if (coeff == 11) {  /* end of block */
                    if (coeff_idx == 1)    /* first AC coeff ? */
                        s->nb_null[1][pt] = vp6_get_nb_null(s);
                    break;
                } else {
                    int coeff2 = ff_vp56_coeff_bias[coeff];
                    if (coeff > 4)
                        coeff2 += get_bits(&s->gb, coeff <= 9 ? coeff - 4 : 11);
                    ct = 1 + (coeff2 > 1);
                    sign = get_bits1(&s->gb);
                    coeff2 = (coeff2 ^ -sign) + sign;
                    if (coeff_idx)
                        coeff2 *= s->dequant_ac;
                    idx = model->coeff_index_to_pos[coeff_idx];
                    s->block_coeff[b][permute[idx]] = coeff2;
                }
            }
            coeff_idx+=run;
            if (coeff_idx >= 64)
                break;
            cg = FFMIN(vp6_coeff_groups[coeff_idx], 3);
            vlc_coeff = &s->ract_vlc[pt][ct][cg];
        }
        s->idct_selector[b] = model->coeff_index_to_idct_selector[FFMIN(coeff_idx, 63)];
    }
    return 0;
}