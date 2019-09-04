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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 scalar_t__ UniStrCmpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool IsInListUniStr(LIST *o, wchar_t *str)
{
	UINT i;
	// Validate arguments
	if (o == NULL || str == NULL)
	{
		return false;
	}

	for (i = 0; i < LIST_NUM(o); i++)
	{
		wchar_t *s = LIST_DATA(o, i);

		if (UniStrCmpi(s, str) == 0)
		{
			return true;
		}
	}

	return false;
}