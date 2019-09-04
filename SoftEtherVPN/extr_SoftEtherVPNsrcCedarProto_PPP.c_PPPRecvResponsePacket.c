#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_17__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_22__ {scalar_t__ Protocol; int IsControl; TYPE_1__* Lcp; } ;
struct TYPE_21__ {TYPE_17__* TubeRecv; scalar_t__ ClientLCPOptionDetermined; TYPE_3__* LastStoredPacket; } ;
struct TYPE_20__ {scalar_t__ Id; scalar_t__ Code; } ;
struct TYPE_19__ {int /*<<< orphan*/  Event; } ;
typedef  TYPE_2__ PPP_SESSION ;
typedef  TYPE_3__ PPP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  FreePPPPacket (TYPE_3__*) ; 
 int IsTubeConnected (TYPE_17__*) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PPPLog (TYPE_2__*,char*) ; 
 TYPE_3__* PPPProcessRequestPacket (TYPE_2__*,TYPE_3__*) ; 
 TYPE_3__* PPPRecvPacketWithLowLayerProcessing (TYPE_2__*,int) ; 
 int PPPSendPacket (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  PPPStoreLastPacket (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ PPP_CHAP_CODE_FAILURE ; 
 scalar_t__ PPP_CODE_IS_REQUEST (scalar_t__,scalar_t__) ; 
 scalar_t__ PPP_CODE_IS_RESPONSE (scalar_t__,scalar_t__) ; 
 scalar_t__ PPP_IS_SUPPORTED_PROTOCOL (scalar_t__) ; 
 scalar_t__ PPP_PACKET_RECV_TIMEOUT ; 
 scalar_t__ PPP_PACKET_RESEND_INTERVAL ; 
 scalar_t__ PPP_PAP_CODE_ACK ; 
 scalar_t__ PPP_PAP_CODE_IS_RESPONSE (scalar_t__) ; 
 scalar_t__ PPP_PROTOCOL_CHAP ; 
 scalar_t__ PPP_PROTOCOL_PAP ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,scalar_t__) ; 

PPP_PACKET *PPPRecvResponsePacket(PPP_SESSION *p, PPP_PACKET *req, USHORT expected_protocol, USHORT *received_protocol, bool finish_when_all_lcp_acked,
								  bool return_mschapv2_response_with_no_processing)
{
	UINT64 giveup_tick = Tick64() + (UINT64)PPP_PACKET_RECV_TIMEOUT;
	UINT64 next_resend = Tick64() + (UINT64)PPP_PACKET_RESEND_INTERVAL;
	PPP_PACKET *ret = NULL;
	USHORT tmp_us = 0;
	// Validate arguments
	if (p == NULL || req != NULL && req->Lcp == NULL)
	{
		return NULL;
	}

	if (received_protocol == NULL)
	{
		received_protocol = &tmp_us;
	}

	if (req != NULL)
	{
		expected_protocol = req->Protocol;
	}

	*received_protocol = 0;

	// Receive the next packet (Retransmission repeatedly the last packet until the reception is completed)
	while (true)
	{
		UINT64 now = Tick64();
		UINT interval;

		if (IsTubeConnected(p->TubeRecv) == false)
		{
			return NULL;
		}

		while (true)
		{
			PPP_PACKET *pp;
			PPP_PACKET *response;

			if (p->LastStoredPacket != NULL)
			{
				pp = p->LastStoredPacket;
				p->LastStoredPacket = NULL;
			}
			else
			{
				pp = PPPRecvPacketWithLowLayerProcessing(p, true);
			}

			if (pp == NULL)
			{
				break;
			}

			if (req != NULL)
			{
				// Determine whether the packet is corresponding to the request that was sent at the last
				if (pp->IsControl && pp->Protocol == req->Protocol && pp->Lcp->Id == req->Lcp->Id &&
					PPP_CODE_IS_RESPONSE(pp->Protocol, pp->Lcp->Code))
				{
					return pp;
				}

				if (return_mschapv2_response_with_no_processing)
				{
					// For the double-MSCHAPv2 technique
					if (pp->IsControl && pp->Protocol == req->Protocol && pp->Lcp->Id == req->Lcp->Id &&
						pp->Protocol == PPP_PROTOCOL_CHAP && PPP_PAP_CODE_IS_RESPONSE(pp->Lcp->Code))
					{
						return pp;
					}
				}
			}

			// Return a response immediately without processing if a protocol other than the expected received
			if ((pp->IsControl && pp->Protocol != expected_protocol) || pp->IsControl == false)
			{
				if (PPP_IS_SUPPORTED_PROTOCOL(pp->Protocol))
				{
					// This is another supported protocol
					// Store this packet
					PPPStoreLastPacket(p, pp);

					*received_protocol = pp->Protocol;
					return NULL;
				}
				else
				{
					// Unsupported protocol
					Debug("Unsupported Protocol: 0x%x\n", pp->Protocol);
					FreePPPPacket(pp);

					return NULL;
				}
			}

			if (pp->IsControl && PPP_CODE_IS_REQUEST(pp->Protocol, pp->Lcp->Code))
			{
				// Record current resend because next steps may take a while
				UINT64 currentresend = next_resend - now;

				// Process when the received packet is a request packet
				response = PPPProcessRequestPacket(p, pp);

				// Increase next resend because this may have taken a while
				next_resend = Tick64() + currentresend;

				FreePPPPacket(pp);

				if (response == NULL)
				{
					return NULL;
				}
				else
				{
					bool is_pap_and_disconnect_now = false;
					bool is_chap_and_disconnect_now = false;

					if (PPPSendPacket(p, response) == false)
					{
						FreePPPPacket(response);
						return NULL;
					}

					if (response->Protocol == PPP_PROTOCOL_PAP && response->IsControl &&
						response->Lcp->Code != PPP_PAP_CODE_ACK)
					{
						is_pap_and_disconnect_now = true;
					}

					if (response->Protocol == PPP_PROTOCOL_CHAP && response->IsControl &&
						response->Lcp->Code == PPP_CHAP_CODE_FAILURE)
					{
						is_chap_and_disconnect_now = true;
					}

					FreePPPPacket(response);

					if (is_pap_and_disconnect_now)
					{
						// Disconnect immediately if user authentication fails at least once in the PAP authentication protocol
						Debug("Disconnecting because PAP failed.\n");
						SleepThread(300);
						return NULL;
					}

					if (is_chap_and_disconnect_now)
					{
						// Disconnect immediately if it fails to user authentication at least once in the CHAP authentication protocol
						Debug("Disconnecting because CHAP failed.\n");
						SleepThread(300);
						return NULL;
					}
				}
			}
			else
			{
				// Ignore in the case of the other packets
				FreePPPPacket(pp);
			}
		}

		// Packet retransmission
		if (req != NULL)
		{
			if (now >= next_resend)
			{
				next_resend = now + PPP_PACKET_RESEND_INTERVAL;

				if (PPPSendPacket(p, req) == false)
				{
					return NULL;
				}
			}
		}

		if (req == NULL)
		{
			giveup_tick = now + (UINT64)PPP_PACKET_RECV_TIMEOUT;
		}

		// Time-out decision
		if (now >= giveup_tick)
		{
			PPPLog(p, "LP_CONTROL_TIMEOUT");
			return NULL;
		}

		// Wait
		if (req != NULL)
		{
			interval = MIN((UINT)(giveup_tick - now), (UINT)(next_resend - now));
		}
		else
		{
			interval = (UINT)(giveup_tick - now);
		}

		if (finish_when_all_lcp_acked && p->ClientLCPOptionDetermined)
		{
			return NULL;
		}

		Wait(p->TubeRecv->Event, interval);
	}
}