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
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int WorkerNodeCompare (void const*,void const*,int /*<<< orphan*/ ) ; 

int
CompareWorkerNodes(const void *leftElement, const void *rightElement)
{
	const void *leftWorker = *((const void **) leftElement);
	const void *rightWorker = *((const void **) rightElement);
	int compare = 0;
	Size ignoredKeySize = 0;

	compare = WorkerNodeCompare(leftWorker, rightWorker, ignoredKeySize);

	return compare;
}