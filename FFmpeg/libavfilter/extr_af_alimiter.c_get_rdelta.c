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
struct TYPE_3__ {scalar_t__ asc_c; double asc_coeff; double asc; scalar_t__ auto_release; } ;
typedef  TYPE_1__ AudioLimiterContext ;

/* Variables and functions */
 double FFMAX (double,double) ; 

__attribute__((used)) static double get_rdelta(AudioLimiterContext *s, double release, int sample_rate,
                         double peak, double limit, double patt, int asc)
{
    double rdelta = (1.0 - patt) / (sample_rate * release);

    if (asc && s->auto_release && s->asc_c > 0) {
        double a_att = limit / (s->asc_coeff * s->asc) * (double)s->asc_c;

        if (a_att > patt) {
            double delta = FFMAX((a_att - patt) / (sample_rate * release), rdelta / 10);

            if (delta < rdelta)
                rdelta = delta;
        }
    }

    return rdelta;
}