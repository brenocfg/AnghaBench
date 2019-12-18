#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct fast_task_info {int length; char* data; scalar_t__ arg; } ;
struct TYPE_14__ {TYPE_8__* connections; } ;
typedef  TYPE_4__ TrackerServerInfo ;
typedef  int /*<<< orphan*/  TrackerHeader ;
struct TYPE_11__ {scalar_t__ tracker_leader; } ;
struct TYPE_15__ {TYPE_3__* pGroup; TYPE_2__* pStorage; TYPE_1__ chg_count; } ;
typedef  TYPE_5__ TrackerClientInfo ;
struct TYPE_19__ {int leader_index; TYPE_4__* servers; } ;
struct TYPE_18__ {char* ip_addr; int /*<<< orphan*/  port; } ;
struct TYPE_17__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  id; int /*<<< orphan*/  status; } ;
struct TYPE_16__ {char* id; int /*<<< orphan*/  status; } ;
struct TYPE_13__ {scalar_t__ trunk_chg_count; scalar_t__ chg_count; int count; int /*<<< orphan*/  storage_port; TYPE_6__** sorted_servers; TYPE_6__* pTrunkServer; } ;
struct TYPE_12__ {scalar_t__ trunk_chg_count; scalar_t__ chg_count; } ;
typedef  TYPE_6__ FDFSStorageDetail ;
typedef  TYPE_7__ FDFSStorageBrief ;
typedef  TYPE_8__ ConnectionInfo ;

/* Variables and functions */
 char FDFS_CHANGE_FLAG_GROUP_SERVER ; 
 char FDFS_CHANGE_FLAG_TRACKER_LEADER ; 
 char FDFS_CHANGE_FLAG_TRUNK_SERVER ; 
 char* FDFS_CURRENT_IP_ADDR (TYPE_6__*) ; 
 int /*<<< orphan*/  FDFS_STORAGE_ID_MAX_SIZE ; 
 int /*<<< orphan*/  IP_ADDRESS_SIZE ; 
 scalar_t__ g_if_leader_self ; 
 scalar_t__ g_tracker_leader_chg_count ; 
 TYPE_9__ g_tracker_servers ; 
 int /*<<< orphan*/  int2buff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int tracker_check_and_sync(struct fast_task_info *pTask, \
			const int status)
{
	FDFSStorageDetail **ppServer;
	FDFSStorageDetail **ppEnd;
	FDFSStorageDetail *pServer;
	FDFSStorageBrief *pDestServer;
	TrackerClientInfo *pClientInfo;
	char *pFlags;
	char *p;

	pClientInfo = (TrackerClientInfo *)pTask->arg;
	if (status != 0 || pClientInfo->pGroup == NULL)
	{
		pTask->length = sizeof(TrackerHeader);
		return status;
	}
	
	p = pTask->data + sizeof(TrackerHeader);
	pFlags = p++;
	*pFlags = 0;
	if (g_if_leader_self)
	{
	if (pClientInfo->chg_count.tracker_leader != g_tracker_leader_chg_count)
	{
		int leader_index;

		*pFlags |= FDFS_CHANGE_FLAG_TRACKER_LEADER;

		pDestServer = (FDFSStorageBrief *)p;
		memset(p, 0, sizeof(FDFSStorageBrief));

		leader_index = g_tracker_servers.leader_index;
		if (leader_index >= 0)
		{
			TrackerServerInfo *pTServer;
			ConnectionInfo *conn;
			pTServer = g_tracker_servers.servers + leader_index;
            conn = pTServer->connections;
			snprintf(pDestServer->id, FDFS_STORAGE_ID_MAX_SIZE,
				"%s", conn->ip_addr);
			memcpy(pDestServer->ip_addr, conn->ip_addr,
				IP_ADDRESS_SIZE);
			int2buff(conn->port, pDestServer->port);
		}
		pDestServer++;

		pClientInfo->chg_count.tracker_leader = \
				g_tracker_leader_chg_count;
		p = (char *)pDestServer;
	}

	if (pClientInfo->pStorage->trunk_chg_count != \
		pClientInfo->pGroup->trunk_chg_count)
	{
		*pFlags |= FDFS_CHANGE_FLAG_TRUNK_SERVER;

		pDestServer = (FDFSStorageBrief *)p;
		memset(p, 0, sizeof(FDFSStorageBrief));

		pServer = pClientInfo->pGroup->pTrunkServer;
		if (pServer != NULL)
		{
			pDestServer->status = pServer->status;
			memcpy(pDestServer->id, pServer->id,
				FDFS_STORAGE_ID_MAX_SIZE);
			memcpy(pDestServer->ip_addr, FDFS_CURRENT_IP_ADDR(pServer),
				IP_ADDRESS_SIZE);
			int2buff(pClientInfo->pGroup->storage_port,
				pDestServer->port);
		}
		pDestServer++;

		pClientInfo->pStorage->trunk_chg_count = \
			pClientInfo->pGroup->trunk_chg_count;
		p = (char *)pDestServer;
	}

	if (pClientInfo->pStorage->chg_count != pClientInfo->pGroup->chg_count)
	{
		*pFlags |= FDFS_CHANGE_FLAG_GROUP_SERVER;

		pDestServer = (FDFSStorageBrief *)p;
		ppEnd = pClientInfo->pGroup->sorted_servers + \
				pClientInfo->pGroup->count;
		for (ppServer=pClientInfo->pGroup->sorted_servers; \
			ppServer<ppEnd; ppServer++)
		{
			pDestServer->status = (*ppServer)->status;
			memcpy(pDestServer->id, (*ppServer)->id,
				FDFS_STORAGE_ID_MAX_SIZE);
			memcpy(pDestServer->ip_addr, FDFS_CURRENT_IP_ADDR(*ppServer),
				IP_ADDRESS_SIZE);
			int2buff(pClientInfo->pGroup->storage_port,
				pDestServer->port);
			pDestServer++;
		}

		pClientInfo->pStorage->chg_count = \
			pClientInfo->pGroup->chg_count;
		p = (char *)pDestServer;
	}
	}

	pTask->length = p - pTask->data;
	return status;
}