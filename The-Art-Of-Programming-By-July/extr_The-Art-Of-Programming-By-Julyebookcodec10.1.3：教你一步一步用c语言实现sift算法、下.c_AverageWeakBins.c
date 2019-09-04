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

void AverageWeakBins (double* hist, int binCount)  
{  
	// TODO: make some tests what number of passes is the best. (its clear  
	// one is not enough, as we may have something like  
	// ( 0.4, 0.4, 0.3, 0.4, 0.4 ))  
	for (int sn = 0 ; sn < 2 ; ++sn)   
	{  
		double firstE = hist[0];  
		double last = hist[binCount-1];  
		for (int sw = 0 ; sw < binCount ; ++sw)   
		{  
			double cur = hist[sw];  
			double next = (sw == (binCount - 1)) ? firstE : hist[(sw + 1) % binCount];  
			hist[sw] = (last + cur + next) / 3.0;  
			last = cur;  
		}  
	}  
}