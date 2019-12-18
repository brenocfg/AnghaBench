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
 double fabs (double) ; 
 double log (double) ; 

__attribute__((used)) static double inv_cdf(double u)
{
    const double a[4] = { 2.50662823884,
                         -18.61500062529,
                          41.39119773534,
                         -25.44106049637};

    const double b[4] = {-8.47351093090,
                          23.08336743743,
                         -21.06224101826,
                           3.13082909833};

    const double c[9] = {0.3374754822726147,
                          0.9761690190917186,
                          0.1607979714918209,
                          0.0276438810333863,
                          0.0038405729373609,
                          0.0003951896511919,
                          0.0000321767881768,
                          0.0000002888167364,
                          0.0000003960315187};

    double r;
    double x = u - 0.5;

    // Beasley-Springer
     if (fabs(x) < 0.42) {

        double y = x * x;
        r        = x * (((a[3]*y+a[2])*y+a[1])*y+a[0]) /
                        ((((b[3]*y+b[2])*y+b[1])*y+b[0])*y+1.0);
    }
    else {// Moro
        r = u;
        if (x > 0.0)
            r = 1.0 - u;
        r = log(-log(r));
        r = c[0] + r*(c[1]+r*(c[2]+r*(c[3]+r*(c[4]+r*(c[5]+r*(c[6]+
                                                        r*(c[7]+r*c[8])))))));
        if (x < 0.0)
            r = -r;
    }

    return r;
}