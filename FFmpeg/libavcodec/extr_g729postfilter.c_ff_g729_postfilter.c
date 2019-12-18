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
typedef  int int16_t ;
typedef  int /*<<< orphan*/  AudioDSPContext ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int RES_PREV_DATA_SIZE ; 
 int /*<<< orphan*/  SUBFRAME_SIZE ; 
 int apply_tilt_comp (int*,int*,int,int,int) ; 
 int /*<<< orphan*/  ff_celp_lp_synthesis_filter (int*,int*,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int const* formant_pp_factor_den_pow ; 
 int const* formant_pp_factor_num_pow ; 
 int get_tilt_comp (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 int long_term_filter (int /*<<< orphan*/ *,int,int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  residual_filter (int*,int*,int*,int) ; 

void ff_g729_postfilter(AudioDSPContext *adsp, int16_t* ht_prev_data, int* voicing,
                     const int16_t *lp_filter_coeffs, int pitch_delay_int,
                     int16_t* residual, int16_t* res_filter_data,
                     int16_t* pos_filter_data, int16_t *speech, int subframe_size)
{
    int16_t residual_filt_buf[SUBFRAME_SIZE+11];
    int16_t lp_gn[33]; // (3.12)
    int16_t lp_gd[11]; // (3.12)
    int tilt_comp_coeff;
    int i;

    /* Zero-filling is necessary for tilt-compensation filter. */
    memset(lp_gn, 0, 33 * sizeof(int16_t));

    /* Calculate A(z/FORMANT_PP_FACTOR_NUM) filter coefficients. */
    for (i = 0; i < 10; i++)
        lp_gn[i + 11] = (lp_filter_coeffs[i + 1] * formant_pp_factor_num_pow[i] + 0x4000) >> 15;

    /* Calculate A(z/FORMANT_PP_FACTOR_DEN) filter coefficients. */
    for (i = 0; i < 10; i++)
        lp_gd[i + 1] = (lp_filter_coeffs[i + 1] * formant_pp_factor_den_pow[i] + 0x4000) >> 15;

    /* residual signal calculation (one-half of short-term postfilter) */
    memcpy(speech - 10, res_filter_data, 10 * sizeof(int16_t));
    residual_filter(residual + RES_PREV_DATA_SIZE, lp_gn + 11, speech, subframe_size);
    /* Save data to use it in the next subframe. */
    memcpy(res_filter_data, speech + subframe_size - 10, 10 * sizeof(int16_t));

    /* long-term filter. If long-term prediction gain is larger than 3dB (returned value is
       nonzero) then declare current subframe as periodic. */
    i = long_term_filter(adsp, pitch_delay_int,
                                                residual, residual_filt_buf + 10,
                                                subframe_size);
    *voicing = FFMAX(*voicing, i);

    /* shift residual for using in next subframe */
    memmove(residual, residual + subframe_size, RES_PREV_DATA_SIZE * sizeof(int16_t));

    /* short-term filter tilt compensation */
    tilt_comp_coeff = get_tilt_comp(adsp, lp_gn, lp_gd, residual_filt_buf + 10, subframe_size);

    /* Apply second half of short-term postfilter: 1/A(z/FORMANT_PP_FACTOR_DEN) */
    ff_celp_lp_synthesis_filter(pos_filter_data + 10, lp_gd + 1,
                                residual_filt_buf + 10,
                                subframe_size, 10, 0, 0, 0x800);
    memcpy(pos_filter_data, pos_filter_data + subframe_size, 10 * sizeof(int16_t));

    *ht_prev_data = apply_tilt_comp(speech, pos_filter_data + 10, tilt_comp_coeff,
                                    subframe_size, *ht_prev_data);
}