#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  VP56RangeCoder ;
struct TYPE_8__ {size_t** coeff_dccv; size_t*** coeff_dcct; int* coeff_index_to_pos; size_t** coeff_runv; size_t**** coeff_ract; int /*<<< orphan*/ * coeff_index_to_idct_selector; } ;
typedef  TYPE_3__ VP56Model ;
struct TYPE_9__ {size_t* idct_scantable; size_t* above_block_idx; int dequant_ac; int** block_coeff; int /*<<< orphan*/ * idct_selector; TYPE_2__* above_blocks; TYPE_1__* left_block; int /*<<< orphan*/  avctx; TYPE_3__* modelp; int /*<<< orphan*/ * ccp; } ;
typedef  TYPE_4__ VP56Context ;
struct TYPE_7__ {int not_null_dc; } ;
struct TYPE_6__ {int not_null_dc; } ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 size_t FFMIN (int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 size_t* ff_vp56_b6to4 ; 
 int* ff_vp56_coeff_bias ; 
 int* ff_vp56_coeff_bit_length ; 
 size_t** ff_vp56_coeff_parse_table ; 
 int /*<<< orphan*/  ff_vp56_pc_tree ; 
 int vp56_rac_get (int /*<<< orphan*/ *) ; 
 int vp56_rac_get_prob (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ vp56_rac_get_prob_branchy (int /*<<< orphan*/ *,size_t) ; 
 int vp56_rac_get_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int* vp6_coeff_groups ; 
 int /*<<< orphan*/  vp6_pcr_tree ; 
 scalar_t__ vpX_rac_is_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vp6_parse_coeff(VP56Context *s)
{
    VP56RangeCoder *c = s->ccp;
    VP56Model *model = s->modelp;
    uint8_t *permute = s->idct_scantable;
    uint8_t *model1, *model2, *model3;
    int coeff, sign, coeff_idx;
    int b, i, cg, idx, ctx;
    int pt = 0;    /* plane type (0 for Y, 1 for U or V) */

    if (vpX_rac_is_end(c)) {
        av_log(s->avctx, AV_LOG_ERROR, "End of AC stream reached in vp6_parse_coeff\n");
        return AVERROR_INVALIDDATA;
    }

    for (b=0; b<6; b++) {
        int ct = 1;    /* code type */
        int run = 1;

        if (b > 3) pt = 1;

        ctx = s->left_block[ff_vp56_b6to4[b]].not_null_dc
              + s->above_blocks[s->above_block_idx[b]].not_null_dc;
        model1 = model->coeff_dccv[pt];
        model2 = model->coeff_dcct[pt][ctx];

        coeff_idx = 0;
        for (;;) {
            if ((coeff_idx>1 && ct==0) || vp56_rac_get_prob_branchy(c, model2[0])) {
                /* parse a coeff */
                if (vp56_rac_get_prob_branchy(c, model2[2])) {
                    if (vp56_rac_get_prob_branchy(c, model2[3])) {
                        idx = vp56_rac_get_tree(c, ff_vp56_pc_tree, model1);
                        coeff = ff_vp56_coeff_bias[idx+5];
                        for (i=ff_vp56_coeff_bit_length[idx]; i>=0; i--)
                            coeff += vp56_rac_get_prob(c, ff_vp56_coeff_parse_table[idx][i]) << i;
                    } else {
                        if (vp56_rac_get_prob_branchy(c, model2[4]))
                            coeff = 3 + vp56_rac_get_prob(c, model1[5]);
                        else
                            coeff = 2;
                    }
                    ct = 2;
                } else {
                    ct = 1;
                    coeff = 1;
                }
                sign = vp56_rac_get(c);
                coeff = (coeff ^ -sign) + sign;
                if (coeff_idx)
                    coeff *= s->dequant_ac;
                idx = model->coeff_index_to_pos[coeff_idx];
                s->block_coeff[b][permute[idx]] = coeff;
                run = 1;
            } else {
                /* parse a run */
                ct = 0;
                if (coeff_idx > 0) {
                    if (!vp56_rac_get_prob_branchy(c, model2[1]))
                        break;

                    model3 = model->coeff_runv[coeff_idx >= 6];
                    run = vp56_rac_get_tree(c, vp6_pcr_tree, model3);
                    if (!run)
                        for (run=9, i=0; i<6; i++)
                            run += vp56_rac_get_prob(c, model3[i+8]) << i;
                }
            }
            coeff_idx += run;
            if (coeff_idx >= 64)
                break;
            cg = vp6_coeff_groups[coeff_idx];
            model1 = model2 = model->coeff_ract[pt][ct][cg];
        }

        s->left_block[ff_vp56_b6to4[b]].not_null_dc =
        s->above_blocks[s->above_block_idx[b]].not_null_dc = !!s->block_coeff[b][0];
        s->idct_selector[b] = model->coeff_index_to_idct_selector[FFMIN(coeff_idx, 63)];
    }
    return 0;
}