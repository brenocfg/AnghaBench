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
 scalar_t__ IS_FAKE_INFINITY (double) ; 
 double exp (double) ; 
 double hermite_interpolation (double,double,double,double,double,double,double) ; 
 double log (double) ; 

__attribute__((used)) static double output_gain(double lin_slope, double ratio, double thres,
                          double knee, double knee_start, double knee_stop,
                          double compressed_knee_start,
                          double compressed_knee_stop,
                          int detection, int mode)
{
    double slope = log(lin_slope);
    double gain = 0.0;
    double delta = 0.0;

    if (detection)
        slope *= 0.5;

    if (IS_FAKE_INFINITY(ratio)) {
        gain = thres;
        delta = 0.0;
    } else {
        gain = (slope - thres) / ratio + thres;
        delta = 1.0 / ratio;
    }

    if (mode) {
        if (knee > 1.0 && slope > knee_start)
            gain = hermite_interpolation(slope, knee_stop, knee_start,
                                         knee_stop, compressed_knee_start,
                                         1.0, delta);
    } else {
        if (knee > 1.0 && slope < knee_stop)
            gain = hermite_interpolation(slope, knee_start, knee_stop,
                                         knee_start, compressed_knee_stop,
                                         1.0, delta);
    }

    return exp(gain - slope);
}