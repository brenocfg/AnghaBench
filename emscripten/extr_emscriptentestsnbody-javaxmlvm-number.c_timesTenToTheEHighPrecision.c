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
typedef  int JAVA_INT ;
typedef  int /*<<< orphan*/  IDATA ;

/* Variables and functions */
 int /*<<< orphan*/  TEN_E19 ; 
 int /*<<< orphan*/  TEN_E3 ; 
 int /*<<< orphan*/  TEN_E4 ; 
 int /*<<< orphan*/  TEN_E5 ; 
 int /*<<< orphan*/  TEN_E6 ; 
 int /*<<< orphan*/  TEN_E7 ; 
 int /*<<< orphan*/  TEN_E8 ; 
 int /*<<< orphan*/  TEN_E9 ; 
 scalar_t__ simpleAppendDecimalDigitHighPrecision (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ simpleMultiplyHighPrecision (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ simpleMultiplyHighPrecision64 (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

IDATA timesTenToTheEHighPrecision (U_64 * result, IDATA length, JAVA_INT e)
{
	/* assumes result can hold value */
	U_64 overflow;
	int exp10 = e;

	if (e == 0)
		return length;

	while (exp10 >= 19)
    {
		overflow = simpleMultiplyHighPrecision64 (result, length, TEN_E19);
		if (overflow)
			result[length++] = overflow;
		exp10 -= 19;
    }
	while (exp10 >= 9)
    {
		overflow = simpleMultiplyHighPrecision (result, length, TEN_E9);
		if (overflow)
			result[length++] = overflow;
		exp10 -= 9;
    }
	if (exp10 == 0)
		return length;
	else if (exp10 == 1)
    {
		overflow = simpleAppendDecimalDigitHighPrecision (result, length, 0);
		if (overflow)
			result[length++] = overflow;
    }
	else if (exp10 == 2)
    {
		overflow = simpleAppendDecimalDigitHighPrecision (result, length, 0);
		if (overflow)
			result[length++] = overflow;
		overflow = simpleAppendDecimalDigitHighPrecision (result, length, 0);
		if (overflow)
			result[length++] = overflow;
    }
	else if (exp10 == 3)
    {
		overflow = simpleMultiplyHighPrecision (result, length, TEN_E3);
		if (overflow)
			result[length++] = overflow;
    }
	else if (exp10 == 4)
    {
		overflow = simpleMultiplyHighPrecision (result, length, TEN_E4);
		if (overflow)
			result[length++] = overflow;
    }
	else if (exp10 == 5)
    {
		overflow = simpleMultiplyHighPrecision (result, length, TEN_E5);
		if (overflow)
			result[length++] = overflow;
    }
	else if (exp10 == 6)
    {
		overflow = simpleMultiplyHighPrecision (result, length, TEN_E6);
		if (overflow)
			result[length++] = overflow;
    }
	else if (exp10 == 7)
    {
		overflow = simpleMultiplyHighPrecision (result, length, TEN_E7);
		if (overflow)
			result[length++] = overflow;
    }
	else if (exp10 == 8)
    {
		overflow = simpleMultiplyHighPrecision (result, length, TEN_E8);
		if (overflow)
			result[length++] = overflow;
    }
	return length;
}