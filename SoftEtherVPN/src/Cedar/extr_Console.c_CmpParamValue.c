#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ PARAM_VALUE ;

/* Variables and functions */
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CmpParamValue(void *p1, void *p2)
{
	PARAM_VALUE *v1, *v2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	v1 = *(PARAM_VALUE **)p1;
	v2 = *(PARAM_VALUE **)p2;
	if (v1 == NULL || v2 == NULL)
	{
		return 0;
	}

	if (IsEmptyStr(v1->Name) && IsEmptyStr(v2->Name))
	{
		return 0;
	}
	return StrCmpi(v1->Name, v2->Name);
}