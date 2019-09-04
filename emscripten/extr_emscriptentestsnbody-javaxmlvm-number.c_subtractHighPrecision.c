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
 int /*<<< orphan*/  addHighPrecision (scalar_t__*,size_t,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  simpleAddHighPrecision (scalar_t__*,size_t,int) ; 

void
subtractHighPrecision (U_64 * arg1, IDATA length1, U_64 * arg2, IDATA length2)
{
	/* assumes arg1 > arg2 */
	IDATA index;
	for (index = 0; index < length1; ++index)
		arg1[index] = ~arg1[index];
	simpleAddHighPrecision (arg1, length1, 1);

	while (length2 > 0 && arg2[length2 - 1] == 0)
		--length2;

	addHighPrecision (arg1, length1, arg2, length2);

	for (index = 0; index < length1; ++index)
		arg1[index] = ~arg1[index];
	simpleAddHighPrecision (arg1, length1, 1);
}