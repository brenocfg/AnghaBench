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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  DYN_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dyn_value_list ; 

void FreeDynList()
{
	UINT i;
	if (g_dyn_value_list == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(g_dyn_value_list);i++)
	{
		DYN_VALUE *d = LIST_DATA(g_dyn_value_list, i);

		Free(d);
	}

	ReleaseList(g_dyn_value_list);

	g_dyn_value_list = NULL;
}