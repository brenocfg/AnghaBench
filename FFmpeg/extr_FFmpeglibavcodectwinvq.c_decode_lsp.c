#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int8_t ;
struct TYPE_4__ {float* lspcodebook; int lsp_bit1; int n_lsp; int lsp_bit2; int lsp_split; } ;
typedef  TYPE_1__ TwinVQModeTab ;
struct TYPE_5__ {TYPE_1__* mtab; } ;
typedef  TYPE_2__ TwinVQContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_sort_nearly_sorted_floats (float*,int) ; 
 int /*<<< orphan*/  rearrange_lsp (int,float*,double) ; 

__attribute__((used)) static void decode_lsp(TwinVQContext *tctx, int lpc_idx1, uint8_t *lpc_idx2,
                       int lpc_hist_idx, float *lsp, float *hist)
{
    const TwinVQModeTab *mtab = tctx->mtab;
    int i, j;

    const float *cb  = mtab->lspcodebook;
    const float *cb2 = cb  + (1 << mtab->lsp_bit1) * mtab->n_lsp;
    const float *cb3 = cb2 + (1 << mtab->lsp_bit2) * mtab->n_lsp;

    const int8_t funny_rounding[4] = {
        -2,
        mtab->lsp_split == 4 ? -2 : 1,
        mtab->lsp_split == 4 ? -2 : 1,
        0
    };

    j = 0;
    for (i = 0; i < mtab->lsp_split; i++) {
        int chunk_end = ((i + 1) * mtab->n_lsp + funny_rounding[i]) /
                        mtab->lsp_split;
        for (; j < chunk_end; j++)
            lsp[j] = cb[lpc_idx1     * mtab->n_lsp + j] +
                     cb2[lpc_idx2[i] * mtab->n_lsp + j];
    }

    rearrange_lsp(mtab->n_lsp, lsp, 0.0001);

    for (i = 0; i < mtab->n_lsp; i++) {
        float tmp1 = 1.0     - cb3[lpc_hist_idx * mtab->n_lsp + i];
        float tmp2 = hist[i] * cb3[lpc_hist_idx * mtab->n_lsp + i];
        hist[i] = lsp[i];
        lsp[i]  = lsp[i] * tmp1 + tmp2;
    }

    rearrange_lsp(mtab->n_lsp, lsp, 0.0001);
    rearrange_lsp(mtab->n_lsp, lsp, 0.000095);
    ff_sort_nearly_sorted_floats(lsp, mtab->n_lsp);
}