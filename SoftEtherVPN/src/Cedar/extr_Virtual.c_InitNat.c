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
struct TYPE_4__ {int HaltNat; int /*<<< orphan*/  NativeNat; int /*<<< orphan*/  NatThread; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  NatTable; } ;
typedef  TYPE_1__ VH ;

/* Variables and functions */
 int /*<<< orphan*/  CompareNat ; 
 scalar_t__ IsEthSupported () ; 
 int /*<<< orphan*/  NatThread ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewNativeNat (TYPE_1__*) ; 
 int /*<<< orphan*/  NewSockEvent () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ ) ; 

void InitNat(VH *v)
{
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	// Create a NAT table
	v->NatTable = NewList(CompareNat);

	// Create a socket event
	v->SockEvent = NewSockEvent();

	// Create the NAT thread
	v->HaltNat = false;
	v->NatThread = NewThread(NatThread, (void *)v);
	WaitThreadInit(v->NatThread);

	if (IsEthSupported())
	{
		// Start a native NAT if access to the layer 2 Ethernet is supported
		v->NativeNat = NewNativeNat(v);
	}
}