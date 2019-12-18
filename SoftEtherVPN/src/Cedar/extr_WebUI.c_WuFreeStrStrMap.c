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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {struct TYPE_3__* Value; struct TYPE_3__* Name; } ;
typedef  TYPE_1__ STRMAP_ENTRY ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 scalar_t__ LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void WuFreeStrStrMap(LIST *params)
{
	UINT i;

	if(params == NULL)
	{
		return;
	}

	for(i=0; i<LIST_NUM(params); i++)
	{
		STRMAP_ENTRY *e = (STRMAP_ENTRY*)LIST_DATA(params, i);
		Free(e->Name);
		Free(e->Value);
		Free(e);
	}
	ReleaseList(params);
}