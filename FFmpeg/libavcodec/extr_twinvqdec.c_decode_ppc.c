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
struct TYPE_6__ {int size; int pgain_bit; int ppc_period_bit; int peak_per2wid; int /*<<< orphan*/  ppc_shape_len; } ;
typedef  TYPE_2__ TwinVQModeTab ;
struct TYPE_7__ {TYPE_1__* avctx; TYPE_2__* mtab; } ;
typedef  TYPE_3__ TwinVQContext ;
struct TYPE_5__ {int sample_rate; int bit_rate; int channels; } ;

/* Variables and functions */
 int ROUNDED_DIV (int,int) ; 
 int /*<<< orphan*/  TWINVQ_PGAIN_MU ; 
 int /*<<< orphan*/  add_peak (int,int,float const*,float,float*,int /*<<< orphan*/ ) ; 
 double twinvq_mulawinv (float,double,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decode_ppc(TwinVQContext *tctx, int period_coef, int g_coef,
                       const float *shape, float *speech)
{
    const TwinVQModeTab *mtab = tctx->mtab;
    int isampf = tctx->avctx->sample_rate /  1000;
    int ibps   = tctx->avctx->bit_rate    / (1000 * tctx->avctx->channels);
    int min_period   = ROUNDED_DIV(40 * 2 * mtab->size, isampf);
    int max_period   = ROUNDED_DIV(40 * 2 * mtab->size * 6, isampf);
    int period_range = max_period - min_period;
    float pgain_step = 25000.0 / ((1 << mtab->pgain_bit) - 1);
    float ppc_gain   = 1.0 / 8192 *
                       twinvq_mulawinv(pgain_step * g_coef +
                                           pgain_step / 2,
                                       25000.0, TWINVQ_PGAIN_MU);

    // This is actually the period multiplied by 400. It is just linearly coded
    // between its maximum and minimum value.
    int period = min_period +
                 ROUNDED_DIV(period_coef * period_range,
                             (1 << mtab->ppc_period_bit) - 1);
    int width;

    if (isampf == 22 && ibps == 32) {
        // For some unknown reason, NTT decided to code this case differently...
        width = ROUNDED_DIV((period + 800) * mtab->peak_per2wid,
                            400 * mtab->size);
    } else
        width = period * mtab->peak_per2wid / (400 * mtab->size);

    add_peak(period, width, shape, ppc_gain, speech, mtab->ppc_shape_len);
}