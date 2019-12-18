#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_23__ {scalar_t__* Buf; scalar_t__ Size; scalar_t__ PriorityQoS; } ;
struct TYPE_22__ {int size; int pos; scalar_t__ p; } ;
struct TYPE_21__ {int /*<<< orphan*/  CipherName; int /*<<< orphan*/  RemoteHostname; int /*<<< orphan*/  LocalPort; int /*<<< orphan*/  LocalIP; int /*<<< orphan*/  RemotePort; int /*<<< orphan*/  RemoteIP; } ;
struct TYPE_20__ {int EstablishedCount; int /*<<< orphan*/  Interrupt; int /*<<< orphan*/  SendQueue; scalar_t__ Disconnected; int /*<<< orphan*/  RecvQueue; } ;
typedef  TYPE_1__ SSTP_SERVER ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  TYPE_2__ SOCK ;
typedef  TYPE_3__ FIFO ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 int /*<<< orphan*/  FreeBlock (TYPE_4__*) ; 
 int /*<<< orphan*/  FreeSstpServer (TYPE_1__*) ; 
 TYPE_4__* GetNext (int /*<<< orphan*/ ) ; 
 scalar_t__ GetNextIntervalForInterrupt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ MAX_BUFFERING_PACKET_SIZE ; 
 int /*<<< orphan*/  MIN (scalar_t__,scalar_t__) ; 
 scalar_t__* Malloc (scalar_t__) ; 
 TYPE_4__* NewBlock (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* NewFifo () ; 
 TYPE_1__* NewSstpServer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int READ_USHORT (scalar_t__*) ; 
 int /*<<< orphan*/  ReadFifo (TYPE_3__*,scalar_t__*,scalar_t__) ; 
 scalar_t__ Recv (TYPE_2__*,scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  ReleaseFifo (TYPE_3__*) ; 
 scalar_t__ SELECT_TIME ; 
 scalar_t__ SOCK_LATER ; 
 scalar_t__ SSTP_VERSION_1 ; 
 scalar_t__ Send (TYPE_2__*,scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  SstpProcessInterrupt (TYPE_1__*) ; 
 int /*<<< orphan*/  WaitSockEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteFifo (TYPE_3__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  YieldCpu () ; 

bool ProcessSstpHttps(CEDAR *cedar, SOCK *s, SOCK_EVENT *se)
{
	UINT tmp_size = 65536;
	UCHAR *tmp_buf;
	FIFO *recv_fifo;
	FIFO *send_fifo;
	SSTP_SERVER *sstp;
	bool ret = false;
	// Validate arguments
	if (cedar == NULL || s == NULL || se == NULL)
	{
		return false;
	}

	tmp_buf = Malloc(tmp_size);
	recv_fifo = NewFifo();
	send_fifo = NewFifo();

	sstp = NewSstpServer(cedar, &s->RemoteIP, s->RemotePort, &s->LocalIP, s->LocalPort, se,
		s->RemoteHostname, s->CipherName);

	while (true)
	{
		UINT r;
		bool is_disconnected = false;
		bool state_changed = false;

		// Receive data over SSL
		while (true)
		{
			r = Recv(s, tmp_buf, tmp_size, true);
			if (r == 0)
			{
				// SSL is disconnected
				is_disconnected = true;
				break;
			}
			else if (r == SOCK_LATER)
			{
				// Data is not received any more
				break;
			}
			else
			{
				// Queue the received data
				WriteFifo(recv_fifo, tmp_buf, r);
				state_changed = true;
			}
		}

		while (recv_fifo->size >= 4)
		{
			UCHAR *first4;
			UINT read_size = 0;
			bool ok = false;
			// Read 4 bytes from the beginning of the receive queue
			first4 = ((UCHAR *)recv_fifo->p) + recv_fifo->pos;
			if (first4[0] == SSTP_VERSION_1)
			{
				USHORT len = READ_USHORT(first4 + 2) & 0xFFF;
				if (len >= 4)
				{
					ok = true;

					if (recv_fifo->size >= len)
					{
						UCHAR *data;
						BLOCK *b;

						read_size = len;
						data = Malloc(read_size);

						ReadFifo(recv_fifo, data, read_size);

						b = NewBlock(data, read_size, 0);

						InsertQueue(sstp->RecvQueue, b);
					}
				}
			}

			if (read_size == 0)
			{
				break;
			}

			if (ok == false)
			{
				// Disconnect the connection since a bad packet received
				is_disconnected = true;
				break;
			}
		}

		// Process the timer interrupt
		SstpProcessInterrupt(sstp);

		if (sstp->Disconnected)
		{
			is_disconnected = true;
		}

		// Put the transmission data that SSTP module has generated into the transmission queue
		while (true)
		{
			BLOCK *b = GetNext(sstp->SendQueue);

			if (b == NULL)
			{
				break;
			}

			// When transmit a data packet, If there are packets of more than about
			// 2.5 MB in the transmission queue of the TCP, discard without transmission
			if (b->PriorityQoS || (send_fifo->size <= MAX_BUFFERING_PACKET_SIZE))
			{
				WriteFifo(send_fifo, b->Buf, b->Size);
			}

			FreeBlock(b);
		}

		// Data is transmitted over SSL
		while (send_fifo->size != 0)
		{
			r = Send(s, ((UCHAR *)send_fifo->p) + send_fifo->pos, send_fifo->size, true);
			if (r == 0)
			{
				// SSL is disconnected
				is_disconnected = true;
				break;
			}
			else if (r == SOCK_LATER)
			{
				// Can not send any more
				break;
			}
			else
			{
				// Advance the transmission queue by the amount of the transmitted
				ReadFifo(send_fifo, NULL, r);
				state_changed = true;
			}
		}

		if (is_disconnected)
		{
			// Disconnected
			break;
		}

		// Wait for the next state change
		if (state_changed == false)
		{
			UINT select_time = SELECT_TIME;
			UINT r = GetNextIntervalForInterrupt(sstp->Interrupt);
			WaitSockEvent(se, MIN(r, select_time));
		}
	}

	if (sstp != NULL && sstp->EstablishedCount >= 1)
	{
		ret = true;
	}

	FreeSstpServer(sstp);

	ReleaseFifo(recv_fifo);
	ReleaseFifo(send_fifo);
	Free(tmp_buf);

	YieldCpu();
	Disconnect(s);

	return ret;
}