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
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  pkg_len; int /*<<< orphan*/  cmd; scalar_t__ status; } ;
typedef  TYPE_1__ TrackerHeader ;
struct TYPE_5__ {int open_flags; scalar_t__ fd; int /*<<< orphan*/  crc32; scalar_t__ calc_crc32; int /*<<< orphan*/  done_callback; int /*<<< orphan*/  op; int /*<<< orphan*/  dio_thread_index; scalar_t__ end; scalar_t__ start; scalar_t__ offset; } ;
struct TYPE_6__ {scalar_t__ total_offset; scalar_t__ total_length; int /*<<< orphan*/  clean_func; int /*<<< orphan*/  deal_func; TYPE_2__ file_context; } ;
typedef  TYPE_2__ StorageFileContext ;
typedef  TYPE_3__ StorageClientInfo ;
typedef  int /*<<< orphan*/  FileDealDoneCallback ;

/* Variables and functions */
 int /*<<< orphan*/  CRC32_XINIT ; 
 int /*<<< orphan*/  FDFS_STORAGE_FILE_OP_READ ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  STORAGE_PROTO_CMD_RESP ; 
 int STORAGE_STATUE_DEAL_FILE ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  dio_read_file ; 
 int /*<<< orphan*/  dio_read_finish_clean_up ; 
 int g_extra_open_file_flags ; 
 int /*<<< orphan*/  long2buff (scalar_t__ const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storage_dio_get_thread_index (struct fast_task_info*,int const,int /*<<< orphan*/ ) ; 
 int storage_dio_queue_push (struct fast_task_info*) ; 

__attribute__((used)) static int storage_read_from_file(struct fast_task_info *pTask, \
		const int64_t file_offset, const int64_t download_bytes, \
		FileDealDoneCallback done_callback, \
		const int store_path_index)
{
	StorageClientInfo *pClientInfo;
	StorageFileContext *pFileContext;
	TrackerHeader *pHeader;
	int result;

	pClientInfo = (StorageClientInfo *)pTask->arg;
	pFileContext =  &(pClientInfo->file_context);

	pClientInfo->deal_func = dio_read_file;
	pClientInfo->clean_func = dio_read_finish_clean_up;
	pClientInfo->total_length = sizeof(TrackerHeader) + download_bytes;
	pClientInfo->total_offset = 0;

	pFileContext->op = FDFS_STORAGE_FILE_OP_READ;
	pFileContext->open_flags = O_RDONLY | g_extra_open_file_flags;
	pFileContext->offset = file_offset;
	pFileContext->start = file_offset;
	pFileContext->end = file_offset + download_bytes;
	pFileContext->dio_thread_index = storage_dio_get_thread_index( \
		pTask, store_path_index, pFileContext->op);
	pFileContext->done_callback = done_callback;

	pTask->length = sizeof(TrackerHeader);

	pHeader = (TrackerHeader *)pTask->data;
	pHeader->status = 0;
	pHeader->cmd = STORAGE_PROTO_CMD_RESP;
	long2buff(download_bytes, pHeader->pkg_len);

	if (pFileContext->calc_crc32)
	{
		pFileContext->crc32 = CRC32_XINIT;
	}
	if ((result=storage_dio_queue_push(pTask)) != 0)
	{
		if (pFileContext->fd >= 0)
		{
			close(pFileContext->fd);
		}
		return result;
	}

	return STORAGE_STATUE_DEAL_FILE;
}