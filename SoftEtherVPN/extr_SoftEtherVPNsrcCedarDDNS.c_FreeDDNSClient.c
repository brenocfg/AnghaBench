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
struct TYPE_4__ {int Halt; int /*<<< orphan*/  Lock; int /*<<< orphan*/  Cedar; int /*<<< orphan*/  Event; int /*<<< orphan*/  Thread; } ;
typedef  TYPE_1__ DDNS_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FreeDDNSClient(DDNS_CLIENT *c)
{
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	// Stop the thread 
	c->Halt = true;
	Set(c->Event);

	WaitThread(c->Thread, INFINITE);
	ReleaseThread(c->Thread);

	ReleaseEvent(c->Event);

	ReleaseCedar(c->Cedar);
	DeleteLock(c->Lock);

	Free(c);
}