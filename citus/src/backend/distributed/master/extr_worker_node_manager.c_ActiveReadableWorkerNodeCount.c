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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * ActiveReadableWorkerNodeList () ; 
 int /*<<< orphan*/  list_length (int /*<<< orphan*/ *) ; 

uint32
ActiveReadableWorkerNodeCount(void)
{
	List *workerNodeList = ActiveReadableWorkerNodeList();
	uint32 liveWorkerCount = list_length(workerNodeList);

	return liveWorkerCount;
}