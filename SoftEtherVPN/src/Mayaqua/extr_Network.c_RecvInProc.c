#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_12__ {int /*<<< orphan*/  Event; } ;
struct TYPE_11__ {scalar_t__ Type; int Connected; int AsyncMode; TYPE_4__* RecvTube; int /*<<< orphan*/ * InProcRecvFifo; TYPE_4__* SendTube; scalar_t__ Disconnecting; } ;
struct TYPE_10__ {scalar_t__ DataSize; scalar_t__ Data; } ;
typedef  TYPE_1__ TUBEDATA ;
typedef  TYPE_2__ SOCK ;
typedef  int /*<<< orphan*/  FIFO ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Disconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeTubeData (TYPE_1__*) ; 
 scalar_t__ GetTimeout (TYPE_2__*) ; 
 int IsTubeConnected (TYPE_4__*) ; 
 scalar_t__ ReadFifo (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 scalar_t__ SOCK_INPROC ; 
 scalar_t__ SOCK_LATER ; 
 scalar_t__ Tick64 () ; 
 TYPE_1__* TubeRecvAsync (TYPE_4__*) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WriteFifo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

UINT RecvInProc(SOCK *sock, void *data, UINT size)
{
	FIFO *f;
	UINT ret;
	UINT timeout;
	UINT64 giveup_time;
	TUBEDATA *d = NULL;
	if (sock == NULL || sock->Type != SOCK_INPROC || sock->Disconnecting || sock->Connected == false)
	{
		return 0;
	}

	if (IsTubeConnected(sock->SendTube) == false)
	{
		return 0;
	}

	f = sock->InProcRecvFifo;
	if (f == NULL)
	{
		return 0;
	}

	// If there is data in the FIFO, return it immediately
	ret = ReadFifo(f, data, size);
	if (ret != 0)
	{
		return ret;
	}

	timeout = GetTimeout(sock);

	giveup_time = Tick64() + (UINT)timeout;

	// When there is no data in the FIFO, read the next data from the tube
	d = NULL;

	while (true)
	{
		UINT64 now = 0;
		UINT interval;

		if (sock->AsyncMode == false)
		{
			now = Tick64();

			if (now >= giveup_time)
			{
				break;
			}
		}

		d = TubeRecvAsync(sock->RecvTube);

		if (d != NULL)
		{
			break;
		}

		if (IsTubeConnected(sock->RecvTube) == false)
		{
			break;
		}

		if (sock->AsyncMode)
		{
			break;
		}

		interval = (UINT)(giveup_time - now);

		Wait(sock->RecvTube->Event, interval);
	}

	if (d == NULL)
	{
		if (IsTubeConnected(sock->RecvTube) == false)
		{
			return 0;
		}

		if (sock->AsyncMode == false)
		{
			// If a timeout occurs in synchronous mode, disconnect ir
			Disconnect(sock);

			return 0;
		}
		else
		{
			// If a timeout occurs in asynchronous mode, returns the blocking error 
			return SOCK_LATER;
		}
	}
	else
	{
		// If the received data is larger than the requested size, write the rest to FIFO
		if (d->DataSize > size)
		{
			WriteFifo(f, ((UCHAR *)d->Data) + size, d->DataSize - size);
			ret = size;
		}
		else
		{
			ret = d->DataSize;
		}

		Copy(data, d->Data, ret);

		FreeTubeData(d);

		return ret;
	}
}