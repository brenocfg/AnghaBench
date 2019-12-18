#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lock; struct TYPE_8__* SlotIdList; } ;
typedef  TYPE_1__ SECURE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseSecSession (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeSecInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeSecModule (TYPE_1__*) ; 
 int /*<<< orphan*/  LogoutSec (TYPE_1__*) ; 

void CloseSec(SECURE *sec)
{
	// Validate arguments
	if (sec == NULL)
	{
		return;
	}

	// Log out
	LogoutSec(sec);

	// Close the session
	CloseSecSession(sec);

	// Release the token information
	FreeSecInfo(sec);

	// Release of the slot list memory
	if (sec->SlotIdList != NULL)
	{
		Free(sec->SlotIdList);
		sec->SlotIdList = NULL;
	}

	// Unload the module
	FreeSecModule(sec);

	// Memory release
	DeleteLock(sec->lock);
	Free(sec);
}