#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redirect_url ;
typedef  int USHORT ;
typedef  scalar_t__ UINT ;
struct TYPE_31__ {int /*<<< orphan*/  AccessList; TYPE_1__* Option; } ;
struct TYPE_27__ {TYPE_4__* IPv4Header; } ;
struct TYPE_25__ {TYPE_6__* TCPHeader; } ;
struct TYPE_30__ {scalar_t__ TypeL3; int AccessChecked; scalar_t__ TypeL4; scalar_t__ PayloadSize; TYPE_5__ L3; TYPE_3__ L4; int /*<<< orphan*/  Loss; int /*<<< orphan*/  Jitter; int /*<<< orphan*/  Delay; TYPE_2__* MacHeader; } ;
struct TYPE_29__ {int FirstTimeHttpRedirect; scalar_t__ FirstTimeHttpAccessCheckIp; scalar_t__* FirstTimeHttpRedirectUrl; scalar_t__ NormalClient; } ;
struct TYPE_28__ {int Flag; int DstPort; } ;
struct TYPE_26__ {int Protocol; scalar_t__ DstIP; } ;
struct TYPE_24__ {int Protocol; } ;
struct TYPE_23__ {scalar_t__ FilterBPDU; scalar_t__ FilterNonIP; scalar_t__ FilterIPv6; scalar_t__ FilterIPv4; scalar_t__ FilterOSPF; scalar_t__ FilterPPPoE; } ;
struct TYPE_22__ {scalar_t__ DestUsernameHash; scalar_t__* RedirectUrl; int /*<<< orphan*/  Loss; int /*<<< orphan*/  Jitter; int /*<<< orphan*/  Delay; scalar_t__ Discard; } ;
typedef  TYPE_6__ TCP_HEADER ;
typedef  TYPE_7__ SESSION ;
typedef  TYPE_8__ PKT ;
typedef  TYPE_9__ HUB ;
typedef  TYPE_10__ ACCESS ;

/* Variables and functions */
 int Endian16 (int) ; 
 int /*<<< orphan*/  ForceRedirectToUrl (TYPE_9__*,TYPE_7__*,TYPE_8__*,char*) ; 
 int IsEmptyStr (scalar_t__*) ; 
 scalar_t__ IsPacketMaskedByAccessList (TYPE_7__*,TYPE_8__*,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IsTcpPacketNcsiHttpAccess (TYPE_8__*) ; 
 scalar_t__ L3_BPDU ; 
 scalar_t__ L3_IPV4 ; 
 scalar_t__ L3_IPV6 ; 
 scalar_t__ L4_TCP ; 
 TYPE_10__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_REDIRECT_URL_LEN ; 
 int /*<<< orphan*/  StrCpy (char*,int,scalar_t__*) ; 
 int TCP_ACK ; 
 int TCP_RST ; 
 int TCP_SYN ; 
 int TCP_URG ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

bool ApplyAccessListToStoredPacket(HUB *hub, SESSION *s, PKT *p)
{
	UINT i;
	bool pass = true;	// Pass by default
	bool use_redirect_url = false;
	char redirect_url[MAX_REDIRECT_URL_LEN + 1];
	// Validate arguments
	if (hub == NULL || s == NULL || p == NULL)
	{
		return false;
	}

	if (hub->Option != NULL && hub->Option->FilterPPPoE)
	{
		if (p->MacHeader != NULL)
		{
			USHORT proto = Endian16(p->MacHeader->Protocol);
			if (proto == 0x8863 || proto == 0x8864)
			{
				// PPPoE Filter
				return false;
			}
		}
	}

	if (hub->Option != NULL && hub->Option->FilterOSPF)
	{
		if (p->TypeL3 == L3_IPV4)
		{
			if (p->L3.IPv4Header != NULL)
			{
				if (p->L3.IPv4Header->Protocol == 89)
				{
					// OSPF Filter
					return false;
				}
			}
		}
	}

	if (hub->Option != NULL && hub->Option->FilterIPv4)
	{
		if (p->MacHeader != NULL)
		{
			USHORT proto = Endian16(p->MacHeader->Protocol);
			if (proto == 0x0800 || proto == 0x0806)
			{
				// IPv4 Filter
				return false;
			}
		}
	}

	if (hub->Option != NULL && hub->Option->FilterIPv6)
	{
		if (p->MacHeader != NULL)
		{
			USHORT proto = Endian16(p->MacHeader->Protocol);
			if (proto == 0x86dd)
			{
				// IPv6 Filter
				return false;
			}
		}
	}

	if (hub->Option != NULL && hub->Option->FilterNonIP)
	{
		if (p->MacHeader != NULL)
		{
			USHORT proto = Endian16(p->MacHeader->Protocol);
			if (!(proto == 0x86dd || proto == 0x0800 || proto == 0x0806))
			{
				// Non-IP Filter
				return false;
			}
		}
	}

	if (hub->Option != NULL && hub->Option->FilterBPDU)
	{
		if (p->MacHeader != NULL)
		{
			if (p->TypeL3 == L3_BPDU)
			{
				// BPDU Filter
				return false;
			}
		}
	}

	LockList(hub->AccessList);
	{
		for (i = 0;i < LIST_NUM(hub->AccessList);i++)
		{
			ACCESS *a = LIST_DATA(hub->AccessList, i);

			if (a->DestUsernameHash != 0)
			{
				// If a destination user name is specified, suspend the scanning of the list.
				break;
			}

			if (IsPacketMaskedByAccessList(s, p, a, 0, 0, NULL))
			{
				// Determine the pass or discard the packet
				pass = a->Discard ? false : true;

				// Packets determined processing here is not scanned when leaving the HUB.
				p->AccessChecked = true;

				// Copy of the parameters of the delay jitter packet loss
				p->Delay = a->Delay;
				p->Jitter = a->Jitter;
				p->Loss = a->Loss;

				if (a->RedirectUrl[0] != 0)
				{
					// There is a setting of URL redirection in the access list
					if ((p->TypeL3 == L3_IPV4 || p->TypeL3 == L3_IPV6) &&
						p->TypeL4 == L4_TCP)
					{
						TCP_HEADER *tcp = p->L4.TCPHeader;

						// Examine whether this packet is a TCP data packet
						if (tcp != NULL)
						{
							if (tcp->Flag & TCP_ACK)
							{
								if ((tcp->Flag & TCP_SYN) == 0 &&
									(tcp->Flag & TCP_RST) == 0 &&
									(tcp->Flag & TCP_URG) == 0)
								{
									if (p->PayloadSize != 0)
									{
										// Do URL redirection
										use_redirect_url = true;
										StrCpy(redirect_url, sizeof(redirect_url), a->RedirectUrl);
									}
								}
							}
						}
					}
				}

				// Complete the scanning of the list here
				break;
			}
		}
	}
	UnlockList(hub->AccessList);

	if (pass)
	{
		if (s->FirstTimeHttpRedirect && s->FirstTimeHttpAccessCheckIp != 0)
		{
			if ((p->TypeL3 == L3_IPV4 || p->TypeL3 == L3_IPV6) &&
				p->TypeL4 == L4_TCP)
			{
				TCP_HEADER *tcp = p->L4.TCPHeader;

				// Examine whether this packet is a TCP data packet
				if (tcp != NULL)
				{
					if (tcp->DstPort == Endian16(80))
					{
						if (p->L3.IPv4Header->DstIP == s->FirstTimeHttpAccessCheckIp)
						{
							s->FirstTimeHttpRedirect = false;
						}
						else if (tcp->Flag & TCP_ACK)
						{
							if ((tcp->Flag & TCP_SYN) == 0 &&
								(tcp->Flag & TCP_RST) == 0 &&
								(tcp->Flag & TCP_URG) == 0)
							{
								if (p->PayloadSize != 0)
								{
									if (IsTcpPacketNcsiHttpAccess(p) == false)
									{
/*										char tmp[4000];
										Zero(tmp, sizeof(tmp));
										Copy(tmp, p->Payload, p->PayloadSize);
										Debug("HTTP: %s\n", tmp);*/
										if (IsEmptyStr(s->FirstTimeHttpRedirectUrl) == false)
										{
											use_redirect_url = true;
											StrCpy(redirect_url, sizeof(redirect_url), s->FirstTimeHttpRedirectUrl);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (use_redirect_url)
	{
		if (s->NormalClient)
		{
			// In the case of a normal VPN client (Not a local bridge, a SecureNAT, and not a virtual L3 switch),
			// process URL redirection and discard the packet
			ForceRedirectToUrl(hub, s, p, redirect_url);
		}
		else
		{
			// Discard packets that is sent from the sessions such as local bridge,
			// SecureNAT, virtual L3 switch
		}

		pass = false;
	}

	return pass;
}