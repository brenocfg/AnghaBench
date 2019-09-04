#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int HostIP; } ;
typedef  TYPE_1__ VH ;
typedef  int UINT ;
struct TYPE_13__ {scalar_t__ num_item; } ;
struct TYPE_12__ {int Param1; int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_11__ {int DestIp; int /*<<< orphan*/  DestPort; int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  SrcIp; TYPE_8__* UdpRecvQueue; } ;
typedef  TYPE_2__ NAT_ENTRY ;
typedef  TYPE_3__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBlock (TYPE_3__*) ; 
 TYPE_3__* GetNext (TYPE_8__*) ; 
 int /*<<< orphan*/  SendUdp (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void PoolingNatUdp(VH *v, NAT_ENTRY *n)
{
	// Validate arguments
	if (v == NULL || n == NULL)
	{
		return;
	}

	// Process if there are any packets in the receive queue
	if (n->UdpRecvQueue->num_item != 0)
	{
		BLOCK *block;

		// Send all UDP packets to the virtual network
		while (block = GetNext(n->UdpRecvQueue))
		{
			UINT src_ip = n->DestIp;

			if (src_ip == 0xFFFFFFFF)
			{
				src_ip = v->HostIP;
			}

			if (block->Param1 != 0)
			{
				src_ip = block->Param1;
			}

			SendUdp(v, n->SrcIp, n->SrcPort, src_ip, n->DestPort,
				block->Buf, block->Size);

			FreeBlock(block);
		}
	}
}