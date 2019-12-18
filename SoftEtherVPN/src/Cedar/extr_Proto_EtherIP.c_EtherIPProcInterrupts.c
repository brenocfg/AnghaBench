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
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_22__ {int /*<<< orphan*/  LockSettings; int /*<<< orphan*/  Services; } ;
struct TYPE_21__ {int Size; int /*<<< orphan*/ * Buf; } ;
struct TYPE_20__ {int /*<<< orphan*/  Password; int /*<<< orphan*/  UserName; int /*<<< orphan*/  HubName; } ;
struct TYPE_17__ {int /*<<< orphan*/  Password; int /*<<< orphan*/  UserName; int /*<<< orphan*/  HubName; } ;
struct TYPE_19__ {scalar_t__ LastEtherIPSettingVerNo; char* ClientId; scalar_t__ LastConnectFailedTick; scalar_t__ Now; int CurrentIPSecServiceSetting; int L2TPv3; int /*<<< orphan*/ * Ipc; int /*<<< orphan*/  SendPacketList; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  Lock; int /*<<< orphan*/  Ref; int /*<<< orphan*/ * IpcConnectThread; TYPE_3__* Ike; TYPE_7__* IPsec; TYPE_2__ CurrentEtherIPIdSetting; } ;
struct TYPE_18__ {int /*<<< orphan*/  ThreadList; TYPE_1__* IPsec; } ;
struct TYPE_16__ {scalar_t__ EtherIPIdListSettingVerNo; } ;
typedef  int /*<<< orphan*/  IPSEC_SERVICES ;
typedef  TYPE_4__ ETHERIP_SERVER ;
typedef  TYPE_5__ ETHERIP_ID ;
typedef  TYPE_6__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddThreadToThreadList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* Clone (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Copy (int*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ETHERIP_VPN_CONNECT_RETRY_INTERVAL ; 
 int /*<<< orphan*/  EtherIPIpcConnectThread ; 
 int /*<<< orphan*/  EtherIPLog (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  FreeBlock (TYPE_6__*) ; 
 int /*<<< orphan*/  FreeIPC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPCProcessInterrupts (int /*<<< orphan*/ *) ; 
 TYPE_6__* IPCRecvL2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPCSetSockEventWhenRecvL2Packet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IsIPCConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int* Malloc (int) ; 
 TYPE_6__* NewBlock (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int SearchEtherIPId (TYPE_7__*,TYPE_5__*,char*) ; 
 scalar_t__ StrCmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void EtherIPProcInterrupts(ETHERIP_SERVER *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	// If EtherIP settings have been changed, and the change may effect to this connection, disconnect
	if (s->Ipc != NULL)
	{
		if (s->Ike->IPsec->EtherIPIdListSettingVerNo != s->LastEtherIPSettingVerNo)
		{
			ETHERIP_ID id;
			bool ok = true;

			s->LastEtherIPSettingVerNo = s->Ike->IPsec->EtherIPIdListSettingVerNo;

			if (SearchEtherIPId(s->IPsec, &id, s->ClientId) == false &&
				SearchEtherIPId(s->IPsec, &id, "*") == false)
			{
				ok = false;
			}
			else
			{
				if (StrCmpi(s->CurrentEtherIPIdSetting.HubName, id.HubName) != 0 ||
					StrCmpi(s->CurrentEtherIPIdSetting.UserName, id.UserName) != 0 ||
					StrCmp(s->CurrentEtherIPIdSetting.Password, id.Password) != 0)
				{
					ok = false;
				}
			}

			if (ok == false)
			{
				// Disconnect immediately since setting of EtherIP seems to have been changed
				FreeIPC(s->Ipc);
				s->Ipc = NULL;

				EtherIPLog(s, "LE_RECONNECT");
			}
		}
	}

	// Connect if IPC connection is not completed
	Lock(s->Lock);
	{
		if (s->Ipc == NULL)
		{
			if (s->IpcConnectThread == NULL)
			{
				if ((s->LastConnectFailedTick == 0) || ((s->LastConnectFailedTick + (UINT64)ETHERIP_VPN_CONNECT_RETRY_INTERVAL) <= s->Now))
				{
					Lock(s->IPsec->LockSettings);
					{
						Copy(&s->CurrentIPSecServiceSetting, &s->IPsec->Services, sizeof(IPSEC_SERVICES));
					}
					Unlock(s->IPsec->LockSettings);

					s->IpcConnectThread = NewThread(EtherIPIpcConnectThread, s);
					AddThreadToThreadList(s->Ike->ThreadList, s->IpcConnectThread);
					AddRef(s->Ref);
				}
			}
		}
	}
	Unlock(s->Lock);

	if (s->Ipc != NULL)
	{
		// Set to get hit the SockEvent when a packet arrives via the IPC
		IPCSetSockEventWhenRecvL2Packet(s->Ipc, s->SockEvent);

		// IPC interrupt processing
		IPCProcessInterrupts(s->Ipc);

		// Receive the MAC frame which arrived via the IPC
		while (true)
		{
			BLOCK *b = IPCRecvL2(s->Ipc);
			UCHAR *dst;
			UINT dst_size;

			if (b == NULL)
			{
				break;
			}

			if (b->Size >= 14)
			{
				BLOCK *block;

				// Store the arrived MAC frame by adding an EtherIP header to the reception packet queue

				if (s->L2TPv3 == false)
				{
					dst_size = b->Size + 2;
					dst = Malloc(dst_size);

					dst[0] = 0x30;
					dst[1] = 0x00;

					Copy(dst + 2, b->Buf, b->Size);
				}
				else
				{
					dst = Clone(b->Buf, b->Size);
					dst_size = b->Size;
				}

				block = NewBlock(dst, dst_size, 0);

				Add(s->SendPacketList, block);
			}

			FreeBlock(b);
		}

		if (IsIPCConnected(s->Ipc) == false)
		{
			// IPC connection is disconnected
			FreeIPC(s->Ipc);
			s->Ipc = NULL;
		}
	}
}