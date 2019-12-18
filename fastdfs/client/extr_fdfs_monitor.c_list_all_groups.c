#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  group_name; } ;
typedef  TYPE_1__ FDFSGroupStat ;

/* Variables and functions */
 int FDFS_MAX_GROUPS ; 
 int /*<<< orphan*/  fdfs_client_destroy () ; 
 int /*<<< orphan*/  list_storages (TYPE_1__*) ; 
 int /*<<< orphan*/  pTrackerServer ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tracker_close_all_connections () ; 
 int tracker_list_groups (int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 

__attribute__((used)) static int list_all_groups(const char *group_name)
{
	int result;
	int group_count;
	FDFSGroupStat group_stats[FDFS_MAX_GROUPS];
	FDFSGroupStat *pGroupStat;
	FDFSGroupStat *pGroupEnd;
	int i;

	result = tracker_list_groups(pTrackerServer, \
		group_stats, FDFS_MAX_GROUPS, \
		&group_count);
	if (result != 0)
	{
		tracker_close_all_connections();
		fdfs_client_destroy();
		return result;
	}

	pGroupEnd = group_stats + group_count;
	if (group_name == NULL)
	{
		printf("group count: %d\n", group_count);
		i = 0;
		for (pGroupStat=group_stats; pGroupStat<pGroupEnd; \
			pGroupStat++)
		{
			printf( "\nGroup %d:\n", ++i);
			list_storages(pGroupStat);
		}
	}
	else
	{
		for (pGroupStat=group_stats; pGroupStat<pGroupEnd; \
			pGroupStat++)
		{
			if (strcmp(pGroupStat->group_name, group_name) == 0)
			{
				list_storages(pGroupStat);
				break;
			}
		}
	}

	return 0;
}