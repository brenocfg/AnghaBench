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
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  Cedar; int /*<<< orphan*/ * Virtual; } ;
typedef  TYPE_1__ NAT ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NiFreeConfig (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseVirtual (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopVirtualHost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void NiFreeNat(NAT *n)
{
	// Validate arguments
	if (n == NULL)
	{
		return;
	}

	// Complete management command
	//NiFreeAdminAccept(n);

	// Stop if the virtual host is running
	Lock(n->lock);
	{
		if (n->Virtual != NULL)
		{
			StopVirtualHost(n->Virtual);
			ReleaseVirtual(n->Virtual);
			n->Virtual = NULL;
		}
	}
	Unlock(n->lock);

	// Release the settings
	NiFreeConfig(n);

	// Delete the object
	ReleaseCedar(n->Cedar);
	ReleaseEvent(n->HaltEvent);
	DeleteLock(n->lock);

	Free(n);
}