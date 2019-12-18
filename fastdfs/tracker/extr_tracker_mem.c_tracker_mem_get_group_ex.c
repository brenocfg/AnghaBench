#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  target_groups ;
struct TYPE_8__ {int /*<<< orphan*/  group_name; } ;
struct TYPE_7__ {int /*<<< orphan*/  count; int /*<<< orphan*/  sorted_groups; } ;
typedef  TYPE_1__ FDFSGroups ;
typedef  TYPE_2__ FDFSGroupInfo ;

/* Variables and functions */
 scalar_t__ bsearch (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tracker_mem_cmp_by_group_name ; 

FDFSGroupInfo *tracker_mem_get_group_ex(FDFSGroups *pGroups, \
		const char *group_name)
{
	FDFSGroupInfo target_groups;
	FDFSGroupInfo *pTargetGroups;
	FDFSGroupInfo **ppGroup;

	memset(&target_groups, 0, sizeof(target_groups));
	strcpy(target_groups.group_name, group_name);
	pTargetGroups = &target_groups;
	ppGroup = (FDFSGroupInfo **)bsearch(&pTargetGroups, \
			pGroups->sorted_groups, \
			pGroups->count, sizeof(FDFSGroupInfo *), \
			tracker_mem_cmp_by_group_name);

	if (ppGroup != NULL)
	{
		return *ppGroup;
	}
	else
	{
		return NULL;
	}
}