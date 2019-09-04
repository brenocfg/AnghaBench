#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  int UINT ;
struct TYPE_5__ {int num_item; } ;
struct TYPE_4__ {void* RawIpYourMacAddr; void* RawIpMyMacAddr; TYPE_2__* RawIpSendQueue; } ;
typedef  TYPE_1__ ETH ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  InsertQueue (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  SeekBufToBegin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  WriteBufShort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void EthSendIpPacketInnerIpRaw(ETH *e, void *data, UINT size, USHORT protocol)
{
	BUF *b;
	if (e == NULL || data == NULL || size == 0)
	{
		return;
	}

	if (e->RawIpSendQueue->num_item >= 1024)
	{
		return;
	}

	b = NewBuf();
	WriteBuf(b, e->RawIpYourMacAddr, 6);
	WriteBuf(b, e->RawIpMyMacAddr, 6);
	WriteBufShort(b, protocol);
	WriteBuf(b, data, size);
	SeekBufToBegin(b);

	InsertQueue(e->RawIpSendQueue, b);
}