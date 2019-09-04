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
typedef  scalar_t__ U_64 ;
typedef  size_t IDATA ;

/* Variables and functions */

IDATA
compareHighPrecision (U_64 * arg1, IDATA length1, U_64 * arg2, IDATA length2)
{
	while (--length1 >= 0 && arg1[length1] == 0);
	while (--length2 >= 0 && arg2[length2] == 0);

	if (length1 > length2)
		return 1;
	else if (length1 < length2)
		return -1;
	else if (length1 > -1)
    {
		do
        {
			if (arg1[length1] > arg2[length1])
				return 1;
			else if (arg1[length1] < arg2[length1])
				return -1;
        }
		while (--length1 >= 0);
    }

	return 0;
}