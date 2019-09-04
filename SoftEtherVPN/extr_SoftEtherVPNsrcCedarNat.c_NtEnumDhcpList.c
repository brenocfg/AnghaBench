#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int Active; int /*<<< orphan*/  DhcpLeaseList; } ;
typedef  TYPE_1__ VH ;
typedef  size_t UINT ;
struct TYPE_18__ {int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Mask; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  ExpireTime; int /*<<< orphan*/  LeasedTime; int /*<<< orphan*/  Id; } ;
struct TYPE_17__ {int Online; int /*<<< orphan*/  lock; TYPE_1__* Virtual; } ;
struct TYPE_16__ {int NumItem; TYPE_2__* Items; } ;
struct TYPE_15__ {int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Mask; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  MacAddress; void* ExpireTime; void* LeasedTime; int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ RPC_ENUM_DHCP_ITEM ;
typedef  TYPE_3__ RPC_ENUM_DHCP ;
typedef  TYPE_4__ NAT ;
typedef  TYPE_5__ DHCP_LEASE ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t ERR_NO_ERROR ; 
 size_t ERR_OFFLINE ; 
 int /*<<< orphan*/  FreeRpcEnumDhcp (TYPE_3__*) ; 
 TYPE_5__* LIST_DATA (int /*<<< orphan*/ ,size_t) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockVirtual (TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* TickToTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockVirtual (TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 

UINT NtEnumDhcpList(NAT *n, RPC_ENUM_DHCP *t)
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
					FreeRpcEnumDhcp(t);
					Zero(t, sizeof(RPC_ENUM_DHCP));

					LockList(v->DhcpLeaseList);
					{
						UINT i;
						t->NumItem = LIST_NUM(v->DhcpLeaseList);
						t->Items = ZeroMalloc(sizeof(RPC_ENUM_DHCP_ITEM) * t->NumItem);

						for (i = 0;i < t->NumItem;i++)
						{
							DHCP_LEASE *dhcp = LIST_DATA(v->DhcpLeaseList, i);
							RPC_ENUM_DHCP_ITEM *e = &t->Items[i];

							e->Id = dhcp->Id;
							e->LeasedTime = TickToTime(dhcp->LeasedTime);
							e->ExpireTime = TickToTime(dhcp->ExpireTime);
							Copy(e->MacAddress, dhcp->MacAddress, 6);
							e->IpAddress = dhcp->IpAddress;
							e->Mask = dhcp->Mask;
							StrCpy(e->Hostname, sizeof(e->Hostname), dhcp->Hostname);
						}
					}
					UnlockList(v->DhcpLeaseList);
				}
			}
			UnlockVirtual(v);
		}
	}
	Unlock(n->lock);

	return ret;
}