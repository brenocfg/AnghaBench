#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  Cancel; int /*<<< orphan*/  PacketQueue; int /*<<< orphan*/  MacAddr; int /*<<< orphan*/  Id; scalar_t__ Halt; int /*<<< orphan*/  Event; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ NULL_LAN ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Malloc (int) ; 
 int /*<<< orphan*/ * NewBlock (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NullGenerateMacAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int Rand32 () ; 
 int /*<<< orphan*/  StrToMac (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  null_lan_broadcast_address ; 

void NullPacketGenerateThread(THREAD *t, void *param)
{
	NULL_LAN *n = (NULL_LAN *)param;
	UINT64 end_tick = Tick64() + (UINT64)(60 * 1000);
	UINT seq = 0;
	// Validate arguments
	if (t == NULL || param == NULL)
	{
		return;
	}

	while (true)
	{
		/*if (Tick64() >= end_tick)
		{
			break;
		}*/

		Wait(n->Event, Rand32() % 1500);
		if (n->Halt)
		{
			break;
		}

		LockQueue(n->PacketQueue);
		{
			UCHAR *data;
			BLOCK *b;
			UINT size = Rand32() % 1500 + 14;
			UCHAR dst_mac[6];

			NullGenerateMacAddress(n->MacAddr, n->Id, seq);

			//NullGenerateMacAddress(dst_mac, n->Id + 1, 0);
			//StrToMac(dst_mac, "00-1B-21-A9-47-E6");
			StrToMac(dst_mac, "00-AC-7A-EF-83-FD");

			data = Malloc(size);
			Copy(data, null_lan_broadcast_address, 6);
			//Copy(data, dst_mac, 6);
			Copy(data + 6, n->MacAddr, 6);
			b = NewBlock(data, size, 0);
			InsertQueue(n->PacketQueue, b);
		}
		UnlockQueue(n->PacketQueue);
		Cancel(n->Cancel);

		//seq++;
	}
}