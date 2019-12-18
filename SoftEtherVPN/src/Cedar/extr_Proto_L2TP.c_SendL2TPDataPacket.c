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
typedef  int /*<<< orphan*/  UDPPACKET ;
typedef  int UCHAR ;
struct TYPE_6__ {int IsV3; int SessionId1; } ;
struct TYPE_5__ {int TunnelId1; int IsYamahaV3; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIp; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIp; } ;
typedef  TYPE_1__ L2TP_TUNNEL ;
typedef  TYPE_2__ L2TP_SESSION ;
typedef  int /*<<< orphan*/  L2TP_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int*,void*,int) ; 
 int /*<<< orphan*/  IPSEC_PORT_L2TPV3_VIRTUAL ; 
 int /*<<< orphan*/  L2TPSendUDP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* Malloc (int) ; 
 int /*<<< orphan*/ * NewUdpPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  WRITE_UINT (int*,int) ; 
 int /*<<< orphan*/  WRITE_USHORT (int*,int) ; 

void SendL2TPDataPacket(L2TP_SERVER *l2tp, L2TP_TUNNEL *t, L2TP_SESSION *s, void *data, UINT size)
{
	UDPPACKET *p;
	UCHAR *buf;
	UINT buf_size;
	// Validate arguments
	if (l2tp == NULL || t == NULL || s == NULL || (size != 0 && data == NULL))
	{
		return;
	}

	// Build a L2TP data packet
	if (s->IsV3 == false)
	{
		// L2TP Ver 2
		buf_size = 8 + size;
		buf = Malloc(buf_size);
		buf[0] = 0x40;
		buf[1] = 0x02;

		WRITE_USHORT(buf + 2, buf_size);
		WRITE_USHORT(buf + 4, t->TunnelId1);
		WRITE_USHORT(buf + 6, s->SessionId1);

		Copy(buf + 8, data, size);

		// Transmission
		p = NewUdpPacket(&t->ServerIp, t->ServerPort, &t->ClientIp, t->ClientPort, buf, buf_size);
	}
	else
	{
		// L2TPv3
		if (t->IsYamahaV3 == false)
		{
			buf_size = 4 + size;
			buf = Malloc(buf_size);

			WRITE_UINT(buf, s->SessionId1);

			Copy(buf + 4, data, size);

			// Transmission
			p = NewUdpPacket(&t->ServerIp, IPSEC_PORT_L2TPV3_VIRTUAL, &t->ClientIp, IPSEC_PORT_L2TPV3_VIRTUAL, buf, buf_size);
		}
		else
		{
			UINT header = 0x00030000;

			buf_size = 8 + size;
			buf = Malloc(buf_size);

			WRITE_UINT(buf, header);
			WRITE_UINT(buf + 4, s->SessionId1);

			Copy(buf + 8, data, size);

			// Transmission
			p = NewUdpPacket(&t->ServerIp, t->ServerPort, &t->ClientIp, t->ClientPort, buf, buf_size);
		}
	}

	L2TPSendUDP(l2tp, p);
}