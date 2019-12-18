#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int count; TYPE_1__** groups; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pTrunkServer; } ;
typedef  TYPE_1__ FDFSGroupInfo ;

/* Variables and functions */
 TYPE_3__ g_groups ; 
 scalar_t__ g_if_leader_self ; 
 scalar_t__ g_if_use_trunk_file ; 
 int /*<<< orphan*/  g_trunk_server_chg_count ; 
 int /*<<< orphan*/  mem_thread_lock ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracker_mem_find_trunk_server (TYPE_1__*,int) ; 

void tracker_mem_find_trunk_servers()
{
	FDFSGroupInfo **ppGroup;
	FDFSGroupInfo **ppGroupEnd;

	if (!(g_if_leader_self && g_if_use_trunk_file))
	{
		return;
	}

	pthread_mutex_lock(&mem_thread_lock);
	ppGroupEnd = g_groups.groups + g_groups.count;
	for (ppGroup=g_groups.groups; ppGroup<ppGroupEnd; ppGroup++)
	{
		if ((*ppGroup)->pTrunkServer == NULL)
		{
			tracker_mem_find_trunk_server(*ppGroup, true);
		}
	}
	g_trunk_server_chg_count++;
	pthread_mutex_unlock(&mem_thread_lock);
}