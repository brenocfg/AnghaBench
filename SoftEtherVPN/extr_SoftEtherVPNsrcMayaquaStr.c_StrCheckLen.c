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
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_STRCHECK_COUNT ; 

bool StrCheckLen(char *str, UINT len)
{
	UINT count = 0;
	UINT i;
	// Validate arguments
	if (str == NULL)
	{
		return false;
	}

	// KS
	KS_INC(KS_STRCHECK_COUNT);

	for (i = 0;;i++)
	{
		if (str[i] == '\0')
		{
			return true;
		}
		count++;
		if (count > len)
		{
			return false;
		}
	}
}