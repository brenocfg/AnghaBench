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
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 scalar_t__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 

bool IsInt64InList(LIST *o, UINT64 i)
{
	UINT j;
	// Validate arguments
	if (o == NULL)
	{
		return false;
	}

	for (j = 0;j < LIST_NUM(o);j++)
	{
		UINT64 *p = LIST_DATA(o, j);

		if (*p == i)
		{
			return true;
		}
	}

	return false;
}