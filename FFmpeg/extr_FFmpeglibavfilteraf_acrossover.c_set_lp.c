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
struct TYPE_3__ {double a2; double a0; double a1; int b1; int b2; } ;
typedef  TYPE_1__ BiquadContext ;

/* Variables and functions */
 double M_PI ; 
 double cos (double) ; 
 double sin (double) ; 

__attribute__((used)) static void set_lp(BiquadContext *b, float fc, float q, float sr)
{
    double omega = (2.0 * M_PI * fc / sr);
    double sn = sin(omega);
    double cs = cos(omega);
    double alpha = (sn / (2 * q));
    double inv = (1.0 / (1.0 + alpha));

    b->a2 = b->a0 = (inv * (1.0 - cs) * 0.5);
    b->a1 = b->a0 + b->a0;
    b->b1 = -2. * cs * inv;
    b->b2 = (1. - alpha) * inv;
}