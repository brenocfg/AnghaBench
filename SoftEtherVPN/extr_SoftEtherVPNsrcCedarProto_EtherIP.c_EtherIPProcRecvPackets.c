#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_6__ {int* Buf; int Size; } ;
struct TYPE_5__ {int L2TPv3; int /*<<< orphan*/ * Ipc; } ;
typedef  TYPE_1__ ETHERIP_SERVER ;
typedef  TYPE_2__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  IPCSendL2 (int /*<<< orphan*/ *,int*,int) ; 

void EtherIPProcRecvPackets(ETHERIP_SERVER *s, BLOCK *b)
{
	UCHAR *src;
	UINT src_size;
	// Validate arguments
	if (s == NULL || b == NULL)
	{
		return;
	}

	if (s->Ipc == NULL)
	{
		// Not connected to the Virtual HUB
		return;
	}

	src = b->Buf;
	src_size = b->Size;

	if (s->L2TPv3 == false)
	{
		// EtherIP header confirmation
		if (src_size < 2)
		{
			return;
		}

		if ((src[0] & 0xf0) != 0x30)
		{
			return;
		}

		src += 2;
		src_size -= 2;
	}

	if (src_size < 14)
	{
		// The size of the MAC frame is less than 14 bytes
		return;
	}

	// Send by IPC since a MAC frame has been received
	IPCSendL2(s->Ipc, src, src_size);
}