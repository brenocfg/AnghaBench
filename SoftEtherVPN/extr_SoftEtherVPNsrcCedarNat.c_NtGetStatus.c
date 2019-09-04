#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  DhcpLeaseList; int /*<<< orphan*/  NatTable; TYPE_6__* NativeNat; } ;
typedef  TYPE_2__ VH ;
typedef  scalar_t__ UINT ;
struct TYPE_22__ {int /*<<< orphan*/  lock; TYPE_2__* Virtual; } ;
struct TYPE_21__ {TYPE_1__* NatTableForSend; } ;
struct TYPE_20__ {int Protocol; } ;
struct TYPE_19__ {int Protocol; } ;
struct TYPE_18__ {int /*<<< orphan*/  IsRawIpMode; int /*<<< orphan*/  IsKernelMode; scalar_t__ NumDhcpClients; int /*<<< orphan*/  NumDnsSessions; int /*<<< orphan*/  NumIcmpSessions; int /*<<< orphan*/  NumUdpSessions; int /*<<< orphan*/  NumTcpSessions; } ;
struct TYPE_16__ {int /*<<< orphan*/  AllList; } ;
typedef  TYPE_3__ RPC_NAT_STATUS ;
typedef  TYPE_4__ NAT_ENTRY ;
typedef  TYPE_5__ NATIVE_NAT_ENTRY ;
typedef  TYPE_6__ NATIVE_NAT ;
typedef  TYPE_7__ NAT ;

/* Variables and functions */
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcNatStatus (TYPE_3__*) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockVirtual (TYPE_2__*) ; 
#define  NAT_DNS 131 
#define  NAT_ICMP 130 
#define  NAT_TCP 129 
#define  NAT_UDP 128 
 scalar_t__ NnIsActive (TYPE_2__*) ; 
 int /*<<< orphan*/  NnIsActiveEx (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockVirtual (TYPE_2__*) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 

UINT NtGetStatus(NAT *n, RPC_NAT_STATUS *t)
{
	Lock(n->lock);
	{
		VH *v = n->Virtual;
		FreeRpcNatStatus(t);
		Zero(t, sizeof(RPC_NAT_STATUS));

		LockVirtual(v);
		{
			UINT i;

			LockList(v->NatTable);
			{
				for (i = 0;i < LIST_NUM(v->NatTable);i++)
				{
					NAT_ENTRY *e = LIST_DATA(v->NatTable, i);

					switch (e->Protocol)
					{
					case NAT_TCP:
						t->NumTcpSessions++;
						break;

					case NAT_UDP:
						t->NumUdpSessions++;
						break;

					case NAT_ICMP:
						t->NumIcmpSessions++;
						break;

					case NAT_DNS:
						t->NumDnsSessions++;
						break;
					}
				}

				if (NnIsActive(v) && v->NativeNat != NULL)
				{
					NATIVE_NAT *nn = v->NativeNat;

					for (i = 0;i < LIST_NUM(nn->NatTableForSend->AllList);i++)
					{
						NATIVE_NAT_ENTRY *e = LIST_DATA(nn->NatTableForSend->AllList, i);

						switch (e->Protocol)
						{
						case NAT_TCP:
							t->NumTcpSessions++;
							break;

						case NAT_UDP:
							t->NumUdpSessions++;
							break;

						case NAT_ICMP:
							t->NumIcmpSessions++;
							break;

						case NAT_DNS:
							t->NumDnsSessions++;
							break;
						}
					}
				}
			}
			UnlockList(v->NatTable);

			t->NumDhcpClients = LIST_NUM(v->DhcpLeaseList);

			t->IsKernelMode = NnIsActiveEx(v, &t->IsRawIpMode);
		}
		UnlockVirtual(v);
	}
	Unlock(n->lock);

	return ERR_NO_ERROR;
}