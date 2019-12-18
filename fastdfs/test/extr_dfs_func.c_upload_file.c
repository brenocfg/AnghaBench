#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ip_addr; } ;
typedef  TYPE_1__ ConnectionInfo ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int /*<<< orphan*/  FDFS_GROUP_NAME_MAX_LEN ; 
 scalar_t__ errno ; 
 int storage_upload_by_filebuff1 (TYPE_1__*,TYPE_1__*,int,char const*,int const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracker_close_connection (TYPE_1__*) ; 
 int /*<<< orphan*/  tracker_close_connection_ex (TYPE_1__*,int) ; 
 TYPE_1__* tracker_get_connection () ; 
 TYPE_1__* tracker_make_connection (TYPE_1__*,int*) ; 
 int tracker_query_storage_store (TYPE_1__*,TYPE_1__*,char*,int*) ; 

int upload_file(const char *file_buff, const int file_size, char *file_id, char *storage_ip)
{
	int result;
	int store_path_index;
	char group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
	ConnectionInfo *pTrackerServer;
	ConnectionInfo *pStorageServer;
	ConnectionInfo storageServer;

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL)
	{
		return errno != 0 ? errno : ECONNREFUSED;
	}

	*group_name = '\0';
	if ((result=tracker_query_storage_store(pTrackerServer, &storageServer,
			 group_name, &store_path_index)) != 0)
	{
		tracker_close_connection_ex(pTrackerServer, true);
		return result;
	}

	if ((pStorageServer=tracker_make_connection(&storageServer, &result)) \
			 == NULL)
	{
		tracker_close_connection(pTrackerServer);
		return result;
	}

	strcpy(storage_ip, storageServer.ip_addr);
	result = storage_upload_by_filebuff1(pTrackerServer, pStorageServer, 
		store_path_index, file_buff, file_size, NULL, NULL, 0, "", file_id);

	tracker_close_connection(pTrackerServer);
	tracker_close_connection(pStorageServer);

	return result;
}