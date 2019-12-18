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
typedef  int /*<<< orphan*/ **** FDFSGroupInfo ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ******) ; 

__attribute__((used)) static void tracker_mem_free_groups(FDFSGroupInfo **groups, const int count)
{
	FDFSGroupInfo **ppGroup;
	FDFSGroupInfo **ppGroupEnd;

	ppGroupEnd = groups + count;
	for (ppGroup=groups; ppGroup<ppGroupEnd; ppGroup++)
	{
		if (*ppGroup != NULL)
		{
			free(*ppGroup);
		}
	}

	free(groups);
}