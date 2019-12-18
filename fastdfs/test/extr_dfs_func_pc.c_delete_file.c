#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ip_addr; } ;
typedef  TYPE_1__ ConnectionInfo ;

/* Variables and functions */
 TYPE_1__* getConnectedStorageServer (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  pTrackerServer ; 
 int storage_delete_file1 (int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int tracker_query_storage_update1 (int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 

int delete_file(const char *file_id, char *storage_ip)
{
	int result;
	ConnectionInfo storageServer;
	ConnectionInfo *pStorageServer;

	if ((result=tracker_query_storage_update1(pTrackerServer, 
			&storageServer, file_id)) != 0)
	{
		return result;
	}

	if ((pStorageServer=getConnectedStorageServer(&storageServer, 
			&result)) == NULL)
	{
		return result;
	}

	strcpy(storage_ip, storageServer.ip_addr);
	result = storage_delete_file1(pTrackerServer, pStorageServer, file_id);

	return result;
}