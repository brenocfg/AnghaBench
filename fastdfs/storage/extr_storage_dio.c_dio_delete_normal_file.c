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
struct TYPE_3__ {int /*<<< orphan*/  (* done_callback ) (struct fast_task_info*,int) ;int /*<<< orphan*/  (* log_callback ) (struct fast_task_info*,int) ;int /*<<< orphan*/  filename; } ;
struct TYPE_4__ {TYPE_1__ file_context; } ;
typedef  TYPE_1__ StorageFileContext ;
typedef  TYPE_2__ StorageClientInfo ;

/* Variables and functions */
 int EACCES ; 
 int errno ; 
 int /*<<< orphan*/  stub1 (struct fast_task_info*,int) ; 
 int /*<<< orphan*/  stub2 (struct fast_task_info*,int) ; 
 scalar_t__ unlink (int /*<<< orphan*/ ) ; 

int dio_delete_normal_file(struct fast_task_info *pTask)
{
	StorageFileContext *pFileContext;
	int result;

	pFileContext = &(((StorageClientInfo *)pTask->arg)->file_context);
	if (unlink(pFileContext->filename) != 0)
	{
		result = errno != 0 ? errno : EACCES;
		pFileContext->log_callback(pTask, result);
	}
	else
	{
		result = 0;
	}

	pFileContext->done_callback(pTask, result);
	return result;
}