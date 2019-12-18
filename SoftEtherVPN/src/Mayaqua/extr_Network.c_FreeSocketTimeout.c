#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int unblocked; int /*<<< orphan*/  thread; int /*<<< orphan*/  cancel; } ;
typedef  TYPE_1__ SOCKET_TIMEOUT_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  Cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseCancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FreeSocketTimeout(SOCKET_TIMEOUT_PARAM *ttp)
{
	if(ttp == NULL)
	{
		return;
	}

	ttp->unblocked = true;
	Cancel(ttp->cancel);
	WaitThread(ttp->thread, INFINITE);
	ReleaseCancel(ttp->cancel);
	ReleaseThread(ttp->thread);
	Free(ttp);
//	Debug("FreeSocketTimeout succeed\n");
	return;
}