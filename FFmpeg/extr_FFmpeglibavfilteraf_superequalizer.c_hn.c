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
struct TYPE_3__ {float upper; float gain; } ;
typedef  TYPE_1__ EqParameter ;

/* Variables and functions */
 int NBANDS ; 
 float hn_imp (int) ; 
 float hn_lpf (int,float,float) ; 

__attribute__((used)) static float hn(int n, EqParameter *param, float fs)
{
    float ret, lhn;
    int i;

    lhn = hn_lpf(n, param[0].upper, fs);
    ret = param[0].gain*lhn;

    for (i = 1; i < NBANDS + 1 && param[i].upper < fs / 2; i++) {
        float lhn2 = hn_lpf(n, param[i].upper, fs);
        ret += param[i].gain * (lhn2 - lhn);
        lhn = lhn2;
    }

    ret += param[i].gain * (hn_imp(n) - lhn);

    return ret;
}