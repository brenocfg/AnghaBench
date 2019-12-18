#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  log_level; } ;
struct TYPE_10__ {char* ip_addr; int port; } ;
struct TYPE_9__ {int server_count; int server_index; scalar_t__ servers; } ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int FDFS_STORAGE_ID_MAX_SIZE ; 
 int /*<<< orphan*/  FDFS_TRACKER_SERVER_DEF_PORT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 scalar_t__ RAND_MAX ; 
 char* STRERROR (int) ; 
 int conn_pool_parse_server_info (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fdfs_client_destroy () ; 
 int fdfs_client_init (char*) ; 
 scalar_t__ fdfs_server_contain1 (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_8__ g_log_context ; 
 TYPE_1__ g_tracker_group ; 
 int /*<<< orphan*/  h_errno ; 
 char* hstrerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_signal_pipe () ; 
 int list_all_groups (char*) ; 
 int /*<<< orphan*/  load_log_level_ex (char*) ; 
 int /*<<< orphan*/  log_init () ; 
 TYPE_2__* pTrackerServer ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracker_close_connection_ex (TYPE_2__*,int) ; 
 int tracker_delete_group (TYPE_1__*,char*) ; 
 int tracker_delete_storage (TYPE_1__*,char*,char*) ; 
 TYPE_2__* tracker_get_connection () ; 
 int tracker_set_trunk_server (TYPE_1__*,char*,char*,char*) ; 
 int /*<<< orphan*/  usage (char**) ; 

int main(int argc, char *argv[])
{
	char *conf_filename;
	int result;
	char *op_type;
	char *tracker_server;
	int arg_index;
	char *group_name;

	if (argc < 2)
	{
		usage(argv);
		return 1;
	}

	tracker_server = NULL;
	conf_filename = argv[1];
	arg_index = 2;

	if (arg_index >= argc)
	{
		op_type = "list";
	}
	else
	{
		int len;

		len = strlen(argv[arg_index]); 
		if (len >= 2 && strncmp(argv[arg_index], "-h", 2) == 0)
		{
			if (len == 2)
			{
				arg_index++;
				if (arg_index >= argc)
				{
					usage(argv);
					return 1;
				}

				tracker_server = argv[arg_index++];
			}
			else
			{
				tracker_server = argv[arg_index] + 2;
				arg_index++;
			}

			if (arg_index < argc)
			{
				op_type = argv[arg_index++];
			}
			else
			{
				op_type = "list";
			}
		}
		else
		{
			op_type = argv[arg_index++];
		}
	}

	log_init();
	g_log_context.log_level = LOG_DEBUG;
	ignore_signal_pipe();

	if ((result=fdfs_client_init(conf_filename)) != 0)
	{
		return result;
	}
	load_log_level_ex(conf_filename);

	if (tracker_server == NULL)
	{
		if (g_tracker_group.server_count > 1)
		{
			srand(time(NULL));
			rand();  //discard the first
			g_tracker_group.server_index = (int)( \
				(g_tracker_group.server_count * (double)rand()) \
				/ (double)RAND_MAX);
		}
	}
	else
	{
		int i;
        ConnectionInfo conn;

        if ((result=conn_pool_parse_server_info(tracker_server, &conn,
                        FDFS_TRACKER_SERVER_DEF_PORT)) != 0)
		{
			printf("resolve ip address of tracker server: %s "
				"fail!, error info: %s\n", tracker_server, hstrerror(h_errno));
			return result;
		}

		for (i=0; i<g_tracker_group.server_count; i++)
		{
			if (fdfs_server_contain1(g_tracker_group.servers + i,
					&conn) == 0)
			{
				g_tracker_group.server_index = i;
				break;
			}
		}

		if (i == g_tracker_group.server_count)
		{
			printf("tracker server: %s not exists!\n", tracker_server);
			return 2;
		}
	}

	printf("server_count=%d, server_index=%d\n",
            g_tracker_group.server_count, g_tracker_group.server_index);

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL)
	{
		fdfs_client_destroy();
		return errno != 0 ? errno : ECONNREFUSED;
	}
	printf("\ntracker server is %s:%d\n\n", pTrackerServer->ip_addr, pTrackerServer->port);

	if (arg_index < argc)
	{
		group_name = argv[arg_index++];
	}
	else
	{
		group_name = NULL;
	}

	if (strcmp(op_type, "list") == 0)
	{
		if (group_name == NULL)
		{
			result = list_all_groups(NULL);
		}
		else
		{
			result = list_all_groups(group_name);
		}
	}
	else if (strcmp(op_type, "delete") == 0)
	{
		if (arg_index >= argc)
		{
		if ((result=tracker_delete_group(&g_tracker_group, \
				group_name)) == 0)
		{
			printf("delete group: %s success\n", \
				group_name);
		}
		else
		{
			printf("delete group: %s fail, " \
				"error no: %d, error info: %s\n", \
				group_name, result, STRERROR(result));
		}
		}
        else
        {
		char *storage_id;

		storage_id = argv[arg_index++];
		if ((result=tracker_delete_storage(&g_tracker_group, \
				group_name, storage_id)) == 0)
		{
			printf("delete storage server %s::%s success\n", \
				group_name, storage_id);
		}
		else
		{
			printf("delete storage server %s::%s fail, " \
				"error no: %d, error info: %s\n", \
				group_name, storage_id, \
				result, STRERROR(result));
		}
        }
	}
	else if (strcmp(op_type, "set_trunk_server") == 0)
	{
		char *storage_id;
		char new_trunk_server_id[FDFS_STORAGE_ID_MAX_SIZE];

		if (group_name == NULL)
		{
			usage(argv);
			return 1;
		}
		if (arg_index >= argc)
		{
			storage_id = "";
		}
		else
		{
			storage_id = argv[arg_index++];
		}

		if ((result=tracker_set_trunk_server(&g_tracker_group, \
			group_name, storage_id, new_trunk_server_id)) == 0)
		{
			printf("set trunk server %s::%s success, " \
				"new trunk server: %s\n", group_name, \
				storage_id, new_trunk_server_id);
		}
		else
		{
			printf("set trunk server %s::%s fail, " \
				"error no: %d, error info: %s\n", \
				group_name, storage_id, \
				result, STRERROR(result));
		}
	}
	else
	{
		printf("Invalid command %s\n\n", op_type);
		usage(argv);
	}

	tracker_close_connection_ex(pTrackerServer, true);
	fdfs_client_destroy();
	return 0;
}