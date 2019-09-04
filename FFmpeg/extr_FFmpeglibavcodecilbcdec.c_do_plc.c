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
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_3__ {int consPLICount; int prevPLI; int* prevResidual; int block_samples; int prevScale; int prevLag; int per_square; int seed; int* prev_lpc; } ;
typedef  TYPE_1__ ILBCContext ;

/* Variables and functions */
 int BLOCKL_MAX ; 
 int FFABS (int) ; 
 int FFMIN (int,int) ; 
 int LPC_FILTERORDER ; 
 int SPL_MUL_16_16 (int,int) ; 
 int SPL_MUL_16_16_RSFT (int,int,int) ; 
 int SPL_SHIFT_W32 (int,int) ; 
 int /*<<< orphan*/  correlation (int*,int*,int*,int,int,int,int) ; 
 int div_w32_w16 (int,int) ; 
 int get_size_in_bits (int) ; 
 int* kPlcPerSqr ; 
 int* kPlcPfSlope ; 
 int* kPlcPitchFact ; 
 int max_abs_value_w16 (int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int norm_w32 (int) ; 
 int scale_dot_product (int*,int*,int,int) ; 

__attribute__((used)) static void do_plc(int16_t *plc_residual,      /* (o) concealed residual */
                   int16_t *plc_lpc,           /* (o) concealed LP parameters */
                   int16_t PLI,                /* (i) packet loss indicator
                                                      0 - no PL, 1 = PL */
                   int16_t *decresidual,       /* (i) decoded residual */
                   int16_t *lpc,               /* (i) decoded LPC (only used for no PL) */
                   int16_t inlag,              /* (i) pitch lag */
                   ILBCContext *s)             /* (i/o) decoder instance */
{
    int16_t i, pick;
    int32_t cross, ener, cross_comp, ener_comp = 0;
    int32_t measure, max_measure, energy;
    int16_t max, cross_square_max, cross_square;
    int16_t j, lag, tmp1, tmp2, randlag;
    int16_t shift1, shift2, shift3, shift_max;
    int16_t scale3;
    int16_t corrLen;
    int32_t tmpW32, tmp2W32;
    int16_t use_gain;
    int16_t tot_gain;
    int16_t max_perSquare;
    int16_t scale1, scale2;
    int16_t totscale;
    int32_t nom;
    int16_t denom;
    int16_t pitchfact;
    int16_t use_lag;
    int ind;
    int16_t randvec[BLOCKL_MAX];

    /* Packet Loss */
    if (PLI == 1) {

        s->consPLICount += 1;

        /* if previous frame not lost,
           determine pitch pred. gain */

        if (s->prevPLI != 1) {

            /* Maximum 60 samples are correlated, preserve as high accuracy
               as possible without getting overflow */
            max = max_abs_value_w16(s->prevResidual, s->block_samples);
            scale3 = (get_size_in_bits(max) << 1) - 25;
            if (scale3 < 0) {
                scale3 = 0;
            }

            /* Store scale for use when interpolating between the
             * concealment and the received packet */
            s->prevScale = scale3;

            /* Search around the previous lag +/-3 to find the
               best pitch period */
            lag = inlag - 3;

            /* Guard against getting outside the frame */
            corrLen = FFMIN(60, s->block_samples - (inlag + 3));

            correlation(&cross, &ener, s->prevResidual, lag, s->block_samples, corrLen, scale3);

            /* Normalize and store cross^2 and the number of shifts */
            shift_max = get_size_in_bits(FFABS(cross)) - 15;
            cross_square_max = (int16_t) SPL_MUL_16_16_RSFT(SPL_SHIFT_W32(cross, -shift_max), SPL_SHIFT_W32(cross, -shift_max), 15);

            for (j = inlag - 2; j <= inlag + 3; j++) {
                correlation(&cross_comp, &ener_comp, s->prevResidual, j, s->block_samples, corrLen, scale3);

                /* Use the criteria (corr*corr)/energy to compare if
                   this lag is better or not. To avoid the division,
                   do a cross multiplication */
                shift1 = get_size_in_bits(FFABS(cross_comp)) - 15;
                cross_square = (int16_t) SPL_MUL_16_16_RSFT(SPL_SHIFT_W32(cross_comp, -shift1), SPL_SHIFT_W32(cross_comp, -shift1), 15);

                shift2 = get_size_in_bits(ener) - 15;
                measure = SPL_MUL_16_16(SPL_SHIFT_W32(ener, -shift2), cross_square);

                shift3 = get_size_in_bits(ener_comp) - 15;
                max_measure = SPL_MUL_16_16(SPL_SHIFT_W32(ener_comp, -shift3), cross_square_max);

                /* Calculate shift value, so that the two measures can
                   be put in the same Q domain */
                if (((shift_max << 1) + shift3) > ((shift1 << 1) + shift2)) {
                    tmp1 = FFMIN(31, (shift_max << 1) + shift3 - (shift1 << 1) - shift2);
                    tmp2 = 0;
                } else {
                    tmp1 = 0;
                    tmp2 = FFMIN(31, (shift1 << 1) + shift2 - (shift_max << 1) - shift3);
                }

                if ((measure >> tmp1) > (max_measure >> tmp2)) {
                    /* New lag is better => record lag, measure and domain */
                    lag = j;
                    cross_square_max = cross_square;
                    cross = cross_comp;
                    shift_max = shift1;
                    ener = ener_comp;
                }
            }

            /* Calculate the periodicity for the lag with the maximum correlation.

               Definition of the periodicity:
               abs(corr(vec1, vec2))/(sqrt(energy(vec1))*sqrt(energy(vec2)))

               Work in the Square domain to simplify the calculations
               max_perSquare is less than 1 (in Q15)
             */
            tmp2W32 = scale_dot_product(&s->prevResidual[s->block_samples - corrLen], &s->prevResidual[s->block_samples - corrLen], corrLen, scale3);

            if ((tmp2W32 > 0) && (ener_comp > 0)) {
                /* norm energies to int16_t, compute the product of the energies and
                   use the upper int16_t as the denominator */

                scale1 = norm_w32(tmp2W32) - 16;
                tmp1 = SPL_SHIFT_W32(tmp2W32, scale1);

                scale2 = norm_w32(ener) - 16;
                tmp2 =  SPL_SHIFT_W32(ener, scale2);
                denom = SPL_MUL_16_16_RSFT(tmp1, tmp2, 16);    /* denom in Q(scale1+scale2-16) */

                /* Square the cross correlation and norm it such that max_perSquare
                   will be in Q15 after the division */

                totscale = scale1 + scale2 - 1;
                tmp1 = SPL_SHIFT_W32(cross, (totscale >> 1));
                tmp2 = SPL_SHIFT_W32(cross, totscale - (totscale >> 1));

                nom = SPL_MUL_16_16(tmp1, tmp2);
                max_perSquare = div_w32_w16(nom, denom);
            } else {
                max_perSquare = 0;
            }
        } else {
            /* previous frame lost, use recorded lag and gain */
            lag = s->prevLag;
            max_perSquare = s->per_square;
        }

        /* Attenuate signal and scale down pitch pred gain if
           several frames lost consecutively */

        use_gain = 32767;       /* 1.0 in Q15 */

        if (s->consPLICount * s->block_samples > 320) {
            use_gain = 29491;   /* 0.9 in Q15 */
        } else if (s->consPLICount * s->block_samples > 640) {
            use_gain = 22938;   /* 0.7 in Q15 */
        } else if (s->consPLICount * s->block_samples > 960) {
            use_gain = 16384;   /* 0.5 in Q15 */
        } else if (s->consPLICount * s->block_samples > 1280) {
            use_gain = 0;       /* 0.0 in Q15 */
        }

        /* Compute mixing factor of picth repeatition and noise:
           for max_per>0.7 set periodicity to 1.0
           0.4<max_per<0.7 set periodicity to (maxper-0.4)/0.7-0.4)
           max_per<0.4 set periodicity to 0.0
         */

        if (max_perSquare > 7868) {     /* periodicity > 0.7  (0.7^4=0.2401 in Q15) */
            pitchfact = 32767;
        } else if (max_perSquare > 839) {       /* 0.4 < periodicity < 0.7 (0.4^4=0.0256 in Q15) */
            /* find best index and interpolate from that */
            ind = 5;
            while ((max_perSquare < kPlcPerSqr[ind]) && (ind > 0)) {
                ind--;
            }
            /* pitch fact is approximated by first order */
            tmpW32 = kPlcPitchFact[ind] + SPL_MUL_16_16_RSFT(kPlcPfSlope[ind], (max_perSquare - kPlcPerSqr[ind]), 11);

            pitchfact = FFMIN(tmpW32, 32767); /* guard against overflow */

        } else {                /* periodicity < 0.4 */
            pitchfact = 0;
        }

        /* avoid repetition of same pitch cycle (buzzyness) */
        use_lag = lag;
        if (lag < 80) {
            use_lag = 2 * lag;
        }

        /* compute concealed residual */
        energy = 0;

        for (i = 0; i < s->block_samples; i++) {
            /* noise component -  52 < randlagFIX < 117 */
            s->seed = SPL_MUL_16_16(s->seed, 31821) + 13849;
            randlag = 53 + (s->seed & 63);

            pick = i - randlag;

            if (pick < 0) {
                randvec[i] = s->prevResidual[s->block_samples + pick];
            } else {
                randvec[i] = s->prevResidual[pick];
            }

            /* pitch repeatition component */
            pick = i - use_lag;

            if (pick < 0) {
                plc_residual[i] = s->prevResidual[s->block_samples + pick];
            } else {
                plc_residual[i] = plc_residual[pick];
            }

            /* Attinuate total gain for each 10 ms */
            if (i < 80) {
                tot_gain = use_gain;
            } else if (i < 160) {
                tot_gain = SPL_MUL_16_16_RSFT(31130, use_gain, 15);    /* 0.95*use_gain */
            } else {
                tot_gain = SPL_MUL_16_16_RSFT(29491, use_gain, 15);    /* 0.9*use_gain */
            }

            /* mix noise and pitch repeatition */
            plc_residual[i] = SPL_MUL_16_16_RSFT(tot_gain, (pitchfact * plc_residual[i] + (32767 - pitchfact) * randvec[i] + 16384) >> 15, 15);

            /* Shifting down the result one step extra to ensure that no overflow
               will occur */
            energy += SPL_MUL_16_16_RSFT(plc_residual[i], plc_residual[i], (s->prevScale + 1));

        }

        /* less than 30 dB, use only noise */
        if (energy < SPL_SHIFT_W32(s->block_samples * 900, -s->prevScale - 1)) {
            energy = 0;
            for (i = 0; i < s->block_samples; i++) {
                plc_residual[i] = randvec[i];
            }
        }

        /* use the old LPC */
        memcpy(plc_lpc, (*s).prev_lpc, (LPC_FILTERORDER + 1) * 2);

        /* Update state in case there are multiple frame losses */
        s->prevLag = lag;
        s->per_square = max_perSquare;
    } else { /* no packet loss, copy input */
        memcpy(plc_residual, decresidual, s->block_samples * 2);
        memcpy(plc_lpc, lpc, (LPC_FILTERORDER + 1) * 2);
        s->consPLICount = 0;
    }

    /* update state */
    s->prevPLI = PLI;
    memcpy(s->prev_lpc, plc_lpc, (LPC_FILTERORDER + 1) * 2);
    memcpy(s->prevResidual, plc_residual, s->block_samples * 2);

    return;
}