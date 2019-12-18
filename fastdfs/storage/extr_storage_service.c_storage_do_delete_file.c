#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fast_task_info {scalar_t__ arg; } ;
struct TYPE_3__ {int fd; int /*<<< orphan*/  done_callback; int /*<<< orphan*/  log_callback; int /*<<< orphan*/  op; int /*<<< orphan*/  dio_thread_index; } ;
struct TYPE_4__ {TYPE_1__ file_context; } ;
typedef  TYPE_1__ StorageFileContext ;
typedef  TYPE_2__ StorageClientInfo ;
typedef  int /*<<< orphan*/  FileDealDoneCallback ;
typedef  int /*<<< orphan*/  DeleteFileLogCallback ;

/* Variables and functions */
 int /*<<< orphan*/  FDFS_STORAGE_FILE_OP_DELETE ; 
 int STORAGE_STATUE_DEAL_FILE ; 
 int /*<<< orphan*/  storage_dio_get_thread_index (struct fast_task_info*,int const,int /*<<< orphan*/ ) ; 
 int storage_dio_queue_push (struct fast_task_info*) ; 

__attribute__((used)) static int storage_do_delete_file(struct fast_task_info *pTask, \
		DeleteFileLogCallback log_callback, \
		FileDealDoneCallback done_callback, \
		const int store_path_index)
{
	StorageClientInfo *pClientInfo;
	StorageFileContext *pFileContext;
	int result;

	pClientInfo = (StorageClientInfo *)pTask->arg;
	pFileContext =  &(pClientInfo->file_context);

	pFileContext->fd = -1;
	pFileContext->op = FDFS_STORAGE_FILE_OP_DELETE;
	pFileContext->dio_thread_index = storage_dio_get_thread_index( \
		pTask, store_path_index, pFileContext->op);
	pFileContext->log_callback = log_callback;
	pFileContext->done_callback = done_callback;

	if ((result=storage_dio_queue_push(pTask)) != 0)
	{
		return result;
	}

	return STORAGE_STATUE_DEAL_FILE;
}