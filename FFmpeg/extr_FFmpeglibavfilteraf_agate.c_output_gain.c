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
 double FFMAX (double,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_FAKE_INFINITY (double) ; 
 int /*<<< orphan*/  exp (double) ; 
 double hermite_interpolation (double,double,double,double,double,double,int) ; 
 double log (double) ; 

__attribute__((used)) static double output_gain(double lin_slope, double ratio, double thres,
                          double knee, double knee_start, double knee_stop,
                          double range, int mode)
{
    double slope = log(lin_slope);
    double tratio = ratio;
    double gain = 0.;
    double delta = 0.;

    if (IS_FAKE_INFINITY(ratio))
        tratio = 1000.;
    gain = (slope - thres) * tratio + thres;
    delta = tratio;

    if (mode) {
        if (knee > 1. && slope < knee_stop)
            gain = hermite_interpolation(slope, knee_stop, knee_start, ((knee_stop - thres) * tratio  + thres), knee_start, delta, 1.);
    } else {
        if (knee > 1. && slope > knee_start)
            gain = hermite_interpolation(slope, knee_start, knee_stop, ((knee_start - thres) * tratio  + thres), knee_stop, delta, 1.);
    }
    return FFMAX(range, exp(gain - slope));
}