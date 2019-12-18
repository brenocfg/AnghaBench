#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* Cancel; } ;
typedef  TYPE_2__ VH ;
struct TYPE_11__ {int /*<<< orphan*/  Thread; void* NatTableForRecv; void* NatTableForSend; int /*<<< orphan*/  HaltTube3; int /*<<< orphan*/  HaltTube2; int /*<<< orphan*/  HaltEvent; void* CancelLock; void* Lock; void* RecvQueue; void* SendQueue; int /*<<< orphan*/  LastInterfaceIndex; TYPE_1__* Cancel; TYPE_2__* v; } ;
struct TYPE_9__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_3__ NATIVE_NAT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CmpNativeNatTableForRecv ; 
 int /*<<< orphan*/  CmpNativeNatTableForSend ; 
 int /*<<< orphan*/  GetHashNativeNatTableForRecv ; 
 int /*<<< orphan*/  GetHashNativeNatTableForSend ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  NativeNatThread ; 
 int /*<<< orphan*/  NewEvent () ; 
 void* NewHashList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 void* NewLock () ; 
 void* NewQueue () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  NewTubePair (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NnInitIpCombineList (TYPE_3__*) ; 
 TYPE_3__* ZeroMalloc (int) ; 

NATIVE_NAT *NewNativeNat(VH *v)
{
	NATIVE_NAT *t;
	// Validate arguments
	if (v == NULL)
	{
		return NULL;
	}

	t = ZeroMalloc(sizeof(NATIVE_NAT));

	t->v = v;

	t->Cancel = v->Cancel;
	AddRef(t->Cancel->ref);

	// Data structure initialization
	t->LastInterfaceIndex = INFINITE;
	t->SendQueue = NewQueue();
	t->RecvQueue = NewQueue();
	NnInitIpCombineList(t);

	t->Lock = NewLock();

	t->CancelLock = NewLock();

	t->HaltEvent = NewEvent();

	NewTubePair(&t->HaltTube2, &t->HaltTube3, 0);

	// Create a NAT table
	t->NatTableForSend = NewHashList(GetHashNativeNatTableForSend, CmpNativeNatTableForSend, 11, true);
	t->NatTableForRecv = NewHashList(GetHashNativeNatTableForRecv, CmpNativeNatTableForRecv, 11, true);

	t->Thread = NewThread(NativeNatThread, t);

	return t;
}