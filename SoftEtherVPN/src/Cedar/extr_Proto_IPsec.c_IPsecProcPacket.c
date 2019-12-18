#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {scalar_t__ Size; int DestPort; int /*<<< orphan*/ * Data; void* Type; } ;
typedef  TYPE_1__ UDPPACKET ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {int /*<<< orphan*/ * Ike; int /*<<< orphan*/ * L2TP; } ;
typedef  int /*<<< orphan*/  L2TP_SERVER ;
typedef  TYPE_2__ IPSEC_SERVER ;
typedef  int /*<<< orphan*/  IKE_SERVER ;

/* Variables and functions */
 void* IKE_UDP_TYPE_ESP ; 
 void* IKE_UDP_TYPE_ISAKMP ; 
#define  IPSEC_PORT_IPSEC_ESP_RAW 131 
#define  IPSEC_PORT_IPSEC_ESP_UDP 130 
#define  IPSEC_PORT_IPSEC_ISAKMP 129 
#define  IPSEC_PORT_L2TP 128 
 scalar_t__ IsZero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ProcIKEPacketRecv (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ProcL2TPPacketRecv (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ WFP_ESP_PACKET_TAG_1 ; 
 scalar_t__ WFP_ESP_PACKET_TAG_2 ; 

void IPsecProcPacket(IPSEC_SERVER *s, UDPPACKET *p)
{
	L2TP_SERVER *l2tp;
	IKE_SERVER *ike;
	void *old_data_ptr;
	UINT old_data_size;
	bool proc_this_packet = true;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return;
	}

	old_data_ptr = p->Data;
	old_data_size = p->Size;

	l2tp = s->L2TP;
	ike = s->Ike;

	// UDP decapsulation process
	if (p->DestPort == IPSEC_PORT_IPSEC_ESP_UDP)
	{
#ifdef	OS_WIN32
		if (p->Size >= 12 && IsZero(p->Data, 4))
		{
			if (((*((UINT *)(((UCHAR *)p->Data) + sizeof(UINT) * 1))) == WFP_ESP_PACKET_TAG_1) &&
				((*((UINT *)(((UCHAR *)p->Data) + sizeof(UINT) * 2))) == WFP_ESP_PACKET_TAG_2))
			{
				// Truncate the head because the packet was modified by WFP
				p->Data = ((UCHAR *)p->Data) + 12;
				p->Size -= 12;
			}
		}
#endif	// OS_WIN32

		if (p->Size >= 4 && IsZero(p->Data, 4))
		{
			// Truncate the Non-ESP Marker
			p->Data = ((UCHAR *)p->Data) + 4;
			p->Size -= 4;

			p->Type = IKE_UDP_TYPE_ISAKMP;
		}
		else
		{
			p->Type = IKE_UDP_TYPE_ESP;
		}
	}
	else if (p->DestPort == IPSEC_PORT_IPSEC_ISAKMP)
	{
		if (p->Size >= 8 && IsZero(p->Data, 8))
		{
			// Truncate the Non-IKE Maker
			p->Data = ((UCHAR *)p->Data) + 8;
			p->Size -= 8;

			p->Type = IKE_UDP_TYPE_ESP;
		}
		else
		{
			p->Type = IKE_UDP_TYPE_ISAKMP;
		}
	}
	else if (p->DestPort == IPSEC_PORT_IPSEC_ESP_RAW)
	{
		// Raw ESP
		p->Type = IKE_UDP_TYPE_ESP;
	}


	if (proc_this_packet)
	{
		switch (p->DestPort)
		{
		case IPSEC_PORT_L2TP:
			// L2TP
			ProcL2TPPacketRecv(l2tp, p);
			break;

		case IPSEC_PORT_IPSEC_ISAKMP:
		case IPSEC_PORT_IPSEC_ESP_UDP:
		case IPSEC_PORT_IPSEC_ESP_RAW:
			// IPsec
			ProcIKEPacketRecv(ike, p);
			break;
		}
	}

	p->Data = old_data_ptr;
	p->Size = old_data_size;
}