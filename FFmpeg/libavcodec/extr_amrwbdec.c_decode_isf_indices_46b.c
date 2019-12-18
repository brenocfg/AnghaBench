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
typedef  size_t uint16_t ;

/* Variables and functions */
 float** dico1_isf ; 
 float** dico21_isf ; 
 float** dico22_isf ; 
 float** dico23_isf ; 
 float** dico24_isf ; 
 float** dico25_isf ; 
 float** dico2_isf ; 

__attribute__((used)) static void decode_isf_indices_46b(uint16_t *ind, float *isf_q)
{
    int i;

    for (i = 0; i < 9; i++)
        isf_q[i]       = dico1_isf[ind[0]][i]  * (1.0f / (1 << 15));

    for (i = 0; i < 7; i++)
        isf_q[i + 9]   = dico2_isf[ind[1]][i]  * (1.0f / (1 << 15));

    for (i = 0; i < 3; i++)
        isf_q[i]      += dico21_isf[ind[2]][i] * (1.0f / (1 << 15));

    for (i = 0; i < 3; i++)
        isf_q[i + 3]  += dico22_isf[ind[3]][i] * (1.0f / (1 << 15));

    for (i = 0; i < 3; i++)
        isf_q[i + 6]  += dico23_isf[ind[4]][i] * (1.0f / (1 << 15));

    for (i = 0; i < 3; i++)
        isf_q[i + 9]  += dico24_isf[ind[5]][i] * (1.0f / (1 << 15));

    for (i = 0; i < 4; i++)
        isf_q[i + 12] += dico25_isf[ind[6]][i] * (1.0f / (1 << 15));
}