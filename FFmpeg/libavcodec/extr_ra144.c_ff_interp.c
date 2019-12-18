#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_3__ {int** lpc_coef; int /*<<< orphan*/ * lpc_refl_rms; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ RA144Context ;

/* Variables and functions */
 int LPC_ORDER ; 
 int NBLOCKS ; 
 scalar_t__ ff_eval_refl (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_int_to_int16 (int*,int*) ; 
 int ff_rescale_rms (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_rms (int*) ; 

int ff_interp(RA144Context *ractx, int16_t *out, int a, int copyold, int energy)
{
    int work[LPC_ORDER];
    int b = NBLOCKS - a;
    int i;

    // Interpolate block coefficients from the this frame's forth block and
    // last frame's forth block.
    for (i = 0; i < LPC_ORDER; i++)
        out[i] = (a * ractx->lpc_coef[0][i] + b * ractx->lpc_coef[1][i])>> 2;

    if (ff_eval_refl(work, out, ractx->avctx)) {
        // The interpolated coefficients are unstable, copy either new or old
        // coefficients.
        ff_int_to_int16(out, ractx->lpc_coef[copyold]);
        return ff_rescale_rms(ractx->lpc_refl_rms[copyold], energy);
    } else {
        return ff_rescale_rms(ff_rms(work), energy);
    }
}