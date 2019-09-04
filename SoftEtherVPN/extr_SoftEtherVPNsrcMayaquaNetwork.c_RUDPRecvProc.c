#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ip_str ;
typedef  int /*<<< orphan*/  ctoken_hash ;
typedef  void* USHORT ;
typedef  scalar_t__ UINT ;
struct TYPE_23__ {scalar_t__ SrcPort; int Size; scalar_t__ Type; int /*<<< orphan*/  Data; int /*<<< orphan*/  SrcIP; int /*<<< orphan*/  DestPort; int /*<<< orphan*/  DstIP; } ;
typedef  TYPE_1__ UDPPACKET ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_25__ {scalar_t__ Status; scalar_t__ YourPort; void* Dns_TranId; scalar_t__ Icmp_Type; int /*<<< orphan*/  YourIp; scalar_t__ LastSentTick; int /*<<< orphan*/  Key_Init; } ;
struct TYPE_24__ {int ServerMode; int NoNatTRegister; scalar_t__ Protocol; int /*<<< orphan*/  SessionList; scalar_t__ NatT_EnableSourceIpValidation; scalar_t__ (* ProcRpcRecv ) (TYPE_2__*,TYPE_1__*) ;int /*<<< orphan*/  NatT_IP_Safe; } ;
typedef  TYPE_2__ RUDP_STACK ;
typedef  TYPE_3__ RUDP_SESSION ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*,TYPE_3__*,char*,scalar_t__) ; 
 scalar_t__ ICMP_TYPE_INFORMATION_REPLY ; 
 scalar_t__ ICMP_TYPE_INFORMATION_REQUEST ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 scalar_t__ RUDPCheckSignOfRecvPacket (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int RUDPIsIpInValidateList (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* RUDPNewSession (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ RUDPProcessBulkRecvPacket (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RUDPProcessRecvPacket (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RUDPProcess_NatT_Recv (TYPE_2__*,TYPE_1__*) ; 
 TYPE_3__* RUDPSearchSession (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ RUDP_PROTOCOL_DNS ; 
 scalar_t__ RUDP_PROTOCOL_ICMP ; 
 scalar_t__ RUDP_QUOTA_MAX_NUM_SESSIONS ; 
 scalar_t__ RUDP_QUOTA_MAX_NUM_SESSIONS_PER_IP ; 
 scalar_t__ RUDP_SESSION_STATUS_CONNECT_SENT ; 
 scalar_t__ RUDP_SESSION_STATUS_ESTABLISHED ; 
 int SHA1_SIZE ; 
 scalar_t__ UDP_NAT_T_PORT ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ g_no_rudp_server ; 
 scalar_t__ stub1 (TYPE_2__*,TYPE_1__*) ; 

void RUDPRecvProc(RUDP_STACK *r, UDPPACKET *p)
{
	RUDP_SESSION *se = NULL;
	// Validate arguments
	if (r == NULL || p == NULL)
	{
		return;
	}

	if (r->ServerMode)
	{
		if (g_no_rudp_server)
		{
			return;
		}
	}

	if (r->ServerMode && r->NoNatTRegister == false)
	{

		if (p->SrcPort == UDP_NAT_T_PORT && CmpIpAddr(&p->SrcIP, &r->NatT_IP_Safe) == 0)
		{
			// There was a response from the NAT-T server
			RUDPProcess_NatT_Recv(r, p);
			return;
		}
	}

	if (r->ServerMode)
	{
		if (r->ProcRpcRecv != NULL)
		{
			if (r->ProcRpcRecv(r, p))
			{
				return;
			}
		}
	}

	if (r->ServerMode)
	{
		// Search the session by the end-point information if in the server mode
		se = RUDPSearchSession(r, &p->DstIP, p->DestPort, &p->SrcIP, p->SrcPort);
	}
	else
	{
		// Session should exist only one in the case of client mode
		if (LIST_NUM(r->SessionList) >= 1)
		{
			se = LIST_DATA(r->SessionList, 0);
		}
		else
		{
			se = NULL;
		}
	}

	if (p->Size < 20)
	{
		// The received packet is too small
		if (r->ServerMode == false)
		{
			if (se != NULL && se->Status == RUDP_SESSION_STATUS_CONNECT_SENT)
			{
				if (CmpIpAddr(&se->YourIp, &p->SrcIP) == 0)
				{
					// If the connection initialization packet which is shorter than 20 bytes
					// has been received from the server side, overwrite the source port number
					// of the packet to the client-side session information (for some NAT)
					se->YourPort = p->SrcPort;
				}
			}
		}
		return;
	}

	if (se == NULL && r->ServerMode && p->Size >= 40)
	{
		// Corresponding to a sudden change of port number on the client side.
		// The target session is a session which matches the client side IP address
		// and the key and the signature is verified
		UINT i;
		for (i = 0; i < LIST_NUM(r->SessionList);i++)
		{
			RUDP_SESSION *s = LIST_DATA(r->SessionList, i);

			if (CmpIpAddr(&s->YourIp, &p->SrcIP) == 0)
			{
				if (RUDPCheckSignOfRecvPacket(r, s, p->Data, p->Size))
				{
					// Signature matched
					se = s;
					break;
				}
			}
		}
	}

	if (se == NULL)
	{
		// There is no session
		if (r->ServerMode)
		{
			if (p->Size < 40)
			{
				bool ok = true;
				UCHAR ctoken_hash[SHA1_SIZE];

				Zero(ctoken_hash, sizeof(ctoken_hash));

				// Examine the quota of new session creation
				if (LIST_NUM(r->SessionList) >= RUDP_QUOTA_MAX_NUM_SESSIONS)
				{
					// Entire number of sessions exceeds the limit
					ok = false;
				}
				else if (r->NatT_EnableSourceIpValidation && RUDPIsIpInValidateList(r, &p->SrcIP) == false)
				{
					// Invalid source IP address, which is not registered on the validated source IP address list
					ok = false;
				}
				else
				{
					UINT i;
					// Check the number of sessions per IP address
					UINT num = 0;

					for (i = 0;i < LIST_NUM(r->SessionList);i++)
					{
						RUDP_SESSION *se = LIST_DATA(r->SessionList, i);

						if (CmpIpAddr(&se->YourIp, &p->SrcIP) == 0)
						{
							num++;
						}
					}

					if (num >= RUDP_QUOTA_MAX_NUM_SESSIONS_PER_IP)
					{
						// Limit exceeded the number of sessions per IP address
						ok = false;
					}
				}


				if (ok)
				{
					char ip_str[64];

					// Create a session since a new session creation request packet was received
					se = RUDPNewSession(true, &p->DstIP, p->DestPort, &p->SrcIP, p->SrcPort, p->Data);
					se->Status = RUDP_SESSION_STATUS_ESTABLISHED;
					Insert(r->SessionList, se);

					IPToStr(ip_str, sizeof(ip_str), &p->SrcIP);
					Debug("RUDPNewSession %X %s:%u\n", se, ip_str, p->SrcPort);

					if (r->Protocol == RUDP_PROTOCOL_ICMP)
					{
						// In case of ICMP, save the ICMP TYPE number to use
						se->Icmp_Type = (p->Type == ICMP_TYPE_INFORMATION_REQUEST ? ICMP_TYPE_INFORMATION_REPLY : p->Type);
					}
					else if (r->Protocol == RUDP_PROTOCOL_DNS)
					{
						// Save the Tran ID to be used if it's a DNS
						se->Dns_TranId = (USHORT)p->Type;
					}
				}
			}
		}
	}
	else
	{
		if (p->Size < 40)
		{
			if (r->ServerMode)
			{
				if (Cmp(se->Key_Init, p->Data, SHA1_SIZE) == 0)
				{
					// New session creation request packet have received more than once. reply an ACK immediately for second and subsequent
					se->LastSentTick = 0;

					// Update the endpoint information
					Copy(&se->YourIp, &p->SrcIP, sizeof(IP));
					se->YourPort = p->SrcPort;

					if (r->Protocol == RUDP_PROTOCOL_ICMP)
					{
						// In case of ICMP, save the ICMP TYPE number to use
						se->Icmp_Type = (p->Type == ICMP_TYPE_INFORMATION_REQUEST ? ICMP_TYPE_INFORMATION_REPLY : p->Type);
					}
					else if (r->Protocol == RUDP_PROTOCOL_DNS)
					{
						// Save the Tran ID to be used if it's a DNS
						se->Dns_TranId = (USHORT)p->Type;
					}
				}
				else
				{
					// Since the different session creation request packet have been received from the same end point, ignore it
				}
			}
		}
		else
		{
			// Process the received packet
			if (RUDPProcessRecvPacket(r, se, p->Data, p->Size) || RUDPProcessBulkRecvPacket(r, se, p->Data, p->Size))
			{
				// Update endpoint information (only the port number)
				//Copy(&se->YourIp, &p->SrcIP, sizeof(IP));
				se->YourPort = p->SrcPort;

				if (r->Protocol == RUDP_PROTOCOL_ICMP)
				{
					// In case of ICMP, save the ICMP TYPE number to use
					if (r->ServerMode)
					{
						se->Icmp_Type = (p->Type == ICMP_TYPE_INFORMATION_REQUEST ? ICMP_TYPE_INFORMATION_REPLY : p->Type);
					}
					else
					{
						se->Icmp_Type = (p->Type == ICMP_TYPE_INFORMATION_REPLY ? ICMP_TYPE_INFORMATION_REQUEST : p->Type);
					}
				}
				else if (r->Protocol == RUDP_PROTOCOL_DNS)
				{
					if (r->ServerMode)
					{
						// Save the Tran ID to be used if it's a DNS
						se->Dns_TranId = (USHORT)p->Type;
					}
				}
			}
		}
	}
}