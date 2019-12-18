#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Virtual; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_3__* Nat; int /*<<< orphan*/  Session; } ;
typedef  TYPE_1__ SNAT ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  NiFreeNat (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseSession (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopSession (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Virtual_Free (int /*<<< orphan*/ ) ; 

void SnFreeSecureNAT(SNAT *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	// Stop the session 
	StopSession(s->Session);
	ReleaseSession(s->Session);

	// Virtual machine release
	Virtual_Free(s->Nat->Virtual);

	// NAT release
	NiFreeNat(s->Nat);

	DeleteLock(s->lock);

	Free(s);
}