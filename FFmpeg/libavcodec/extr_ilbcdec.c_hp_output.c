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
 int INT32_MAX ; 
 int INT32_MIN ; 
 int SPL_MUL_16_16 (int,int const) ; 
 int av_clip_intp2 (int,int) ; 

__attribute__((used)) static void hp_output(int16_t *signal, const int16_t *ba, int16_t *y,
                      int16_t *x, int16_t len)
{
    int32_t tmp;

    for (int i = 0; i < len; i++) {
        tmp = SPL_MUL_16_16(y[1], ba[3]);     /* (-a[1])*y[i-1] (low part) */
        tmp += SPL_MUL_16_16(y[3], ba[4]);    /* (-a[2])*y[i-2] (low part) */
        tmp = (tmp >> 15);
        tmp += SPL_MUL_16_16(y[0], ba[3]);    /* (-a[1])*y[i-1] (high part) */
        tmp += SPL_MUL_16_16(y[2], ba[4]);    /* (-a[2])*y[i-2] (high part) */
        tmp = (tmp * 2);

        tmp += SPL_MUL_16_16(signal[i], ba[0]);       /* b[0]*x[0] */
        tmp += SPL_MUL_16_16(x[0], ba[1]);    /* b[1]*x[i-1] */
        tmp += SPL_MUL_16_16(x[1], ba[2]);    /* b[2]*x[i-2] */

        /* Update state (input part) */
        x[1] = x[0];
        x[0] = signal[i];

        /* Convert back to Q0 and multiply with 2 */
        signal[i] = av_clip_intp2(tmp + 1024, 26) >> 11;

        /* Update state (filtered part) */
        y[2] = y[0];
        y[3] = y[1];

        /* upshift tmp by 3 with saturation */
        if (tmp > 268435455) {
            tmp = INT32_MAX;
        } else if (tmp < -268435456) {
            tmp = INT32_MIN;
        } else {
            tmp = tmp * 8;
        }

        y[0] = tmp >> 16;
        y[1] = (tmp - (y[0] * (1 << 16))) >> 1;
    }
}