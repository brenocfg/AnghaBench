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
 int FFABS (int) ; 
 float FFMAX (float,float) ; 
 int /*<<< orphan*/  PITCH_MAX_PERIOD ; 
 float Q15ONE ; 
 float celt_inner_prod (float*,float*,int) ; 
 float compute_pitch_gain (float,float,float) ; 
 int /*<<< orphan*/  dual_inner_prod (float*,float*,float*,int,float*,float*) ; 
 int* second_check ; 

__attribute__((used)) static float remove_doubling(float *x, int maxperiod, int minperiod, int N,
                             int *T0_, int prev_period, float prev_gain)
{
    int k, i, T, T0;
    float g, g0;
    float pg;
    float xy,xx,yy,xy2;
    float xcorr[3];
    float best_xy, best_yy;
    int offset;
    int minperiod0;
    float yy_lookup[PITCH_MAX_PERIOD+1];

    minperiod0 = minperiod;
    maxperiod /= 2;
    minperiod /= 2;
    *T0_ /= 2;
    prev_period /= 2;
    N /= 2;
    x += maxperiod;
    if (*T0_>=maxperiod)
        *T0_=maxperiod-1;

    T = T0 = *T0_;
    dual_inner_prod(x, x, x-T0, N, &xx, &xy);
    yy_lookup[0] = xx;
    yy=xx;
    for (i = 1; i <= maxperiod; i++) {
        yy = yy+(x[-i] * x[-i])-(x[N-i] * x[N-i]);
        yy_lookup[i] = FFMAX(0, yy);
    }
    yy = yy_lookup[T0];
    best_xy = xy;
    best_yy = yy;
    g = g0 = compute_pitch_gain(xy, xx, yy);
    /* Look for any pitch at T/k */
    for (k = 2; k <= 15; k++) {
        int T1, T1b;
        float g1;
        float cont=0;
        float thresh;
        T1 = (2*T0+k)/(2*k);
        if (T1 < minperiod)
            break;
        /* Look for another strong correlation at T1b */
        if (k==2)
        {
            if (T1+T0>maxperiod)
                T1b = T0;
            else
                T1b = T0+T1;
        } else
        {
            T1b = (2*second_check[k]*T0+k)/(2*k);
        }
        dual_inner_prod(x, &x[-T1], &x[-T1b], N, &xy, &xy2);
        xy = .5f * (xy + xy2);
        yy = .5f * (yy_lookup[T1] + yy_lookup[T1b]);
        g1 = compute_pitch_gain(xy, xx, yy);
        if (FFABS(T1-prev_period)<=1)
            cont = prev_gain;
        else if (FFABS(T1-prev_period)<=2 && 5 * k * k < T0)
            cont = prev_gain * .5f;
        else
            cont = 0;
        thresh = FFMAX(.3f, (.7f * g0) - cont);
        /* Bias against very high pitch (very short period) to avoid false-positives
           due to short-term correlation */
        if (T1<3*minperiod)
            thresh = FFMAX(.4f, (.85f * g0) - cont);
        else if (T1<2*minperiod)
            thresh = FFMAX(.5f, (.9f * g0) - cont);
        if (g1 > thresh)
        {
            best_xy = xy;
            best_yy = yy;
            T = T1;
            g = g1;
        }
    }
    best_xy = FFMAX(0, best_xy);
    if (best_yy <= best_xy)
        pg = Q15ONE;
    else
        pg = best_xy/(best_yy + 1);

    for (k = 0; k < 3; k++)
        xcorr[k] = celt_inner_prod(x, x-(T+k-1), N);
    if ((xcorr[2]-xcorr[0]) > .7f * (xcorr[1]-xcorr[0]))
        offset = 1;
    else if ((xcorr[0]-xcorr[2]) > (.7f * (xcorr[1] - xcorr[2])))
        offset = -1;
    else
        offset = 0;
    if (pg > g)
        pg = g;
    *T0_ = 2*T+offset;

    if (*T0_<minperiod0)
        *T0_=minperiod0;
    return pg;
}