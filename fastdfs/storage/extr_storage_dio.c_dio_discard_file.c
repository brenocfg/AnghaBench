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
struct fast_task_info {scalar_t__ length; scalar_t__ arg; } ;
struct TYPE_3__ {scalar_t__ offset; scalar_t__ buff_offset; scalar_t__ end; int /*<<< orphan*/  (* continue_callback ) (struct fast_task_info*) ;int /*<<< orphan*/  (* done_callback ) (struct fast_task_info*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ file_context; } ;
typedef  TYPE_1__ StorageFileContext ;
typedef  TYPE_2__ StorageClientInfo ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct fast_task_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct fast_task_info*) ; 

int dio_discard_file(struct fast_task_info *pTask)
{
	StorageFileContext *pFileContext;

	pFileContext = &(((StorageClientInfo *)pTask->arg)->file_context);
	pFileContext->offset+=pTask->length - pFileContext->buff_offset;
	if (pFileContext->offset >= pFileContext->end)
	{
		pFileContext->done_callback(pTask, 0);
	}
	else
	{
		pFileContext->buff_offset = 0;
        pFileContext->continue_callback(pTask);
	}

	return 0;
}