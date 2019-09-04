#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  SockList; } ;
typedef  TYPE_1__ SOCKLIST ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopSockList (TYPE_1__*) ; 

void FreeSockList(SOCKLIST *sl)
{
	// Validate arguments
	if (sl == NULL)
	{
		return;
	}

	StopSockList(sl);

	ReleaseList(sl->SockList);

	Free(sl);
}