#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmpmsg ;
typedef  scalar_t__ UINT ;
struct TYPE_23__ {int /*<<< orphan*/  IsDisconnected; TYPE_3__* SslInOut; TYPE_2__* RawIn; TYPE_1__* RawOut; } ;
struct TYPE_22__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_21__ {TYPE_9__* SslPipe; } ;
struct TYPE_20__ {int /*<<< orphan*/  Type; } ;
struct TYPE_19__ {scalar_t__ size; } ;
struct TYPE_18__ {int /*<<< orphan*/  SendFifo; } ;
struct TYPE_17__ {TYPE_4__* SendFifo; } ;
struct TYPE_16__ {TYPE_4__* RecvFifo; } ;
typedef  TYPE_4__ FIFO ;
typedef  TYPE_5__ EAP_MESSAGE ;
typedef  TYPE_6__ EAP_CLIENT ;
typedef  TYPE_7__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (TYPE_5__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_7__*) ; 
 int /*<<< orphan*/  MIN (scalar_t__,int) ; 
 TYPE_7__* ReadFifoAll (TYPE_4__*) ; 
 int SendPeapRawPacket (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SyncSslPipe (TYPE_9__*) ; 
 int /*<<< orphan*/  WriteFifo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_5__*,int) ; 

bool SendPeapPacket(EAP_CLIENT *e, void *msg, UINT msg_size)
{
	bool ret = false;
	FIFO *send_fifo;
	FIFO *recv_fifo;
	BUF *buf;
	EAP_MESSAGE tmpmsg;
	if (e == NULL || msg == NULL || msg_size == 0)
	{
		return false;
	}
	if (e->SslPipe == NULL)
	{
		return false;
	}

	send_fifo = e->SslPipe->RawOut->RecvFifo;
	recv_fifo = e->SslPipe->RawIn->SendFifo;

	Zero(&tmpmsg, sizeof(tmpmsg));
	Copy(&tmpmsg, msg, MIN(msg_size, sizeof(EAP_MESSAGE)));

	WriteFifo(e->SslPipe->SslInOut->SendFifo, &tmpmsg.Type, msg_size - 4);

	SyncSslPipe(e->SslPipe);

	buf = ReadFifoAll(send_fifo);

	while (true)
	{
		ret = SendPeapRawPacket(e, buf->Buf, buf->Size);
		FreeBuf(buf);

		if (send_fifo->size == 0)
		{
			break;
		}

		buf = ReadFifoAll(send_fifo);
	}

	return !e->SslPipe->IsDisconnected;
}