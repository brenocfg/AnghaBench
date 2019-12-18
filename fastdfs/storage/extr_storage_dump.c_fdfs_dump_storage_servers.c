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
typedef  int /*<<< orphan*/  szLastSyncSrcTimestamp ;
struct TYPE_5__ {char* ip_addr; int status; } ;
struct TYPE_6__ {TYPE_1__ server; int /*<<< orphan*/  last_sync_src_timestamp; } ;
typedef  TYPE_2__ FDFSStorageServer ;

/* Variables and functions */
 char* formatDatetime (int /*<<< orphan*/ ,char*,char*,int) ; 
 TYPE_2__** g_sorted_storages ; 
 int g_storage_count ; 
 TYPE_2__* g_storage_servers ; 
 int snprintf (char*,int const,char*,...) ; 

__attribute__((used)) static int fdfs_dump_storage_servers(char *buff, const int buffSize)
{
	int total_len;
	char szLastSyncSrcTimestamp[32];
	FDFSStorageServer *pServer;
	FDFSStorageServer *pServerEnd;
	FDFSStorageServer **ppServer;
	FDFSStorageServer **ppServerEnd;

	total_len = snprintf(buff, buffSize,
			"\ng_storage_count=%d\n", g_storage_count);
	pServerEnd = g_storage_servers + g_storage_count;
	for (pServer=g_storage_servers; pServer<pServerEnd; pServer++)
	{
		total_len += snprintf(buff + total_len, buffSize - total_len,
			"\t%d. server: %s, status: %d, sync timestamp: %s\n", 
			(int)(pServer - g_storage_servers) + 1, 
			pServer->server.ip_addr, pServer->server.status,
			formatDatetime(pServer->last_sync_src_timestamp, 
				"%Y-%m-%d %H:%M:%S", szLastSyncSrcTimestamp, 
				sizeof(szLastSyncSrcTimestamp)));
	}

	total_len += snprintf(buff + total_len, buffSize - total_len,
			"sorted storage servers:\n");
	ppServerEnd = g_sorted_storages + g_storage_count;
	for (ppServer=g_sorted_storages; ppServer<ppServerEnd; ppServer++)
	{
		total_len += snprintf(buff + total_len, buffSize - total_len,
			"\t%d. server: %s\n", 
			(int)(ppServer - g_sorted_storages) + 1, 
			(*ppServer)->server.ip_addr);
	}

	return total_len;
}