#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ *) ; 

void InsertQueueWithLock(QUEUE *q, void *p)
{
	// Validate arguments
	if (q == NULL || p == NULL)
	{
		return;
	}

	LockQueue(q);
	{
		InsertQueue(q, p);
	}
	UnlockQueue(q);
}