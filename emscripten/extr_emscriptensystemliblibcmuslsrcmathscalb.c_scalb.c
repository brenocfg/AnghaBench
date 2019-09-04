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
 int /*<<< orphan*/  isfinite (double) ; 
 scalar_t__ isnan (double) ; 
 double rint (double) ; 
 double scalbn (double,int) ; 

double scalb(double x, double fn)
{
	if (isnan(x) || isnan(fn))
		return x*fn;
	if (!isfinite(fn)) {
		if (fn > 0.0)
			return x*fn;
		else
			return x/(-fn);
	}
	if (rint(fn) != fn) return (fn-fn)/(fn-fn);
	if ( fn > 65000.0) return scalbn(x, 65000);
	if (-fn > 65000.0) return scalbn(x,-65000);
	return scalbn(x,(int)fn);
}