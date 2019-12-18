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
struct TYPE_3__ {double a0; int a1; double a2; int b1; double b2; } ;
typedef  TYPE_1__ BiquadD2 ;

/* Variables and functions */
 double M_PI ; 
 double cos (double) ; 
 int sin (double) ; 
 int sqrt (double) ; 

__attribute__((used)) static inline void set_highshelf_rbj(BiquadD2 *bq, double freq, double q, double peak, double sr)
{
    double A = sqrt(peak);
    double w0 = freq * 2 * M_PI / sr;
    double alpha = sin(w0) / (2 * q);
    double cw0 = cos(w0);
    double tmp = 2 * sqrt(A) * alpha;
    double b0 = 0, ib0 = 0;

    bq->a0 =    A*( (A+1) + (A-1)*cw0 + tmp);
    bq->a1 = -2*A*( (A-1) + (A+1)*cw0);
    bq->a2 =    A*( (A+1) + (A-1)*cw0 - tmp);
        b0 =        (A+1) - (A-1)*cw0 + tmp;
    bq->b1 =    2*( (A-1) - (A+1)*cw0);
    bq->b2 =        (A+1) - (A-1)*cw0 - tmp;

    ib0     = 1 / b0;
    bq->b1 *= ib0;
    bq->b2 *= ib0;
    bq->a0 *= ib0;
    bq->a1 *= ib0;
    bq->a2 *= ib0;
}