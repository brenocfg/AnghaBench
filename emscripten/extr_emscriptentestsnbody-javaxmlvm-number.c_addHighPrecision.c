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
typedef  scalar_t__ IDATA ;

/* Variables and functions */

IDATA addHighPrecision (U_64 * arg1, IDATA length1, U_64 * arg2, IDATA length2)
{

	U_64 temp1, temp2, temp3;     /* temporary variables to help the SH-4, and gcc */
	U_64 carry;
	IDATA index;

	if (length1 == 0 || length2 == 0)
    {
		return 0;
    }
	else if (length1 < length2)
    {
		length2 = length1;
    }

	carry = 0;
	index = 0;
	do
    {
		temp1 = arg1[index];
		temp2 = arg2[index];
		temp3 = temp1 + temp2;
		arg1[index] = temp3 + carry;
		if (arg2[index] < arg1[index])
			carry = 0;
		else if (arg2[index] != arg1[index])
			carry = 1;
    }
	while (++index < length2);
	if (!carry)
		return 0;
	else if (index == length1)
		return 1;

	while (++arg1[index] == 0 && ++index < length1);

	return (IDATA) index == length1;
}