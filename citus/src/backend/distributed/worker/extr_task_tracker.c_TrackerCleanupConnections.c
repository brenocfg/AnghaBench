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
typedef  TYPE_1__ WorkerTask ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 scalar_t__ INVALID_CONNECTION_ID ; 
 int /*<<< orphan*/  MultiClientDisconnect (scalar_t__) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
TrackerCleanupConnections(HTAB *WorkerTasksHash)
{
	HASH_SEQ_STATUS status;
	WorkerTask *currentTask = NULL;

	hash_seq_init(&status, WorkerTasksHash);

	currentTask = (WorkerTask *) hash_seq_search(&status);
	while (currentTask != NULL)
	{
		if (currentTask->connectionId != INVALID_CONNECTION_ID)
		{
			MultiClientDisconnect(currentTask->connectionId);
			currentTask->connectionId = INVALID_CONNECTION_ID;
		}

		currentTask = (WorkerTask *) hash_seq_search(&status);
	}
}