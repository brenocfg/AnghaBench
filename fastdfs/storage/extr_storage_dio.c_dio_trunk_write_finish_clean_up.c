#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fast_task_info {scalar_t__ arg; } ;
struct TYPE_5__ {int /*<<< orphan*/  trunk_info; } ;
struct TYPE_6__ {TYPE_1__ upload; } ;
struct TYPE_7__ {int fd; scalar_t__ offset; scalar_t__ start; scalar_t__ end; TYPE_2__ extra_info; int /*<<< orphan*/  filename; } ;
struct TYPE_8__ {TYPE_3__ file_context; } ;
typedef  TYPE_3__ StorageFileContext ;
typedef  TYPE_4__ StorageClientInfo ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int trunk_file_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dio_trunk_write_finish_clean_up(struct fast_task_info *pTask)
{
	StorageFileContext *pFileContext;
	int result;

	pFileContext = &(((StorageClientInfo *)pTask->arg)->file_context);
	if (pFileContext->fd > 0)
	{
		close(pFileContext->fd);
		pFileContext->fd = -1;

		/* if file does not write to the end, 
                   delete the appended contents 
                */
		if (pFileContext->offset > pFileContext->start && \
		    pFileContext->offset < pFileContext->end)
		{
			if ((result=trunk_file_delete(pFileContext->filename, \
			&(pFileContext->extra_info.upload.trunk_info))) != 0)
			{
			}
		}
	}
}