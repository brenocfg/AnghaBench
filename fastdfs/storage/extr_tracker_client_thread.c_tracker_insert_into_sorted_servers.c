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
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ server; } ;
typedef  TYPE_2__ FDFSStorageServer ;

/* Variables and functions */
 TYPE_2__** g_sorted_storages ; 
 int g_storage_count ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tracker_insert_into_sorted_servers( \
		FDFSStorageServer *pInsertedServer)
{
	FDFSStorageServer **ppServer;
	FDFSStorageServer **ppEnd;
	int nCompare;

	ppEnd = g_sorted_storages + g_storage_count;
	for (ppServer=ppEnd; ppServer > g_sorted_storages; ppServer--)
	{
		nCompare = strcmp(pInsertedServer->server.id, \
			   	(*(ppServer-1))->server.id);
		if (nCompare > 0)
		{
			*ppServer = pInsertedServer;
			return true;
		}
		else if (nCompare < 0)
		{
			*ppServer = *(ppServer-1);
		}
		else  //nCompare == 0
		{
			for (; ppServer < ppEnd; ppServer++) //restore
			{
				*ppServer = *(ppServer+1);
			}
			return false;
		}
	}

	*ppServer = pInsertedServer;
	return true;
}