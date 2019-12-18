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
struct TYPE_6__ {float size; int ppc_period_bit; float ppc_shape_len; int pgain_bit; } ;
typedef  TYPE_2__ TwinVQModeTab ;
struct TYPE_7__ {TYPE_1__* avctx; TYPE_2__* mtab; } ;
typedef  TYPE_3__ TwinVQContext ;
struct TYPE_5__ {int sample_rate; int bit_rate; int channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWINVQ_PGAIN_MU ; 
 int /*<<< orphan*/  add_peak (float,int,float const*,float,float*,float) ; 
 float log2 (int) ; 
 float powf (double,float) ; 
 double twinvq_mulawinv (float,float,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decode_ppc(TwinVQContext *tctx, int period_coef, int g_coef,
                       const float *shape, float *speech)
{
    const TwinVQModeTab *mtab = tctx->mtab;
    int isampf       = tctx->avctx->sample_rate / 1000;
    int ibps         = tctx->avctx->bit_rate / (1000 * tctx->avctx->channels);
    int width;

    float ratio = (float)mtab->size / isampf;
    float min_period, max_period, period_range, period;
    float some_mult;

    float pgain_base, pgain_step, ppc_gain;

    if (tctx->avctx->channels == 1) {
        min_period = log2(ratio * 0.2);
        max_period = min_period + log2(6);
    } else {
        min_period = (int)(ratio * 0.2 * 400     + 0.5) / 400.0;
        max_period = (int)(ratio * 0.2 * 400 * 6 + 0.5) / 400.0;
    }
    period_range = max_period - min_period;
    period       = min_period + period_coef * period_range /
                   ((1 << mtab->ppc_period_bit) - 1);
    if (tctx->avctx->channels == 1)
        period = powf(2.0, period);
    else
        period = (int)(period * 400 + 0.5) / 400.0;

    switch (isampf) {
    case  8: some_mult = 2.0; break;
    case 11: some_mult = 3.0; break;
    case 16: some_mult = 3.0; break;
    case 22: some_mult = ibps == 32 ? 2.0 : 4.0; break;
    case 44: some_mult = 8.0; break;
    default: some_mult = 4.0;
    }

    width = (int)(some_mult / (mtab->size / period) * mtab->ppc_shape_len);
    if (isampf == 22 && ibps == 32)
        width = (int)((2.0 / period + 1) * width + 0.5);

    pgain_base = tctx->avctx->channels == 2 ? 25000.0 : 20000.0;
    pgain_step = pgain_base / ((1 << mtab->pgain_bit) - 1);
    ppc_gain   = 1.0 / 8192 *
                 twinvq_mulawinv(pgain_step * g_coef + pgain_step / 2,
                                 pgain_base, TWINVQ_PGAIN_MU);

    add_peak(period, width, shape, ppc_gain, speech, mtab->ppc_shape_len);
}