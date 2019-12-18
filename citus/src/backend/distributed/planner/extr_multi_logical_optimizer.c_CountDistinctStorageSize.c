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
 double log (int) ; 
 double pow (double,int) ; 
 scalar_t__ rint (double) ; 

__attribute__((used)) static int
CountDistinctStorageSize(double approximationErrorRate)
{
	double desiredStorageSize = pow((1.04 / approximationErrorRate), 2);
	double logOfDesiredStorageSize = log(desiredStorageSize) / log(2);

	/* keep log2(storage size) inside allowed range */
	int logOfStorageSize = (int) rint(logOfDesiredStorageSize);
	if (logOfStorageSize < 4)
	{
		logOfStorageSize = 4;
	}
	else if (logOfStorageSize > 17)
	{
		logOfStorageSize = 17;
	}

	return logOfStorageSize;
}