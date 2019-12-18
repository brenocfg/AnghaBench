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
struct TYPE_3__ {int a0; double a1; double a2; double b1; double b2; } ;
typedef  TYPE_1__ BiquadCoeffs ;

/* Variables and functions */
 double M_PI ; 
 double cos (double) ; 
 double hypot (int,double) ; 
 double sin (double) ; 

__attribute__((used)) static double freq_gain(BiquadCoeffs *c, double freq, double sr)
{
    double zr, zi;

    freq *= 2.0 * M_PI / sr;
    zr = cos(freq);
    zi = -sin(freq);

    /* |(a0 + a1*z + a2*z^2)/(1 + b1*z + b2*z^2)| */
    return hypot(c->a0 + c->a1*zr + c->a2*(zr*zr-zi*zi), c->a1*zi + 2*c->a2*zr*zi) /
           hypot(1 + c->b1*zr + c->b2*(zr*zr-zi*zi), c->b1*zi + 2*c->b2*zr*zi);
}