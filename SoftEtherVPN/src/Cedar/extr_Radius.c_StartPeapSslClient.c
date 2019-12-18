#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  IsDisconnected; TYPE_2__* RawIn; TYPE_1__* RawOut; } ;
struct TYPE_17__ {int /*<<< orphan*/  Size; int /*<<< orphan*/ * Buf; } ;
struct TYPE_16__ {TYPE_6__* SslPipe; } ;
struct TYPE_15__ {scalar_t__ size; } ;
struct TYPE_14__ {TYPE_3__* SendFifo; } ;
struct TYPE_13__ {TYPE_3__* RecvFifo; } ;
typedef  TYPE_3__ FIFO ;
typedef  TYPE_4__ EAP_CLIENT ;
typedef  TYPE_5__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_5__*) ; 
 TYPE_6__* NewSslPipe (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* ReadFifoAll (TYPE_3__*) ; 
 int SendPeapRawPacket (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SyncSslPipe (TYPE_6__*) ; 

bool StartPeapSslClient(EAP_CLIENT *e)
{
	bool ret = false;
	FIFO *send_fifo;
	FIFO *recv_fifo;
	BUF *buf;
	if (e == NULL)
	{
		return false;
	}
	if (e->SslPipe != NULL)
	{
		return false;
	}

	e->SslPipe = NewSslPipe(false, NULL, NULL, NULL);
	send_fifo = e->SslPipe->RawOut->RecvFifo;
	recv_fifo = e->SslPipe->RawIn->SendFifo;

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

	SendPeapRawPacket(e, NULL, 0);

	return !e->SslPipe->IsDisconnected;
}