#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* connections; } ;
typedef  TYPE_2__ TrackerServerInfo ;
struct TYPE_6__ {int server_count; int leader_index; TYPE_2__* servers; } ;
struct TYPE_4__ {char* ip_addr; int port; } ;

/* Variables and functions */
 TYPE_3__ g_tracker_group ; 
 int snprintf (char*,int const,char*,int,...) ; 

__attribute__((used)) static int fdfs_dump_tracker_servers(char *buff, const int buffSize)
{
	int total_len;
	TrackerServerInfo *pTrackerServer;
	TrackerServerInfo *pTrackerEnd;

	total_len = snprintf(buff, buffSize, \
		"\ng_tracker_group.server_count=%d, " \
		"g_tracker_group.leader_index=%d\n", \
		g_tracker_group.server_count, \
		g_tracker_group.leader_index);
	if (g_tracker_group.server_count == 0)
	{
		return total_len;
	}

	pTrackerEnd = g_tracker_group.servers + g_tracker_group.server_count;
	for (pTrackerServer=g_tracker_group.servers; \
		pTrackerServer<pTrackerEnd; pTrackerServer++)
	{
		total_len += snprintf(buff + total_len, buffSize - total_len,
			"\t%d. tracker server=%s:%d\n",
			(int)(pTrackerServer - g_tracker_group.servers) + 1,
			pTrackerServer->connections[0].ip_addr,
            pTrackerServer->connections[0].port);
	}

	return total_len;
}