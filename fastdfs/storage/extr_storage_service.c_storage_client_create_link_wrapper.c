#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct fast_task_info {scalar_t__ arg; } ;
typedef  int /*<<< orphan*/  TrackerServerInfo ;
struct TYPE_26__ {int /*<<< orphan*/  ip_addr; } ;
struct TYPE_25__ {int src_file_sig_len; char* src_file_sig; int /*<<< orphan*/  src_true_filename; } ;
struct TYPE_19__ {int store_path_index; } ;
struct TYPE_20__ {TYPE_1__ path; } ;
struct TYPE_21__ {TYPE_2__ trunk_info; } ;
struct TYPE_22__ {TYPE_3__ upload; } ;
struct TYPE_23__ {TYPE_4__ extra_info; } ;
struct TYPE_24__ {TYPE_5__ file_context; } ;
typedef  TYPE_5__ StorageFileContext ;
typedef  TYPE_6__ StorageClientInfo ;
typedef  TYPE_7__ SourceFileInfo ;
typedef  TYPE_8__ ConnectionInfo ;

/* Variables and functions */
 int STORAGE_STATUE_DEAL_FILE ; 
 int /*<<< orphan*/  g_group_name ; 
 scalar_t__ is_local_host_ip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int const) ; 
 int storage_client_create_link (TYPE_8__*,TYPE_8__*,char const*,char const*,int const,char const*,int const,char const*,char const*,char const*,char*,int*) ; 
 int storage_create_link_core (struct fast_task_info*,TYPE_7__*,char const*,char const*,int /*<<< orphan*/ ,char const*,char const*,char*,int*,int) ; 
 int storage_split_filename_ex (char const*,int*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  tracker_close_connection (TYPE_8__*) ; 
 int /*<<< orphan*/  tracker_close_connection_ex (TYPE_8__*,int) ; 
 TYPE_8__* tracker_get_connection_r (int /*<<< orphan*/ *,int*) ; 
 TYPE_8__* tracker_make_connection (TYPE_8__*,int*) ; 
 int tracker_query_storage_update (TYPE_8__*,TYPE_8__*,char const*,char const*) ; 

__attribute__((used)) static int storage_client_create_link_wrapper(struct fast_task_info *pTask, \
		const char *master_filename, \
		const char *src_filename, const int src_filename_len, \
		const char *src_file_sig, const int src_file_sig_len, \
		const char *group_name, const char *prefix_name, \
		const char *file_ext_name, \
		char *remote_filename, int *filename_len)
{
	int result;
	int src_store_path_index;
	TrackerServerInfo trackerServer;
	ConnectionInfo *pTracker;
	ConnectionInfo storageServer;
	ConnectionInfo *pStorageServer;
	StorageClientInfo *pClientInfo;
	StorageFileContext *pFileContext;
	SourceFileInfo sourceFileInfo;
	bool bCreateDirectly;

	pClientInfo = (StorageClientInfo *)pTask->arg;
	pFileContext =  &(pClientInfo->file_context);

	if ((pTracker=tracker_get_connection_r(&trackerServer, &result)) == NULL)
	{
		return result;
	}

	if (strcmp(group_name, g_group_name) != 0)
	{
		pStorageServer = NULL;
		bCreateDirectly = false;
	}
	else
	{
		result = tracker_query_storage_update(pTracker, \
				&storageServer, group_name, src_filename);
		if (result != 0)
		{
			tracker_close_connection_ex(pTracker, true);
			return result;
		}

		if (is_local_host_ip(storageServer.ip_addr))
		{
			bCreateDirectly = true;
		}
		else
		{
			bCreateDirectly = false;
		}

		if (!bCreateDirectly)
		{
			if ((pStorageServer=tracker_make_connection(
				&storageServer, &result)) == NULL)
			{
				tracker_close_connection(pTracker);
				return result;
			}
		}
		else
		{
			pStorageServer = NULL;
		}
	}

	if (bCreateDirectly)
	{
		sourceFileInfo.src_file_sig_len = src_file_sig_len;
		memcpy(sourceFileInfo.src_file_sig, src_file_sig, \
			src_file_sig_len);
		*(sourceFileInfo.src_file_sig + src_file_sig_len) = '\0';

		*filename_len = src_filename_len;
		if ((result=storage_split_filename_ex(src_filename, \
			filename_len, sourceFileInfo.src_true_filename, \
			&src_store_path_index)) != 0)
		{
			tracker_close_connection(pTracker);
			return result;
		}

		pFileContext->extra_info.upload.trunk_info.path. \
			store_path_index = src_store_path_index;
		result = storage_create_link_core(pTask, \
			&sourceFileInfo, src_filename, \
			master_filename, strlen(master_filename), \
			prefix_name, file_ext_name, \
			remote_filename, filename_len, false);
		if (result == STORAGE_STATUE_DEAL_FILE)
		{
			result = 0;
		}
	}
	else
	{
		result = storage_client_create_link(pTracker, \
				pStorageServer, master_filename, \
				src_filename, src_filename_len, \
				src_file_sig, src_file_sig_len, \
				group_name, prefix_name, \
				file_ext_name, remote_filename, filename_len);
		if (pStorageServer != NULL)
		{
			tracker_close_connection_ex(pStorageServer, result != 0);
		}
	}

	tracker_close_connection(pTracker);

	return result;
}