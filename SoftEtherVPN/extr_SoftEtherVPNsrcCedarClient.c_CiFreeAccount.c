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
struct TYPE_4__ {int /*<<< orphan*/ * ServerCert; int /*<<< orphan*/  ClientAuth; struct TYPE_4__* ClientOption; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  CiFreeClientAuth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 

void CiFreeAccount(ACCOUNT *a)
{
	// Validate arguments
	if (a == NULL)
	{
		return;
	}

	// Release the lock
	DeleteLock(a->lock);

	// Release the client option
	Free(a->ClientOption);

	// Release the client authentication data
	CiFreeClientAuth(a->ClientAuth);

	if (a->ServerCert != NULL)
	{
		FreeX(a->ServerCert);
	}

	Free(a);
}