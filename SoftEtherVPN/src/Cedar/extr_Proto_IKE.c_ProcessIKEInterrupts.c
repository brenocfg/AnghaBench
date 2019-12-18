#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_28__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  data ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;
struct TYPE_36__ {scalar_t__ CurrentExpiresSoftTick_CtoS; scalar_t__ CurrentExpiresSoftTick_StoC; scalar_t__ CurrentNumHealtyIPsecSA_CtoS; scalar_t__ CurrentNumHealtyIPsecSA_StoC; scalar_t__ ServerPort; int StartQuickModeAsSoon; scalar_t__ LastQuickModeStartTick; scalar_t__ NeedQmBeginTick; scalar_t__ LastCommTick; scalar_t__ NextKeepAliveSendTick; scalar_t__ NextDpdSendTick; int /*<<< orphan*/  DpdSeqNo; TYPE_5__* CurrentIkeSa; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIP; int /*<<< orphan*/  ServerIP; int /*<<< orphan*/ * EtherIP; int /*<<< orphan*/ * L2TP; TYPE_3__* CurrentIpSecSaSend; TYPE_3__* CurrentIpSecSaRecv; scalar_t__ Deleting; scalar_t__ CurrentNumEstablishedIPsecSA_CtoS; scalar_t__ CurrentNumEstablishedIPsecSA_StoC; } ;
struct TYPE_32__ {scalar_t__ DpdRfc3706; } ;
struct TYPE_35__ {scalar_t__ NextSendTick; scalar_t__ NumResends; int Established; scalar_t__ LastCommTick; int /*<<< orphan*/  ResponderCookie; int /*<<< orphan*/  InitiatorCookie; TYPE_2__ Caps; scalar_t__ Deleting; TYPE_6__* IkeClient; TYPE_28__* SendBuffer; } ;
struct TYPE_34__ {scalar_t__ Now; int StateHasChanged; int /*<<< orphan*/  ThreadList; int /*<<< orphan*/  Interrupts; int /*<<< orphan*/  ClientList; int /*<<< orphan*/  IPsecSaList; int /*<<< orphan*/  IkeSaList; } ;
struct TYPE_33__ {scalar_t__ NextSendTick; scalar_t__ NumResends; int Established; int Deleting; scalar_t__ ExpiresSoftTick; scalar_t__ LastCommTick; TYPE_1__* PairIPsecSa; scalar_t__ ServerToClient; TYPE_6__* IkeClient; TYPE_28__* SendBuffer; } ;
struct TYPE_31__ {int* Buf; int Size; } ;
struct TYPE_30__ {scalar_t__ LastCommTick; } ;
typedef  TYPE_3__ IPSECSA ;
typedef  TYPE_4__ IKE_SERVER ;
typedef  TYPE_5__ IKE_SA ;
typedef  TYPE_6__ IKE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AddInterrupt (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  Clone (int*,int) ; 
 int /*<<< orphan*/  Debug (char*,TYPE_6__*) ; 
 int /*<<< orphan*/  EtherIPProcInterrupts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_28__*) ; 
 scalar_t__ IKE_INTERVAL_DPD_KEEPALIVE ; 
 scalar_t__ IKE_INTERVAL_UDP_KEEPALIVE ; 
 scalar_t__ IKE_QUICKMODE_FAILED_TIMEOUT ; 
 scalar_t__ IKE_QUICKMODE_START_INTERVAL ; 
 scalar_t__ IKE_SA_RESEND_INTERVAL ; 
 scalar_t__ IKE_TIMEOUT_FOR_IKE_CLIENT ; 
 scalar_t__ IKE_TIMEOUT_FOR_IKE_CLIENT_FOR_NOT_ESTABLISHED ; 
 int /*<<< orphan*/  IKE_UDP_KEEPALIVE ; 
 int /*<<< orphan*/  IKE_UDP_TYPE_ISAKMP ; 
 scalar_t__ IPSEC_PORT_IPSEC_ESP_UDP ; 
 int /*<<< orphan*/  IPsecIkeClientManageEtherIPServer (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  IPsecIkeClientManageL2TPServer (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  IPsecIkeClientSendEtherIPPackets (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPsecIkeClientSendL2TPPackets (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeNewNoticeDpdPayload (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IkeSendUdpPacket (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  L2TPProcessInterrupts (int /*<<< orphan*/ *) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 void* MAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MaintainThreadList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkIPsecSaAsDeleted (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  MarkIkeClientAsDeleted (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  MarkIkeSaAsDeleted (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  PurgeDeletingSAsAndClients (TYPE_4__*) ; 
 int /*<<< orphan*/  SendInformationalExchangePacket (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartQuickMode (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  WHERE ; 
 int /*<<< orphan*/  Zero (int*,int) ; 

void ProcessIKEInterrupts(IKE_SERVER *ike)
{
	UINT i;
	// Validate arguments
	if (ike == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(ike->ClientList);i++)
	{
		IKE_CLIENT *c = LIST_DATA(ike->ClientList, i);

		c->CurrentExpiresSoftTick_CtoS = 0;
		c->CurrentExpiresSoftTick_StoC = 0;
		c->CurrentNumEstablishedIPsecSA_CtoS = 0;
		c->CurrentNumEstablishedIPsecSA_StoC = 0;
		c->CurrentNumHealtyIPsecSA_CtoS = 0;
		c->CurrentNumHealtyIPsecSA_StoC = 0;
	}

	// Packet retransmission by scanning all IKE SA
	for (i = 0;i < LIST_NUM(ike->IkeSaList);i++)
	{
		IKE_SA *sa = LIST_DATA(ike->IkeSaList, i);

		if (sa->SendBuffer != NULL)
		{
			if (ike->Now >= sa->NextSendTick)
			{
				IKE_CLIENT *c = sa->IkeClient;

				IkeSendUdpPacket(ike, IKE_UDP_TYPE_ISAKMP, &c->ServerIP, c->ServerPort, &c->ClientIP, c->ClientPort,
					Clone(sa->SendBuffer->Buf, sa->SendBuffer->Size), sa->SendBuffer->Size);

				sa->NextSendTick += (UINT64)(IKE_SA_RESEND_INTERVAL);

				AddInterrupt(ike->Interrupts, sa->NextSendTick);

				if (sa->NumResends != 0)
				{
					sa->NumResends--;
					if (sa->NumResends == 0)
					{
						sa->NextSendTick = 0;
						FreeBuf(sa->SendBuffer);
						sa->SendBuffer = NULL;
					}
				}
			}
		}

		// Remove those of non-communication
		if (sa->IkeClient == NULL || (sa->IkeClient->CurrentIkeSa != sa))
		{
			// When the IKE_CLIENT don't point this
			if (sa->Established == false)
			{
				// Make time-out in a short time when it is not established
				if ((sa->LastCommTick + (UINT64)IKE_TIMEOUT_FOR_IKE_CLIENT_FOR_NOT_ESTABLISHED) <= ike->Now)
				{
					WHERE;
					MarkIkeSaAsDeleted(ike, sa);
				}
			}
			else
			{
				// Timeout in a long time in the case of established
				if ((sa->LastCommTick + (UINT64)IKE_TIMEOUT_FOR_IKE_CLIENT) <= ike->Now)
				{
					WHERE;
					MarkIkeSaAsDeleted(ike, sa);
				}
			}
		}
	}

	// Packet retransmission by scanning all IPsec SA
	for (i = 0;i < LIST_NUM(ike->IPsecSaList);i++)
	{
		IPSECSA *sa = LIST_DATA(ike->IPsecSaList, i);
		IKE_CLIENT *c = sa->IkeClient;

		if (sa->SendBuffer != NULL)
		{
			if (ike->Now >= sa->NextSendTick)
			{
				IKE_CLIENT *c = sa->IkeClient;

				IkeSendUdpPacket(ike, IKE_UDP_TYPE_ISAKMP, &c->ServerIP, c->ServerPort, &c->ClientIP, c->ClientPort,
					Clone(sa->SendBuffer->Buf, sa->SendBuffer->Size), sa->SendBuffer->Size);

				sa->NextSendTick += (UINT64)(IKE_SA_RESEND_INTERVAL);

				AddInterrupt(ike->Interrupts, sa->NextSendTick);

				if (sa->NumResends != 0)
				{
					sa->NumResends--;

					if (sa->NumResends == 0)
					{
						sa->NextSendTick = 0;
						FreeBuf(sa->SendBuffer);
						sa->SendBuffer = NULL;
					}
				}
			}
		}

		if (sa->Established && sa->Deleting == false && c != NULL)
		{
			// Get the flexible expiration date of SA for each IKE_CLIENT
			if (sa->ServerToClient)
			{
				c->CurrentExpiresSoftTick_StoC = MAX(c->CurrentExpiresSoftTick_StoC, sa->ExpiresSoftTick);
				c->CurrentNumEstablishedIPsecSA_StoC++;

				if (sa->ExpiresSoftTick == 0 || sa->ExpiresSoftTick > ike->Now)
				{
					c->CurrentNumHealtyIPsecSA_StoC++;
				}
			}
			else
			{
				c->CurrentExpiresSoftTick_CtoS = MAX(c->CurrentExpiresSoftTick_CtoS, sa->ExpiresSoftTick);
				c->CurrentNumEstablishedIPsecSA_CtoS++;

				if (sa->ExpiresSoftTick == 0 || sa->ExpiresSoftTick > ike->Now)
				{
					c->CurrentNumHealtyIPsecSA_CtoS++;
				}
			}
		}

		// Remove those of non-communication
		if (sa->IkeClient == NULL || (sa->IkeClient->CurrentIpSecSaRecv != sa && sa->IkeClient->CurrentIpSecSaSend != sa))
		{
			// When the IKE_CLIENT don't point this
			UINT64 last_comm_tick = sa->LastCommTick;

			if (sa->ServerToClient && sa->PairIPsecSa != NULL)
			{
				last_comm_tick = sa->PairIPsecSa->LastCommTick;
			}

			if (sa->Established == false)
			{
				// Make time-out in a short time when it is not established
				if ((last_comm_tick + (UINT64)IKE_TIMEOUT_FOR_IKE_CLIENT_FOR_NOT_ESTABLISHED) <= ike->Now)
				{
					WHERE;
					MarkIPsecSaAsDeleted(ike, sa);
				}
			}
			else
			{
				// Timeout in a long time in the case of established
				if ((last_comm_tick + (UINT64)IKE_TIMEOUT_FOR_IKE_CLIENT) <= ike->Now)
				{
					WHERE;
					MarkIPsecSaAsDeleted(ike, sa);
				}
			}
		}
	}

	// IKE_CLIENT scanning process
	for (i = 0;i < LIST_NUM(ike->ClientList);i++)
	{
		IKE_CLIENT *c = LIST_DATA(ike->ClientList, i);
		UINT64 tick;
		UCHAR data[1];
		bool need_qm = false;
		bool need_qm_hard = false;
		UINT64 qm_soft_tick = 0;

		// Determine whether it is necessary to start a new Quick Mode
		if (c->CurrentExpiresSoftTick_StoC != 0 && ike->Now >= c->CurrentExpiresSoftTick_StoC)
		{
			need_qm = true;
			qm_soft_tick = MAX(qm_soft_tick, c->CurrentExpiresSoftTick_StoC);
		}

		if (c->CurrentExpiresSoftTick_CtoS != 0 && ike->Now >= c->CurrentExpiresSoftTick_CtoS)
		{
			need_qm = true;
			qm_soft_tick = MAX(qm_soft_tick, c->CurrentExpiresSoftTick_StoC);
		}

		if (c->CurrentNumHealtyIPsecSA_CtoS == 0 || c->CurrentNumHealtyIPsecSA_StoC == 0)
		{
			need_qm = true;
			need_qm_hard = true;
		}

		if (c->StartQuickModeAsSoon)
		{
			need_qm = true;
			need_qm_hard = true;
		}

		if (c->Deleting || c->CurrentIkeSa == NULL || c->CurrentIkeSa->Deleting)
		{
			need_qm = false;
			need_qm_hard = true;
		}

		if (need_qm)
		{
			if (c->StartQuickModeAsSoon || ((c->LastQuickModeStartTick + (UINT64)IKE_QUICKMODE_START_INTERVAL) <= ike->Now))
			{
				// Start the Quick Mode
				Debug("IKE_CLIENT 0x%X: Begin QuickMode\n", c);
				c->StartQuickModeAsSoon = false;
				c->LastQuickModeStartTick = ike->Now;

				AddInterrupt(ike->Interrupts, c->LastQuickModeStartTick + (UINT64)IKE_QUICKMODE_START_INTERVAL);

				StartQuickMode(ike, c);
			}
		}

		if (need_qm_hard)
		{
			if (c->NeedQmBeginTick == 0)
			{
				c->NeedQmBeginTick = ike->Now;
			}
		}
		else
		{
			c->NeedQmBeginTick = 0;
		}

		if (((c->LastCommTick + (UINT64)IKE_TIMEOUT_FOR_IKE_CLIENT) <= ike->Now) ||
			((c->CurrentIkeSa == NULL && c->CurrentIpSecSaRecv == NULL && c->CurrentIpSecSaSend == NULL) && (c->LastCommTick + (UINT64)IKE_TIMEOUT_FOR_IKE_CLIENT_FOR_NOT_ESTABLISHED) <= ike->Now) ||
			(c->NeedQmBeginTick != 0 && ((c->NeedQmBeginTick + (UINT64)IKE_QUICKMODE_FAILED_TIMEOUT) <= ike->Now)))
		{
			// Remove IKE_CLIENT not communicating for a certain period of time
			WHERE;
			MarkIkeClientAsDeleted(ike, c);
		}

		// L2TP processing
		if (c->L2TP != NULL)
		{
			IPsecIkeClientManageL2TPServer(ike, c);

			// Interrupt processing occurs
			L2TPProcessInterrupts(c->L2TP);

			// Packet transmission
			IPsecIkeClientSendL2TPPackets(ike, c, c->L2TP);
		}

		// EtherIP processing
		if (c->EtherIP != NULL)
		{
			IPsecIkeClientManageEtherIPServer(ike, c);

			// Interrupt processing occurs
			EtherIPProcInterrupts(c->EtherIP);

			// Packet transmission
			IPsecIkeClientSendEtherIPPackets(ike, c, c->EtherIP);
		}

		// KeepAlive transmission
		tick = MAX(c->LastCommTick + (UINT64)IKE_INTERVAL_UDP_KEEPALIVE, c->NextKeepAliveSendTick);

		if (tick <= ike->Now && c->ServerPort == IPSEC_PORT_IPSEC_ESP_UDP)
		{
			c->NextKeepAliveSendTick = ike->Now + (UINT64)IKE_INTERVAL_UDP_KEEPALIVE;

			AddInterrupt(ike->Interrupts, c->NextKeepAliveSendTick);

			Zero(data, sizeof(data));
			data[0] = 0xff;

			IkeSendUdpPacket(ike, IKE_UDP_KEEPALIVE, &c->ServerIP, c->ServerPort, &c->ClientIP, c->ClientPort, Clone(data, sizeof(data)), sizeof(data));
		}

		// DPD transmission
		if (c->NextDpdSendTick == 0 || c->NextDpdSendTick <= ike->Now)
		{
			if (c->CurrentIkeSa != NULL && c->CurrentIkeSa->Established)
			{
				if (c->CurrentIkeSa->Caps.DpdRfc3706)
				{
					c->NextDpdSendTick = ike->Now + (UINT64)IKE_INTERVAL_DPD_KEEPALIVE;

					AddInterrupt(ike->Interrupts, c->NextDpdSendTick);

					SendInformationalExchangePacket(ike, c,
						IkeNewNoticeDpdPayload(false, c->CurrentIkeSa->InitiatorCookie, c->CurrentIkeSa->ResponderCookie,
						c->DpdSeqNo++));
				}
			}
		}
	}

	do
	{
		ike->StateHasChanged = false;

		// Deletion process
		PurgeDeletingSAsAndClients(ike);
	}
	while (ike->StateHasChanged);

	// Maintenance of the thread list
	MaintainThreadList(ike->ThreadList);
	/*Debug("ike->ThreadList: %u\n", LIST_NUM(ike->ThreadList));
	{
		UINT i;
		for (i = 0;i < LIST_NUM(ike->ThreadList);i++)
		{
			THREAD *t = LIST_DATA(ike->ThreadList, i);

			Debug("  Thread %u: 0x%p ID: %u Stop: %u Ref: %u\n", i, t, t->ThreadId, t->Stopped, t->ref->c->c);
		}
	}*/
}