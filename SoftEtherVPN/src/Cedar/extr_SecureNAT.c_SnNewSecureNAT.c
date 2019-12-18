#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VH_OPTION ;
struct TYPE_11__ {int /*<<< orphan*/  Virtual; } ;
struct TYPE_10__ {int /*<<< orphan*/  Cedar; } ;
struct TYPE_9__ {TYPE_6__* Nat; int /*<<< orphan*/  lock; TYPE_2__* Hub; int /*<<< orphan*/  Cedar; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ SNAT ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_6__* NiNewNatEx (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SnSecureNATThread ; 
 int /*<<< orphan*/  VirtualInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

SNAT *SnNewSecureNAT(HUB *h, VH_OPTION *o)
{
	SNAT *s;
	THREAD *t;
	// Validate arguments
	if (h == NULL || o == NULL)
	{
		return NULL;
	}

	s = ZeroMalloc(sizeof(SNAT));
	s->Cedar = h->Cedar;
	s->Hub = h;
	s->lock = NewLock();

	// Create a NAT
	s->Nat = NiNewNatEx(s, o);

	// Initialize the virtual machine
	VirtualInit(s->Nat->Virtual);

	// Create a thread
	t = NewThread(SnSecureNATThread, s);
	WaitThreadInit(t);
	ReleaseThread(t);

	return s;
}