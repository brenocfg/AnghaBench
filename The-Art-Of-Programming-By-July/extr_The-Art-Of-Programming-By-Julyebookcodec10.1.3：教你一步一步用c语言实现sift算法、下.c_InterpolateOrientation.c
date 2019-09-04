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

bool InterpolateOrientation (double left, double middle,double right, double *degreeCorrection, double *peakValue)  
{  
	double a = ((left + right) - 2.0 * middle) / 2.0;   //抛物线捏合系数a  
	// degreeCorrection = peakValue = Double.NaN;  

	// Not a parabol  
	if (a == 0.0)  
		return false;  
	double c = (((left - middle) / a) - 1.0) / 2.0;  
	double b = middle - c * c * a;  
	if (c < -0.5 || c > 0.5)  
		return false;  
	*degreeCorrection = c;  
	*peakValue = b;  
	return true;  
}