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
struct TYPE_3__ {float* sp_hist; float* gain_hist; float* gain_lpc; int /*<<< orphan*/  sp_lpc; } ;
typedef  TYPE_1__ RA288Context ;

/* Variables and functions */
 float FFMAX (float,double) ; 
 float av_clipf (float,int /*<<< orphan*/ ,int) ; 
 float avpriv_scalarproduct_float_c (float*,float*,int) ; 
 double** codetable ; 
 float exp (float) ; 
 int /*<<< orphan*/  ff_celp_lp_synthesis_filterf (float*,int /*<<< orphan*/ ,float*,int,int) ; 
 int log10 (int) ; 
 int /*<<< orphan*/  memmove (float*,float*,int) ; 

__attribute__((used)) static void decode(RA288Context *ractx, float gain, int cb_coef)
{
    int i;
    double sumsum;
    float sum, buffer[5];
    float *block = ractx->sp_hist + 70 + 36; // current block
    float *gain_block = ractx->gain_hist + 28;

    memmove(ractx->sp_hist + 70, ractx->sp_hist + 75, 36*sizeof(*block));

    /* block 46 of G.728 spec */
    sum = 32.0;
    for (i=0; i < 10; i++)
        sum -= gain_block[9-i] * ractx->gain_lpc[i];

    /* block 47 of G.728 spec */
    sum = av_clipf(sum, 0, 60);

    /* block 48 of G.728 spec */
    /* exp(sum * 0.1151292546497) == pow(10.0,sum/20) */
    sumsum = exp(sum * 0.1151292546497) * gain * (1.0/(1<<23));

    for (i=0; i < 5; i++)
        buffer[i] = codetable[cb_coef][i] * sumsum;

    sum = avpriv_scalarproduct_float_c(buffer, buffer, 5);

    sum = FFMAX(sum, 5.0 / (1<<24));

    /* shift and store */
    memmove(gain_block, gain_block + 1, 9 * sizeof(*gain_block));

    gain_block[9] = 10 * log10(sum) + (10*log10(((1<<24)/5.)) - 32);

    ff_celp_lp_synthesis_filterf(block, ractx->sp_lpc, buffer, 5, 36);
}