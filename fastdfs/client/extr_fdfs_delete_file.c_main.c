#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  file_id ;
struct TYPE_2__ {int /*<<< orphan*/  log_level; } ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int /*<<< orphan*/  LOG_ERR ; 
 char* STRERROR (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fdfs_client_destroy () ; 
 int fdfs_client_init (char*) ; 
 TYPE_1__ g_log_context ; 
 int /*<<< orphan*/  ignore_signal_pipe () ; 
 int /*<<< orphan*/  log_init () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int storage_delete_file1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tracker_close_connection_ex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tracker_get_connection () ; 

int main(int argc, char *argv[])
{
	char *conf_filename;
	ConnectionInfo *pTrackerServer;
	int result;
	char file_id[128];
	
	if (argc < 3)
	{
		printf("Usage: %s <config_file> <file_id>\n", argv[0]);
		return 1;
	}

	log_init();
	g_log_context.log_level = LOG_ERR;
	ignore_signal_pipe();

	conf_filename = argv[1];
	if ((result=fdfs_client_init(conf_filename)) != 0)
	{
		return result;
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL)
	{
		fdfs_client_destroy();
		return errno != 0 ? errno : ECONNREFUSED;
	}

	snprintf(file_id, sizeof(file_id), "%s", argv[2]);
	if ((result=storage_delete_file1(pTrackerServer, NULL, file_id)) != 0)
	{
		printf("delete file fail, " \
			"error no: %d, error info: %s\n", \
			result, STRERROR(result));
	}

	tracker_close_connection_ex(pTrackerServer, true);
	fdfs_client_destroy();

	return result;
}