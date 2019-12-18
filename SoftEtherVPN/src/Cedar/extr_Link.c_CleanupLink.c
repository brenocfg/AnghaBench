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
struct TYPE_4__ {int /*<<< orphan*/ * ServerCert; struct TYPE_4__* Policy; int /*<<< orphan*/  Auth; struct TYPE_4__* Option; scalar_t__ ClientSession; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ LINK ;

/* Variables and functions */
 int /*<<< orphan*/  CiFreeClientAuth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSession (scalar_t__) ; 

void CleanupLink(LINK *k)
{
	// Validate arguments
	if (k == NULL)
	{
		return;
	}

	DeleteLock(k->lock);
	if (k->ClientSession)
	{
		ReleaseSession(k->ClientSession);
	}
	Free(k->Option);
	CiFreeClientAuth(k->Auth);
	Free(k->Policy);

	if (k->ServerCert != NULL)
	{
		FreeX(k->ServerCert);
	}

	Free(k);
}