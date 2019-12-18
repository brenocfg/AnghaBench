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
struct TYPE_3__ {int x0; int xscale; int y0; int yscale; double dmax; double const angle; } ;
typedef  TYPE_1__ VignetteContext ;

/* Variables and functions */
 double cos (double const) ; 
 double hypot (int const,int const) ; 

__attribute__((used)) static double get_natural_factor(const VignetteContext *s, int x, int y)
{
    const int xx = (x - s->x0) * s->xscale;
    const int yy = (y - s->y0) * s->yscale;
    const double dnorm = hypot(xx, yy) / s->dmax;
    if (dnorm > 1) {
        return 0;
    } else {
        const double c = cos(s->angle * dnorm);
        return (c*c)*(c*c); // do not remove braces, it helps compilers
    }
}