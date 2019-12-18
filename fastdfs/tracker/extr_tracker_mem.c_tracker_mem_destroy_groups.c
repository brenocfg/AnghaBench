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
struct TYPE_3__ {int count; int /*<<< orphan*/ ** groups; int /*<<< orphan*/ ** sorted_groups; } ;
typedef  TYPE_1__ FDFSGroups ;
typedef  int /*<<< orphan*/  FDFSGroupInfo ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tracker_mem_free_group (int /*<<< orphan*/ *) ; 
 int tracker_save_sys_files () ; 

__attribute__((used)) static int tracker_mem_destroy_groups(FDFSGroups *pGroups, const bool saveFiles)
{
	FDFSGroupInfo **ppGroup;
	FDFSGroupInfo **ppEnd;
	int result;

	if (pGroups->groups == NULL)
	{
		result = 0;
	}
	else
	{
		if (saveFiles)
		{
			result = tracker_save_sys_files();
		}
		else
		{
			result = 0;
		}

		ppEnd = pGroups->groups + pGroups->count;
		for (ppGroup=pGroups->groups; ppGroup<ppEnd; ppGroup++)
		{
			tracker_mem_free_group(*ppGroup);
		}

		if (pGroups->sorted_groups != NULL)
		{
			free(pGroups->sorted_groups);
			pGroups->sorted_groups = NULL;
		}

		free(pGroups->groups);
		pGroups->groups = NULL;
	}

	return result;
}