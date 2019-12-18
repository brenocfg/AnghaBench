#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_21__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT64 ;
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_33__ {scalar_t__ num_item; } ;
struct TYPE_32__ {int IsFlooding; int /*<<< orphan*/  Size; } ;
struct TYPE_28__ {int Value; } ;
struct TYPE_31__ {int /*<<< orphan*/  Cancel; TYPE_8__* PacketQueue; TYPE_4__* Session; TYPE_3__ DownloadLimiter; } ;
struct TYPE_30__ {int* MacAddressSrc; int /*<<< orphan*/  PacketSize; int /*<<< orphan*/  PacketData; } ;
struct TYPE_29__ {scalar_t__ VLanId; scalar_t__ AdjustMss; scalar_t__ UdpAccelMss; scalar_t__ RUdpMss; int /*<<< orphan*/  CancelList; int /*<<< orphan*/  Cedar; TYPE_21__* Hub; scalar_t__ IsRUDPSession; scalar_t__ IsUsingUdpAcceleration; int /*<<< orphan*/  LastDLinkSTPPacketSendTick; int /*<<< orphan*/  LastDLinkSTPPacketDataHash; TYPE_1__* Policy; } ;
struct TYPE_27__ {int VlanTypeId; int DisableAdjustTcpMss; scalar_t__ FixForDLinkBPDU; } ;
struct TYPE_26__ {TYPE_2__* Option; } ;
struct TYPE_25__ {int MaxDownload; scalar_t__ CheckMac; } ;
typedef  TYPE_3__ TRAFFIC_LIMITER ;
typedef  TYPE_4__ SESSION ;
typedef  TYPE_5__ PKT ;
typedef  TYPE_6__ HUB_PA ;
typedef  TYPE_7__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AddCancelList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AdjustTcpMssL2 (void*,int,int,int) ; 
 int ApplyAccessListToForwardPacket (TYPE_21__*,TYPE_4__*,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  Cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CedarAddCurrentTcpQueueSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  FreeBlock (TYPE_7__*) ; 
 int INFINITE ; 
 int /*<<< orphan*/  InsertQueue (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  IntoTrafficLimiter (TYPE_3__*,TYPE_5__*) ; 
 int IsMostHighestPriorityPacket (TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ LIMITER_SAMPLING_SPAN ; 
 int /*<<< orphan*/  LockQueue (TYPE_8__*) ; 
 scalar_t__ MAX_STORED_QUEUE_NUM ; 
 int MD5_SIZE ; 
 int MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  Md5 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* NewBlock (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  UnlockQueue (TYPE_8__*) ; 
 int VLanRemoveTag (void**,int*,scalar_t__,int) ; 

void StorePacketToHubPa(HUB_PA *dest, SESSION *src, void *data, UINT size, PKT *packet, bool is_flooding, bool no_check_acl)
{
	BLOCK *b;
	// Validate arguments
	if (dest == NULL || data == NULL)
	{
		return;
	}

	if (size < 14)
	{
		Free(data);
		return;
	}

	if (no_check_acl == false)
	{
		if (src != NULL)
		{
			// Apply the access list for forwarding
			if (ApplyAccessListToForwardPacket(src->Hub, src, dest->Session, packet) == false)
			{
				Free(data);
				return;
			}
		}
	}

	if (src != NULL)
	{
		if (dest->Session->Policy->MaxDownload != 0)
		{
			// Traffic limit
			if (packet != NULL && IsMostHighestPriorityPacket(dest->Session, packet) == false)
			{
				TRAFFIC_LIMITER *tr = &dest->DownloadLimiter;
				IntoTrafficLimiter(tr, packet);

				if ((tr->Value * (UINT64)1000 / (UINT64)LIMITER_SAMPLING_SPAN) > dest->Session->Policy->MaxDownload)
				{
					// Limit
					Free(data);
					return;
				}
			}
		}
	}

	if (packet != NULL && src != NULL && src->Hub != NULL && src->Hub->Option != NULL && src->Hub->Option->FixForDLinkBPDU)
	{
		// Measures for D-Link bug
		UCHAR *mac = packet->MacAddressSrc;
		if ((mac[0] == 0x00 && mac[1] == 0x80 && mac[2] == 0xc8 && mac[3] == 0x00 && mac[4] == 0x00 && mac[5] == 0x00) ||
			(mac[0] == 0x00 && mac[1] == 0x0d && mac[2] == 0x88 && mac[3] == 0x00 && mac[4] == 0x00 && mac[5] == 0x00))
		{
			SESSION *session = dest->Session;

			if (session != NULL)
			{
				if (session->Policy != NULL && session->Policy->CheckMac)
				{
					UCHAR hash[MD5_SIZE];
					Md5(hash, packet->PacketData, packet->PacketSize);

					Copy(session->LastDLinkSTPPacketDataHash, hash, MD5_SIZE);
					session->LastDLinkSTPPacketSendTick = Tick64();
				}
			}
		}
	}

	// Remove the VLAN tag
	if (dest->Session != NULL && dest->Session->VLanId != 0)
	{
		UINT vlan_tpid = 0;
		if (src != NULL && src->Hub != NULL && src->Hub->Option != NULL)
		{
			vlan_tpid = src->Hub->Option->VlanTypeId;
		}
		if (VLanRemoveTag(&data, &size, dest->Session->VLanId, vlan_tpid) == false)
		{
			Free(data);
			return;
		}
	}

	if (src != NULL && dest->Session != NULL && src->Hub != NULL && src->Hub->Option != NULL)
	{
		if (dest->Session->AdjustMss != 0 ||
			(dest->Session->IsUsingUdpAcceleration && dest->Session->UdpAccelMss != 0) ||
			(dest->Session->IsRUDPSession && dest->Session->RUdpMss != 0))
		{
			if (src->Hub->Option->DisableAdjustTcpMss == false)
			{
				UINT target_mss = INFINITE;
				
				if (dest->Session->AdjustMss != 0)
				{
					target_mss = MIN(target_mss, dest->Session->AdjustMss);
				}

				if (dest->Session->IsUsingUdpAcceleration && dest->Session->UdpAccelMss != 0)
				{
					target_mss = MIN(target_mss, dest->Session->UdpAccelMss);
				}
				else if (dest->Session->IsRUDPSession && dest->Session->RUdpMss != 0)
				{
					target_mss = MIN(target_mss, dest->Session->RUdpMss);
				}

				// Processing of Adjust TCP MSS
				if (target_mss != INFINITE)
				{
					AdjustTcpMssL2(data, size, target_mss, src->Hub->Option->VlanTypeId);
				}
			}
		}
	}

	// Create a block
	b = NewBlock(data, size, 0);

	LockQueue(dest->PacketQueue);
	{
		// Measure the length of queue
		if (dest->PacketQueue->num_item < MAX_STORED_QUEUE_NUM)
		{
			// Store
			InsertQueue(dest->PacketQueue, b);

			if (is_flooding)
			{
				if (src != NULL)
				{
					b->IsFlooding = true;
					CedarAddCurrentTcpQueueSize(src->Cedar, b->Size);
				}
			}
		}
		else
		{
			// Drop the packet
			FreeBlock(b);
		}
	}
	UnlockQueue(dest->PacketQueue);

	// Issue of cancellation
	if (src != NULL)
	{
		AddCancelList(src->CancelList, dest->Cancel);
	}
	else
	{
		Cancel(dest->Cancel);
	}
}