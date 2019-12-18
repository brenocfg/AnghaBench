#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_3__ {size_t NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;

/* Variables and functions */
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 

bool IsInToken(TOKEN_LIST *t, char *str)
{
	UINT i;
	// Validate arguments
	if (t == NULL || str == NULL)
	{
		return false;
	}

	for (i = 0;i < t->NumTokens;i++)
	{
		if (StrCmpi(t->Token[i], str) == 0)
		{
			return true;
		}
	}

	return false;
}