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
struct TYPE_3__ {double a2; double a0; double a1; double b1; double b2; } ;
typedef  TYPE_1__ BiquadD2 ;

/* Variables and functions */
 double M_PI ; 
 double cos (double) ; 
 double sin (double) ; 

__attribute__((used)) static inline void set_lp_rbj(BiquadD2 *bq, double fc, double q, double sr, double gain)
{
    double omega = 2.0 * M_PI * fc / sr;
    double sn = sin(omega);
    double cs = cos(omega);
    double alpha = sn/(2 * q);
    double inv = 1.0/(1.0 + alpha);

    bq->a2 = bq->a0 = gain * inv * (1.0 - cs) * 0.5;
    bq->a1 = bq->a0 + bq->a0;
    bq->b1 = (-2.0 * cs * inv);
    bq->b2 = ((1.0 - alpha) * inv);
}