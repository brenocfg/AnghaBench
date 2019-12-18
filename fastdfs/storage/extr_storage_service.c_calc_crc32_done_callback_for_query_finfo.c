#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fast_task_info {int length; scalar_t__ data; scalar_t__ arg; } ;
struct TYPE_4__ {int status; int /*<<< orphan*/  pkg_len; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ TrackerHeader ;
struct TYPE_5__ {int /*<<< orphan*/  crc32; } ;
struct TYPE_6__ {int total_length; scalar_t__ total_offset; scalar_t__ extra_arg; TYPE_2__ file_context; } ;
typedef  int /*<<< orphan*/  StorageFileInfoForCRC32 ;
typedef  TYPE_2__ StorageFileContext ;
typedef  TYPE_3__ StorageClientInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_LOG_ACTION_QUERY_FILE ; 
 int /*<<< orphan*/  STORAGE_ACCESS_LOG (struct fast_task_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STORAGE_PROTO_CMD_RESP ; 
 int /*<<< orphan*/  fast_mblock_free_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finfo_for_crc32_allocator ; 
 int /*<<< orphan*/  long2buff (int,int /*<<< orphan*/ ) ; 
 int query_file_info_response (struct fast_task_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storage_nio_notify (struct fast_task_info*) ; 

__attribute__((used)) static void calc_crc32_done_callback_for_query_finfo(
        struct fast_task_info *pTask, const int err_no)
{
	StorageClientInfo *pClientInfo;
    StorageFileInfoForCRC32 *crc32_file_info;
	StorageFileContext *pFileContext;
	TrackerHeader *pHeader;
	int result;

	pClientInfo = (StorageClientInfo *)pTask->arg;
	pFileContext =  &(pClientInfo->file_context);
    crc32_file_info = (StorageFileInfoForCRC32 *)pClientInfo->extra_arg;

	if (err_no == 0)
	{
        result = query_file_info_response(pTask, crc32_file_info,
                pFileContext->crc32);
	}
	else
	{
		result = err_no;
        pClientInfo->total_length = sizeof(TrackerHeader);
	}

    fast_mblock_free_object(&finfo_for_crc32_allocator, crc32_file_info);

	pClientInfo->total_offset = 0;
	pTask->length = pClientInfo->total_length;

	pHeader = (TrackerHeader *)pTask->data;
	pHeader->status = result;
	pHeader->cmd = STORAGE_PROTO_CMD_RESP;
	long2buff(pTask->length - sizeof(TrackerHeader), pHeader->pkg_len);

    STORAGE_ACCESS_LOG(pTask, ACCESS_LOG_ACTION_QUERY_FILE, result);
	storage_nio_notify(pTask);
}