#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  group_name; } ;
struct TYPE_5__ {int count; TYPE_2__** sorted_groups; } ;
typedef  TYPE_1__ FDFSGroups ;
typedef  TYPE_2__ FDFSGroupInfo ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tracker_mem_insert_into_sorted_groups(FDFSGroups *pGroups, \
		FDFSGroupInfo *pTargetGroup)
{
	FDFSGroupInfo **ppGroup;
	FDFSGroupInfo **ppEnd;

	ppEnd = pGroups->sorted_groups + pGroups->count;
	for (ppGroup=ppEnd; ppGroup > pGroups->sorted_groups; ppGroup--)
	{
		if (strcmp(pTargetGroup->group_name, \
			   (*(ppGroup-1))->group_name) > 0)
		{
			*ppGroup = pTargetGroup;
			return;
		}
		else
		{
			*ppGroup = *(ppGroup-1);
		}
	}

	*ppGroup = pTargetGroup;
}