#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VH_OPTION ;
struct TYPE_8__ {int IcmpRawSocketOk; int IcmpApiOk; int /*<<< orphan*/ * nat; int /*<<< orphan*/  Counter; int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ VH ;
struct TYPE_9__ {scalar_t__ IsTtlSupported; } ;
typedef  TYPE_2__ SOCK ;
typedef  int /*<<< orphan*/  NAT ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  int /*<<< orphan*/  CLIENT_AUTH ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  IP_PROTO_ICMPV4 ; 
 scalar_t__ IsIcmpApiSupported () ; 
 int /*<<< orphan*/  MAKE_SPECIAL_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewCounter () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewRef () ; 
 TYPE_2__* NewUDP4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_2__*) ; 
 int /*<<< orphan*/  SetVirtualHostOption (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

VH *NewVirtualHostEx(CEDAR *cedar, CLIENT_OPTION *option, CLIENT_AUTH *auth, VH_OPTION *vh_option, NAT *nat)
{
	VH *v;
	SOCK *s;
	// Validate arguments
	if (vh_option == NULL)
	{
		return NULL;
	}

	// Create a VH
	v = ZeroMalloc(sizeof(VH));
	v->ref = NewRef();
	v->lock = NewLock();
	v->Counter = NewCounter();

	v->nat = nat;

	// Examine whether ICMP Raw Socket can be created
	s = NewUDP4(MAKE_SPECIAL_PORT(IP_PROTO_ICMPV4), NULL);
	if (s != NULL)
	{
		if (s->IsTtlSupported)
		{
			v->IcmpRawSocketOk = true;
		}

		ReleaseSock(s);
	}

	if (v->IcmpRawSocketOk == false)
	{
		if (IsIcmpApiSupported())
		{
			v->IcmpApiOk = true;
		}
	}

	// Set the options
	SetVirtualHostOption(v, vh_option);

	return v;
}