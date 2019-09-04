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
typedef  int IDATA ;

/* Variables and functions */

IDATA
simpleAddHighPrecision (U_64 * arg1, IDATA length, U_64 arg2)
{
	/* assumes length > 0 */
	IDATA index = 1;

	*arg1 += arg2;
	if (arg2 <= *arg1)
		return 0;
	else if (length == 1)
		return 1;

	while (++arg1[index] == 0 && ++index < length);

	return (IDATA) index == length;
}