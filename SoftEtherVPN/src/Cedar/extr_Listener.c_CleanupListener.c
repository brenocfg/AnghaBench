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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Cedar; int /*<<< orphan*/  Event; int /*<<< orphan*/  Thread; int /*<<< orphan*/  lock; int /*<<< orphan*/ * Sock; } ;
typedef  TYPE_1__ LISTENER ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 

void CleanupListener(LISTENER *r)
{
	UINT i = 0;
	// Validate arguments
	if (r == NULL)
	{
		return;
	}


	if (r->Sock != NULL)
	{
		ReleaseSock(r->Sock);
	}

	DeleteLock(r->lock);
	ReleaseThread(r->Thread);
	ReleaseEvent(r->Event);

	ReleaseCedar(r->Cedar);

	Free(r);
}