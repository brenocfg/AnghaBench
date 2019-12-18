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
 int LP_FILTER_ORDER_16k ; 
 int /*<<< orphan*/  dequant (float*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsf_codebooks_16k ; 
 int* mean_lsf_16k ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int* qu ; 

__attribute__((used)) static void lsf_decode_fp_16k(float* lsf_history, float* isp_new,
                              const int* parm, int ma_pred)
{
    int i;
    float isp_q[LP_FILTER_ORDER_16k];

    dequant(isp_q, parm, lsf_codebooks_16k);

    for (i = 0; i < LP_FILTER_ORDER_16k; i++) {
        isp_new[i] = (1 - qu[ma_pred]) * isp_q[i]
                    +     qu[ma_pred]  * lsf_history[i]
                    + mean_lsf_16k[i];
    }

    memcpy(lsf_history, isp_q, LP_FILTER_ORDER_16k * sizeof(float));
}