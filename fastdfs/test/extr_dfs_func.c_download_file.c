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
typedef  int int64_t ;
struct TYPE_11__ {int /*<<< orphan*/  ip_addr; } ;
typedef  TYPE_1__ ConnectionInfo ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int /*<<< orphan*/  downloadFileCallback ; 
 scalar_t__ errno ; 
 int storage_download_file_ex1 (TYPE_1__*,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracker_close_connection (TYPE_1__*) ; 
 int /*<<< orphan*/  tracker_close_connection_ex (TYPE_1__*,int) ; 
 TYPE_1__* tracker_get_connection () ; 
 TYPE_1__* tracker_make_connection (TYPE_1__*,int*) ; 
 int tracker_query_storage_fetch1 (TYPE_1__*,TYPE_1__*,char const*) ; 

int download_file(const char *file_id, int *file_size, char *storage_ip)
{
	int result;
	ConnectionInfo *pTrackerServer;
	ConnectionInfo *pStorageServer;
	ConnectionInfo storageServer;
	int64_t file_bytes;

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL)
	{
		return errno != 0 ? errno : ECONNREFUSED;
	}

	if ((result=tracker_query_storage_fetch1(pTrackerServer, \
			&storageServer, file_id)) != 0)
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
	result = storage_download_file_ex1(pTrackerServer, pStorageServer, \
		file_id, 0, 0, downloadFileCallback, NULL, &file_bytes);
	*file_size = file_bytes;

	tracker_close_connection(pTrackerServer);
	tracker_close_connection(pStorageServer);

	return result;
}