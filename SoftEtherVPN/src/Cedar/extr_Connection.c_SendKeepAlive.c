#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  size_t UINT ;
typedef  size_t UCHAR ;
struct TYPE_8__ {TYPE_2__* Session; } ;
struct TYPE_7__ {int TotalSendSize; int TotalSendSizeReal; TYPE_1__* UdpAccel; scalar_t__ UseUdpAcceleration; } ;
struct TYPE_6__ {scalar_t__ MyPortByNatTServer; } ;
typedef  int /*<<< orphan*/  TCPSOCK ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (size_t*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Endian16 (int /*<<< orphan*/ ) ; 
 size_t Endian32 (size_t) ; 
 int /*<<< orphan*/  Free (size_t*) ; 
 size_t KEEP_ALIVE_MAGIC ; 
 size_t MAX (size_t,int) ; 
 size_t MAX_KEEPALIVE_SIZE ; 
 size_t* MallocFast (size_t) ; 
 int StrLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UDP_NAT_T_PORT_SIGNATURE_IN_KEEP_ALIVE ; 
 int /*<<< orphan*/  WriteSendFifo (TYPE_2__*,int /*<<< orphan*/ *,size_t*,size_t) ; 
 size_t rand () ; 

void SendKeepAlive(CONNECTION *c, TCPSOCK *ts)
{
	UINT size, i, num;
	UINT size_be;
	SESSION *s;
	UCHAR *buf;
	bool insert_natt_port = false;
	// Validate arguments
	if (c == NULL || ts == NULL)
	{
		return;
	}

	s = c->Session;

	size = rand() % MAX_KEEPALIVE_SIZE;
	num = KEEP_ALIVE_MAGIC;

	if (s != NULL && s->UseUdpAcceleration && s->UdpAccel != NULL)
	{
		if (s->UdpAccel->MyPortByNatTServer != 0)
		{
			size = MAX(size, (StrLen(UDP_NAT_T_PORT_SIGNATURE_IN_KEEP_ALIVE) + sizeof(USHORT)));

			insert_natt_port = true;
		}
	}

	buf = MallocFast(size);

	for (i = 0;i < size;i++)
	{
		buf[i] = rand();
	}

	if (insert_natt_port)
	{
		USHORT myport = Endian16((USHORT)s->UdpAccel->MyPortByNatTServer);

		Copy(buf, UDP_NAT_T_PORT_SIGNATURE_IN_KEEP_ALIVE, StrLen(UDP_NAT_T_PORT_SIGNATURE_IN_KEEP_ALIVE));
		Copy(buf + StrLen(UDP_NAT_T_PORT_SIGNATURE_IN_KEEP_ALIVE), &myport, sizeof(USHORT));
	}

	num = Endian32(num);
	size_be = Endian32(size);
	WriteSendFifo(c->Session, ts, &num, sizeof(UINT));
	WriteSendFifo(c->Session, ts, &size_be, sizeof(UINT));
	WriteSendFifo(c->Session, ts, buf, size);

	c->Session->TotalSendSize += sizeof(UINT) * 2 + size;
	c->Session->TotalSendSizeReal += sizeof(UINT) * 2 + size;

	Free(buf);
}