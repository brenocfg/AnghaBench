#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WU_CONTEXT ;
struct TYPE_6__ {int /*<<< orphan*/  PageList; int /*<<< orphan*/  Contexts; scalar_t__ Value; struct TYPE_6__* Name; } ;
typedef  TYPE_1__ WEBUI ;
typedef  scalar_t__ UINT ;
typedef  TYPE_1__ STRMAP_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WuFreeContext (int /*<<< orphan*/ *) ; 

bool WuFreeWebUI(WEBUI *wu)
{
	UINT i;

	if(wu == NULL)
	{
		return false;
	}

	for(i=0; i<LIST_NUM(wu->Contexts); i++)
	{
		STRMAP_ENTRY *se = LIST_DATA(wu->Contexts, i);
		Free(se->Name);
		WuFreeContext((WU_CONTEXT*)se->Value);
		Free(se);
	}
	ReleaseList(wu->Contexts);

	ReleaseList(wu->PageList);
	Free(wu);
	return true;
}