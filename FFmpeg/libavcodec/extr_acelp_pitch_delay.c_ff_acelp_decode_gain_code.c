#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* scalarproduct_int16 ) (int const*,int const*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* scalarproduct_int16 ) (int const*,int const*,int) ;} ;
typedef  TYPE_1__ AudioDSPContext ;

/* Variables and functions */
 int bidir_sal (int,int) ; 
 TYPE_3__* dsp ; 
 int ff_exp10 (double) ; 
 int ff_exp2 (int) ; 
 long long ff_log2 (int /*<<< orphan*/ ) ; 
 int sqrt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int const*,int const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int const*,int const*,int) ; 

int16_t ff_acelp_decode_gain_code(
    AudioDSPContext *adsp,
    int gain_corr_factor,
    const int16_t* fc_v,
    int mr_energy,
    const int16_t* quant_energy,
    const int16_t* ma_prediction_coeff,
    int subframe_size,
    int ma_pred_order)
{
    int i;

    mr_energy <<= 10;

    for(i=0; i<ma_pred_order; i++)
        mr_energy += quant_energy[i] * ma_prediction_coeff[i];

#ifdef G729_BITEXACT
    mr_energy += (((-6165LL * ff_log2(dsp->scalarproduct_int16(fc_v, fc_v, subframe_size, 0))) >> 3) & ~0x3ff);

    mr_energy = (5439 * (mr_energy >> 15)) >> 8;           // (0.15) = (0.15) * (7.23)

    return bidir_sal(
               ((ff_exp2(mr_energy & 0x7fff) + 16) >> 5) * (gain_corr_factor >> 1),
               (mr_energy >> 15) - 25
           );
#else
    mr_energy = gain_corr_factor * ff_exp10((double)mr_energy / (20 << 23)) /
                sqrt(adsp->scalarproduct_int16(fc_v, fc_v, subframe_size));
    return mr_energy >> 12;
#endif
}