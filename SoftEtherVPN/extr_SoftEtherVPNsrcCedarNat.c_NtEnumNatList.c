#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int Active; int /*<<< orphan*/  NatTable; TYPE_8__* NativeNat; } ;
typedef  TYPE_3__ VH ;
typedef  size_t UINT ;
struct TYPE_26__ {int Online; int /*<<< orphan*/  lock; TYPE_3__* Virtual; } ;
struct TYPE_25__ {TYPE_2__* NatTableForSend; } ;
struct TYPE_24__ {int /*<<< orphan*/  Status; int /*<<< orphan*/  TotalRecv; int /*<<< orphan*/  TotalSent; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  DestPort; int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  DestIp; int /*<<< orphan*/  SrcIp; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  Id; } ;
struct TYPE_23__ {int /*<<< orphan*/  TcpStatus; TYPE_1__* Sock; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  DestPort; int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  DestIp; int /*<<< orphan*/  SrcIp; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  Id; } ;
struct TYPE_22__ {size_t NumItem; TYPE_4__* Items; } ;
struct TYPE_21__ {int /*<<< orphan*/  TcpStatus; int /*<<< orphan*/  RecvSize; int /*<<< orphan*/  SendSize; int /*<<< orphan*/  DestIp; int /*<<< orphan*/  DestHost; int /*<<< orphan*/  SrcIp; int /*<<< orphan*/  SrcHost; void* LastCommTime; void* CreatedTime; int /*<<< orphan*/  DestPort; int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  Id; } ;
struct TYPE_19__ {int /*<<< orphan*/  AllList; } ;
struct TYPE_18__ {scalar_t__ Type; int /*<<< orphan*/  RemoteHostname; int /*<<< orphan*/  RecvSize; int /*<<< orphan*/  SendSize; } ;
typedef  TYPE_4__ RPC_ENUM_NAT_ITEM ;
typedef  TYPE_5__ RPC_ENUM_NAT ;
typedef  TYPE_6__ NAT_ENTRY ;
typedef  TYPE_7__ NATIVE_NAT_ENTRY ;
typedef  TYPE_8__ NATIVE_NAT ;
typedef  TYPE_9__ NAT ;

/* Variables and functions */
 size_t ERR_NO_ERROR ; 
 size_t ERR_OFFLINE ; 
 int /*<<< orphan*/  FreeRpcEnumNat (TYPE_5__*) ; 
 int /*<<< orphan*/  IPToStr32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockVirtual (TYPE_3__*) ; 
 scalar_t__ NnIsActive (TYPE_3__*) ; 
 scalar_t__ SOCK_TCP ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* TickToTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockVirtual (TYPE_3__*) ; 
 int /*<<< orphan*/  Zero (TYPE_5__*,int) ; 
 TYPE_4__* ZeroMalloc (int) ; 

UINT NtEnumNatList(NAT *n, RPC_ENUM_NAT *t)
{
	UINT ret = ERR_NO_ERROR;
	VH *v = NULL;

	Lock(n->lock);
	{
		v = n->Virtual;

		if (n->Online == false || v == NULL)
		{
			ret = ERR_OFFLINE;
		}
		else
		{
			LockVirtual(v);
			{
				if (v->Active == false)
				{
					ret = ERR_OFFLINE;
				}
				else
				{
					FreeRpcEnumNat(t);
					Zero(t, sizeof(RPC_ENUM_NAT));

					LockList(v->NatTable);
					{
						UINT i;
						UINT num_usermode_nat = LIST_NUM(v->NatTable);
						UINT num_kernel_mode_nat = 0;
						NATIVE_NAT *native = NULL;

						if (NnIsActive(v) && (v->NativeNat != NULL))
						{
							native = v->NativeNat;

							num_kernel_mode_nat = LIST_NUM(native->NatTableForSend->AllList);
						}

						t->NumItem = num_usermode_nat + num_kernel_mode_nat;
						t->Items = ZeroMalloc(sizeof(RPC_ENUM_NAT_ITEM) * t->NumItem);

						// Enumerate entries of the user mode NAT
						for (i = 0;i < num_usermode_nat;i++)
						{
							NAT_ENTRY *nat = LIST_DATA(v->NatTable, i);
							RPC_ENUM_NAT_ITEM *e = &t->Items[i];

							e->Id = nat->Id;
							e->Protocol = nat->Protocol;
							e->SrcIp = nat->SrcIp;
							e->DestIp = nat->DestIp;
							e->SrcPort = nat->SrcPort;
							e->DestPort = nat->DestPort;

							e->CreatedTime = TickToTime(nat->CreatedTime);
							e->LastCommTime = TickToTime(nat->LastCommTime);

							IPToStr32(e->SrcHost, sizeof(e->SrcHost), e->SrcIp);
							IPToStr32(e->DestHost, sizeof(e->DestHost), e->DestIp);

							if (nat->Sock != NULL)
							{
								e->SendSize = nat->Sock->SendSize;
								e->RecvSize = nat->Sock->RecvSize;

								if (nat->Sock->Type == SOCK_TCP)
								{
									StrCpy(e->DestHost, sizeof(e->DestHost), nat->Sock->RemoteHostname);
								}
							}

							e->TcpStatus = nat->TcpStatus;
						}

						// Enumerate the entries in the kernel-mode NAT
						if (native != NULL)
						{
							for (i = 0;i < num_kernel_mode_nat;i++)
							{
								NATIVE_NAT_ENTRY *nat = LIST_DATA(native->NatTableForSend->AllList, i);
								RPC_ENUM_NAT_ITEM *e = &t->Items[num_usermode_nat + i];

								e->Id = nat->Id;
								e->Protocol = nat->Protocol;
								e->SrcIp = nat->SrcIp;
								e->DestIp = nat->DestIp;
								e->SrcPort = nat->SrcPort;
								e->DestPort = nat->DestPort;
								e->CreatedTime = TickToTime(nat->CreatedTime);
								e->LastCommTime = TickToTime(nat->LastCommTime);

								IPToStr32(e->SrcHost, sizeof(e->SrcHost), e->SrcIp);
								IPToStr32(e->DestHost, sizeof(e->DestHost), e->DestIp);

								e->SendSize = nat->TotalSent;
								e->RecvSize = nat->TotalRecv;

								e->TcpStatus = nat->Status;
							}
						}
					}
					UnlockList(v->NatTable);
				}
			}
			UnlockVirtual(v);
		}
	}
	Unlock(n->lock);

	return ret;
}