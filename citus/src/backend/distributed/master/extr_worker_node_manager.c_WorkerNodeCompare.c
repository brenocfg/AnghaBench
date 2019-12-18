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
struct TYPE_2__ {int workerPort; int /*<<< orphan*/  workerName; } ;
typedef  TYPE_1__ WorkerNode ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int /*<<< orphan*/  WORKER_LENGTH ; 
 int strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
WorkerNodeCompare(const void *lhsKey, const void *rhsKey, Size keySize)
{
	const WorkerNode *workerLhs = (const WorkerNode *) lhsKey;
	const WorkerNode *workerRhs = (const WorkerNode *) rhsKey;

	int nameCompare = 0;
	int portCompare = 0;

	nameCompare = strncmp(workerLhs->workerName, workerRhs->workerName, WORKER_LENGTH);
	if (nameCompare != 0)
	{
		return nameCompare;
	}

	portCompare = workerLhs->workerPort - workerRhs->workerPort;
	return portCompare;
}