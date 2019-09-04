#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int e; void* m; } ;
typedef  TYPE_1__ softfloat ;
typedef  int int32_t ;
struct TYPE_11__ {int e; int /*<<< orphan*/  m; } ;
struct TYPE_10__ {int e; int /*<<< orphan*/  m; } ;
struct TYPE_9__ {int* cb_to_level; } ;
typedef  TYPE_2__ DCAEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 int* ff_dca_quant_levels ; 
 void* mul32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int quantize_value (int,TYPE_1__) ; 
 TYPE_4__* scalefactor_inv ; 
 TYPE_3__* stepsize_inv ; 

__attribute__((used)) static int calc_one_scale(DCAEncContext *c, int32_t peak_cb, int abits,
                          softfloat *quant)
{
    int32_t peak;
    int our_nscale, try_remove;
    softfloat our_quant;

    av_assert0(peak_cb <= 0);
    av_assert0(peak_cb >= -2047);

    our_nscale = 127;
    peak = c->cb_to_level[-peak_cb];

    for (try_remove = 64; try_remove > 0; try_remove >>= 1) {
        if (scalefactor_inv[our_nscale - try_remove].e + stepsize_inv[abits].e <= 17)
            continue;
        our_quant.m = mul32(scalefactor_inv[our_nscale - try_remove].m, stepsize_inv[abits].m);
        our_quant.e = scalefactor_inv[our_nscale - try_remove].e + stepsize_inv[abits].e - 17;
        if ((ff_dca_quant_levels[abits] - 1) / 2 < quantize_value(peak, our_quant))
            continue;
        our_nscale -= try_remove;
    }

    if (our_nscale >= 125)
        our_nscale = 124;

    quant->m = mul32(scalefactor_inv[our_nscale].m, stepsize_inv[abits].m);
    quant->e = scalefactor_inv[our_nscale].e + stepsize_inv[abits].e - 17;
    av_assert0((ff_dca_quant_levels[abits] - 1) / 2 >= quantize_value(peak, *quant));

    return our_nscale;
}