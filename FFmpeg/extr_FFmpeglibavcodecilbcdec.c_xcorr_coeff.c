#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int INT16_MAX ; 
 scalar_t__ SPL_MUL_16_16_RSFT (int,int,int) ; 
 scalar_t__ SPL_SHIFT_W32 (scalar_t__,int) ; 
 int max_abs_value_w16 (int*,int) ; 
 int norm_w32 (scalar_t__) ; 
 scalar_t__ scale_dot_product (int*,int*,int,int) ; 

__attribute__((used)) static int xcorr_coeff(int16_t *target, int16_t *regressor,
                       int16_t subl, int16_t searchLen,
                       int16_t offset, int16_t step)
{
    int16_t maxlag;
    int16_t pos;
    int16_t max;
    int16_t cross_corr_scale, energy_scale;
    int16_t cross_corr_sg_mod, cross_corr_sg_mod_max;
    int32_t cross_corr, energy;
    int16_t cross_corr_mod, energy_mod, enery_mod_max;
    int16_t *tp, *rp;
    int16_t *rp_beg, *rp_end;
    int16_t totscale, totscale_max;
    int16_t scalediff;
    int32_t new_crit, max_crit;
    int shifts;
    int k;

    /* Initializations, to make sure that the first one is selected */
    cross_corr_sg_mod_max = 0;
    enery_mod_max = INT16_MAX;
    totscale_max = -500;
    maxlag = 0;
    pos = 0;

    /* Find scale value and start position */
    if (step == 1) {
        max = max_abs_value_w16(regressor, (int16_t) (subl + searchLen - 1));
        rp_beg = regressor;
        rp_end = &regressor[subl];
    } else {                    /* step== -1 */
        max = max_abs_value_w16(&regressor[-searchLen], (int16_t) (subl + searchLen - 1));
        rp_beg = &regressor[-1];
        rp_end = &regressor[subl - 1];
    }

    /* Introduce a scale factor on the energy in int32_t in
       order to make sure that the calculation does not
       overflow */

    if (max > 5000) {
        shifts = 2;
    } else {
        shifts = 0;
    }

    /* Calculate the first energy, then do a +/- to get the other energies */
    energy = scale_dot_product(regressor, regressor, subl, shifts);

    for (k = 0; k < searchLen; k++) {
        tp = target;
        rp = &regressor[pos];

        cross_corr = scale_dot_product(tp, rp, subl, shifts);

        if ((energy > 0) && (cross_corr > 0)) {
            /* Put cross correlation and energy on 16 bit word */
            cross_corr_scale = norm_w32(cross_corr) - 16;
            cross_corr_mod = (int16_t) SPL_SHIFT_W32(cross_corr, cross_corr_scale);
            energy_scale = norm_w32(energy) - 16;
            energy_mod = (int16_t) SPL_SHIFT_W32(energy, energy_scale);

            /* Square cross correlation and store upper int16_t */
            cross_corr_sg_mod = (int16_t) SPL_MUL_16_16_RSFT(cross_corr_mod, cross_corr_mod, 16);

            /* Calculate the total number of (dynamic) right shifts that have
               been performed on (cross_corr*cross_corr)/energy
             */
            totscale = energy_scale - (cross_corr_scale * 2);

            /* Calculate the shift difference in order to be able to compare the two
               (cross_corr*cross_corr)/energy in the same domain
             */
            scalediff = totscale - totscale_max;
            scalediff = FFMIN(scalediff, 31);
            scalediff = FFMAX(scalediff, -31);

            /* Compute the cross multiplication between the old best criteria
               and the new one to be able to compare them without using a
               division */

            if (scalediff < 0) {
                new_crit = ((int32_t) cross_corr_sg_mod * enery_mod_max) >> (-scalediff);
                max_crit = ((int32_t) cross_corr_sg_mod_max * energy_mod);
            } else {
                new_crit = ((int32_t) cross_corr_sg_mod * enery_mod_max);
                max_crit = ((int32_t) cross_corr_sg_mod_max * energy_mod) >> scalediff;
            }

            /* Store the new lag value if the new criteria is larger
               than previous largest criteria */

            if (new_crit > max_crit) {
                cross_corr_sg_mod_max = cross_corr_sg_mod;
                enery_mod_max = energy_mod;
                totscale_max = totscale;
                maxlag = k;
            }
        }
        pos += step;

        /* Do a +/- to get the next energy */
        energy += (unsigned)step * ((*rp_end * *rp_end - *rp_beg * *rp_beg) >> shifts);

        rp_beg += step;
        rp_end += step;
    }

    return maxlag + offset;
}