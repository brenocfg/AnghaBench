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
typedef  scalar_t__ int8_t ;
typedef  scalar_t__ int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int DCA_ADPCM_COEFFS ; 
 scalar_t__ clip23 (scalar_t__) ; 
 scalar_t__ ff_dcaadpcm_predict (int const,scalar_t__*) ; 

__attribute__((used)) static inline void inverse_adpcm(int32_t **subband_samples,
                                 const int16_t *vq_index,
                                 const int8_t *prediction_mode,
                                 int sb_start, int sb_end,
                                 int ofs, int len)
{
    int i, j;

    for (i = sb_start; i < sb_end; i++) {
        if (prediction_mode[i]) {
            const int pred_id = vq_index[i];
            int32_t *ptr = subband_samples[i] + ofs;
            for (j = 0; j < len; j++) {
                int32_t x = ff_dcaadpcm_predict(pred_id, ptr + j - DCA_ADPCM_COEFFS);
                ptr[j] = clip23(ptr[j] + x);
            }
        }
    }
}