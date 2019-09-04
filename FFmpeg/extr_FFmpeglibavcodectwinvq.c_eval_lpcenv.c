#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; int /*<<< orphan*/  n_lsp; TYPE_1__* fmode; } ;
typedef  TYPE_2__ TwinVQModeTab ;
struct TYPE_7__ {float** cos_tabs; TYPE_2__* mtab; } ;
typedef  TYPE_3__ TwinVQContext ;
struct TYPE_5__ {int sub; } ;

/* Variables and functions */
 size_t TWINVQ_FT_SHORT ; 
 float eval_lpc_spectrum (float const*,float,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eval_lpcenv(TwinVQContext *tctx, const float *cos_vals, float *lpc)
{
    int i;
    const TwinVQModeTab *mtab = tctx->mtab;
    int size_s = mtab->size / mtab->fmode[TWINVQ_FT_SHORT].sub;

    for (i = 0; i < size_s / 2; i++) {
        float cos_i = tctx->cos_tabs[0][i];
        lpc[i]              = eval_lpc_spectrum(cos_vals,  cos_i, mtab->n_lsp);
        lpc[size_s - i - 1] = eval_lpc_spectrum(cos_vals, -cos_i, mtab->n_lsp);
    }
}