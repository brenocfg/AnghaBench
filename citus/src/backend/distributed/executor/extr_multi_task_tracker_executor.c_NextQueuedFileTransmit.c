#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ status; } ;
typedef  TYPE_1__ TrackerTaskState ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 scalar_t__ TASK_FILE_TRANSMIT_QUEUED ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_term (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TrackerTaskState *
NextQueuedFileTransmit(HTAB *taskStateHash)
{
	HASH_SEQ_STATUS status;
	TrackerTaskState *taskState = NULL;
	hash_seq_init(&status, taskStateHash);

	taskState = (TrackerTaskState *) hash_seq_search(&status);
	while (taskState != NULL)
	{
		if (taskState->status == TASK_FILE_TRANSMIT_QUEUED)
		{
			hash_seq_term(&status);
			break;
		}

		taskState = (TrackerTaskState *) hash_seq_search(&status);
	}

	return taskState;
}