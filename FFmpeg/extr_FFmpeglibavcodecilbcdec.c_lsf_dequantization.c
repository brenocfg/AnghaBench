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

/* Variables and functions */
 int LPC_FILTERORDER ; 
 int LSF_NSPLIT ; 
 int* lsf_codebook ; 
 int* lsf_dim_codebook ; 
 int* lsf_size_codebook ; 

__attribute__((used)) static void lsf_dequantization(int16_t *lsfdeq, int16_t *index, int16_t lpc_n)
{
    int i, j, pos = 0, cb_pos = 0;

    for (i = 0; i < LSF_NSPLIT; i++) {
        for (j = 0; j < lsf_dim_codebook[i]; j++) {
            lsfdeq[pos + j] = lsf_codebook[cb_pos + index[i] * lsf_dim_codebook[i] + j];
        }

        pos    += lsf_dim_codebook[i];
        cb_pos += lsf_size_codebook[i] * lsf_dim_codebook[i];
    }

    if (lpc_n > 1) {
        pos = 0;
        cb_pos = 0;
        for (i = 0; i < LSF_NSPLIT; i++) {
            for (j = 0; j < lsf_dim_codebook[i]; j++) {
                lsfdeq[LPC_FILTERORDER + pos + j] = lsf_codebook[cb_pos +
                    index[LSF_NSPLIT + i] * lsf_dim_codebook[i] + j];
            }

            pos    += lsf_dim_codebook[i];
            cb_pos += lsf_size_codebook[i] * lsf_dim_codebook[i];
        }
    }
}