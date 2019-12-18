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
struct TYPE_3__ {int allocatedSize; int edgeCount; int /*<<< orphan*/ * edges; } ;
typedef  TYPE_1__ WaitGraph ;
typedef  int /*<<< orphan*/  WaitEdge ;

/* Variables and functions */
 scalar_t__ repalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static WaitEdge *
AllocWaitEdge(WaitGraph *waitGraph)
{
	/* ensure space for new edge */
	if (waitGraph->allocatedSize == waitGraph->edgeCount)
	{
		waitGraph->allocatedSize *= 2;
		waitGraph->edges = (WaitEdge *)
						   repalloc(waitGraph->edges, sizeof(WaitEdge) *
									waitGraph->allocatedSize);
	}

	return &waitGraph->edges[waitGraph->edgeCount++];
}