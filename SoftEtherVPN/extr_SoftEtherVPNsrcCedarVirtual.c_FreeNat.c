#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int HaltNat; int /*<<< orphan*/  NatTable; int /*<<< orphan*/ * SockEvent; int /*<<< orphan*/ * NatThread; int /*<<< orphan*/ * NativeNat; } ;
typedef  TYPE_1__ VH ;

/* Variables and functions */
 int /*<<< orphan*/  FreeNativeNat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void FreeNat(VH *v)
{
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	// Stop the native NAT
	if (v->NativeNat != NULL)
	{
		FreeNativeNat(v->NativeNat);
		v->NativeNat = NULL;
	}

	// Stop the NAT thread
	v->HaltNat = true;
	SetSockEvent(v->SockEvent);
	WaitThread(v->NatThread, INFINITE);
	ReleaseThread(v->NatThread);
	v->NatThread = NULL;
	ReleaseSockEvent(v->SockEvent);
	v->SockEvent = NULL;

	// Release the NAT table
	ReleaseList(v->NatTable);
}