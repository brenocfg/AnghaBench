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
struct TYPE_4__ {int /*<<< orphan*/ * AdminAcceptThread; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ NAT ;

/* Variables and functions */
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  NiListenThread ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 

void NiInitAdminAccept(NAT *n)
{
	THREAD *t;
	// Validate arguments
	if (n == NULL)
	{
		return;
	}

	t = NewThread(NiListenThread, n);
	WaitThreadInit(t);
	n->AdminAcceptThread = t;
}