#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_2__ server; } ;
typedef  TYPE_1__ FDFSStorageServer ;

/* Variables and functions */
 int ENOENT ; 
 int g_storage_count ; 
 TYPE_1__* g_storage_servers ; 
 scalar_t__ storage_server_is_myself (TYPE_2__*) ; 
 int trunk_unlink_mark_file (int /*<<< orphan*/ ) ; 

int trunk_unlink_all_mark_files()
{
	FDFSStorageServer *pStorageServer;
	FDFSStorageServer *pServerEnd;
	int result;

	pServerEnd = g_storage_servers + g_storage_count;
	for (pStorageServer=g_storage_servers; pStorageServer<pServerEnd; 
		pStorageServer++)
	{
		if (storage_server_is_myself(&(pStorageServer->server)))
		{
			continue;
		}

		if ((result=trunk_unlink_mark_file( \
			pStorageServer->server.id)) != 0)
		{
			if (result != ENOENT)
			{
				return result;
			}
		}
	}

	return 0;
}