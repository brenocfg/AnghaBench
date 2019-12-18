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
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int* cos_derivative_tbl ; 
 int* cos_tbl ; 

__attribute__((used)) static void lsf2lsp(int16_t *lsf, int16_t *lsp, int order)
{
    int16_t diff, freq;
    int32_t tmp;
    int i, k;

    for (i = 0; i < order; i++) {
        freq = (lsf[i] * 20861) >> 15;
        /* 20861: 1.0/(2.0*PI) in Q17 */
        /*
           Upper 8 bits give the index k and
           Lower 8 bits give the difference, which needs
           to be approximated linearly
         */
        k = FFMIN(freq >> 8, 63);
        diff = freq & 0xFF;

        /* Calculate linear approximation */
        tmp = cos_derivative_tbl[k] * diff;
        lsp[i] = cos_tbl[k] + (tmp >> 12);
    }
}