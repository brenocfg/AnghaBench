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
typedef  double int32_t ;

/* Variables and functions */
 double FFMAX (double,int /*<<< orphan*/ ) ; 
 double av_clip (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  fabs (double) ; 
 int /*<<< orphan*/  lrintf (double) ; 
 int /*<<< orphan*/  memset (double*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void quantize_lpc_coefs(double *lpc_in, int order, int precision,
                               int32_t *lpc_out, int *shift, int min_shift,
                               int max_shift, int zero_shift)
{
    int i;
    double cmax, error;
    int32_t qmax;
    int sh;

    /* define maximum levels */
    qmax = (1 << (precision - 1)) - 1;

    /* find maximum coefficient value */
    cmax = 0.0;
    for(i=0; i<order; i++) {
        cmax= FFMAX(cmax, fabs(lpc_in[i]));
    }

    /* if maximum value quantizes to zero, return all zeros */
    if(cmax * (1 << max_shift) < 1.0) {
        *shift = zero_shift;
        memset(lpc_out, 0, sizeof(int32_t) * order);
        return;
    }

    /* calculate level shift which scales max coeff to available bits */
    sh = max_shift;
    while((cmax * (1 << sh) > qmax) && (sh > min_shift)) {
        sh--;
    }

    /* since negative shift values are unsupported in decoder, scale down
       coefficients instead */
    if(sh == 0 && cmax > qmax) {
        double scale = ((double)qmax) / cmax;
        for(i=0; i<order; i++) {
            lpc_in[i] *= scale;
        }
    }

    /* output quantized coefficients and level shift */
    error=0;
    for(i=0; i<order; i++) {
        error -= lpc_in[i] * (1 << sh);
        lpc_out[i] = av_clip(lrintf(error), -qmax, qmax);
        error -= lpc_out[i];
    }
    *shift = sh;
}