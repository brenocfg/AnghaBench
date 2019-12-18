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
 float FFMAX3 (float,float,float) ; 
 float FFMIN3 (float,float,float) ; 
 float hfun (int,float,float,float) ; 

__attribute__((used)) static void preservel(float *r, float *g, float *b, float l)
{
    float max = FFMAX3(*r, *g, *b);
    float min = FFMIN3(*r, *g, *b);
    float h, s;

    l *= 0.5;

    if (*r == *g && *g == *b) {
        h = 0.;
    } else if (max == *r) {
        h = 60. * (0. + (*g - *b) / (max - min));
    } else if (max == *g) {
        h = 60. * (2. + (*b - *r) / (max - min));
    } else if (max == *b) {
        h = 60. * (4. + (*r - *g) / (max - min));
    } else {
        h = 0.;
    }
    if (h < 0.)
        h += 360.;

    if (max == 0. || min == 1.) {
        s = 0.;
    } else {
        s = (max - min) / (1. - FFABS(2. * l - 1));
    }

    *r = hfun(0, h, s, l);
    *g = hfun(8, h, s, l);
    *b = hfun(4, h, s, l);
}