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

/* Variables and functions */
 int AMRWB_SFR_SIZE_16k ; 
 int HB_FIR_SIZE ; 
 int /*<<< orphan*/  memcpy (float*,float const*,int) ; 

__attribute__((used)) static void hb_fir_filter(float *out, const float fir_coef[HB_FIR_SIZE + 1],
                          float mem[HB_FIR_SIZE], const float *in)
{
    int i, j;
    float data[AMRWB_SFR_SIZE_16k + HB_FIR_SIZE]; // past and current samples

    memcpy(data, mem, HB_FIR_SIZE * sizeof(float));
    memcpy(data + HB_FIR_SIZE, in, AMRWB_SFR_SIZE_16k * sizeof(float));

    for (i = 0; i < AMRWB_SFR_SIZE_16k; i++) {
        out[i] = 0.0;
        for (j = 0; j <= HB_FIR_SIZE; j++)
            out[i] += data[i + j] * fir_coef[j];
    }

    memcpy(mem, data + AMRWB_SFR_SIZE_16k, HB_FIR_SIZE * sizeof(float));
}