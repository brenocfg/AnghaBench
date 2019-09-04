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
typedef  int U_64 ;
typedef  int IDATA ;

/* Variables and functions */

void simpleShiftLeftHighPrecision (U_64 * arg1, IDATA length, IDATA arg2)
{
	/* assumes length > 0 */
	IDATA index, offset;
	if (arg2 >= 64)
    {
		offset = arg2 >> 6;
		index = length;

		while (--index - offset >= 0)
			arg1[index] = arg1[index - offset];
		do
        {
			arg1[index] = 0;
        }
		while (--index >= 0);

		arg2 &= 0x3F;
    }

	if (arg2 == 0)
		return;
	while (--length > 0)
    {
		arg1[length] = arg1[length] << arg2 | arg1[length - 1] >> (64 - arg2);
    }
	*arg1 <<= arg2;
}