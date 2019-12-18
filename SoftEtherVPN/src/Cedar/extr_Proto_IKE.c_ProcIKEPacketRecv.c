#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ Type; } ;
typedef  TYPE_1__ UDPPACKET ;
struct TYPE_17__ {int ExchangeType; } ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  TYPE_2__ IKE_PACKET ;

/* Variables and functions */
#define  IKE_EXCHANGE_TYPE_AGGRESSIVE 131 
#define  IKE_EXCHANGE_TYPE_INFORMATION 130 
#define  IKE_EXCHANGE_TYPE_MAIN 129 
#define  IKE_EXCHANGE_TYPE_QUICK 128 
 scalar_t__ IKE_UDP_TYPE_ESP ; 
 scalar_t__ IKE_UDP_TYPE_ISAKMP ; 
 int /*<<< orphan*/  IkeFree (TYPE_2__*) ; 
 TYPE_2__* ParseIKEPacketHeader (TYPE_1__*) ; 
 int /*<<< orphan*/  ProcIPsecEspPacketRecv (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ProcIkeAggressiveModePacketRecv (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ProcIkeInformationalExchangePacketRecv (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ProcIkeMainModePacketRecv (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ProcIkeQuickModePacketRecv (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 

void ProcIKEPacketRecv(IKE_SERVER *ike, UDPPACKET *p)
{
	// Validate arguments
	if (ike == NULL || p == NULL)
	{
		return;
	}

	if (p->Type == IKE_UDP_TYPE_ISAKMP)
	{
		// ISAKMP (IKE) packet
		IKE_PACKET *header;

		header = ParseIKEPacketHeader(p);
		if (header == NULL)
		{
			return;
		}

		//Debug("InitiatorCookie: %I64u, ResponderCookie: %I64u\n", header->InitiatorCookie, header->ResponderCookie);

		switch (header->ExchangeType)
		{
		case IKE_EXCHANGE_TYPE_MAIN:	// Main mode
			ProcIkeMainModePacketRecv(ike, p, header);
			break;

		case IKE_EXCHANGE_TYPE_AGGRESSIVE:	// Aggressive mode
			ProcIkeAggressiveModePacketRecv(ike, p, header);
			break;

		case IKE_EXCHANGE_TYPE_QUICK:	// Quick mode
			ProcIkeQuickModePacketRecv(ike, p, header);
			break;

		case IKE_EXCHANGE_TYPE_INFORMATION:	// Information exchange
			ProcIkeInformationalExchangePacketRecv(ike, p, header);
			break;
		}

		IkeFree(header);
	}
	else if (p->Type == IKE_UDP_TYPE_ESP)
	{
		// ESP packet
		ProcIPsecEspPacketRecv(ike, p);
	}
}