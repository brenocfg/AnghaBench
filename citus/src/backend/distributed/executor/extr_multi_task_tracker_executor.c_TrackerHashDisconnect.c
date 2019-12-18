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
struct TYPE_2__ {scalar_t__ connectionId; } ;
typedef  TYPE_1__ TaskTracker ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 scalar_t__ INVALID_CONNECTION_ID ; 
 int /*<<< orphan*/  MultiClientDisconnect (scalar_t__) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
TrackerHashDisconnect(HTAB *taskTrackerHash)
{
	TaskTracker *taskTracker = NULL;
	HASH_SEQ_STATUS status;
	hash_seq_init(&status, taskTrackerHash);

	taskTracker = (TaskTracker *) hash_seq_search(&status);
	while (taskTracker != NULL)
	{
		if (taskTracker->connectionId != INVALID_CONNECTION_ID)
		{
			MultiClientDisconnect(taskTracker->connectionId);
			taskTracker->connectionId = INVALID_CONNECTION_ID;
		}

		taskTracker = (TaskTracker *) hash_seq_search(&status);
	}
}