#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_54__   TYPE_9__ ;
typedef  struct TYPE_53__   TYPE_8__ ;
typedef  struct TYPE_52__   TYPE_7__ ;
typedef  struct TYPE_51__   TYPE_6__ ;
typedef  struct TYPE_50__   TYPE_5__ ;
typedef  struct TYPE_49__   TYPE_4__ ;
typedef  struct TYPE_48__   TYPE_3__ ;
typedef  struct TYPE_47__   TYPE_2__ ;
typedef  struct TYPE_46__   TYPE_1__ ;
typedef  struct TYPE_45__   TYPE_13__ ;
typedef  struct TYPE_44__   TYPE_12__ ;
typedef  struct TYPE_43__   TYPE_11__ ;
typedef  struct TYPE_42__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ret ;
typedef  int /*<<< orphan*/  magic_cookie ;
typedef  int /*<<< orphan*/  client_mac ;
typedef  int /*<<< orphan*/  client_ip ;
struct TYPE_54__ {size_t NumExistingRoutes; TYPE_12__* Entries; } ;
struct TYPE_52__ {int DhcpExpire; int DhcpMask; int HostIP; scalar_t__ DhcpGateway; int UseNat; int /*<<< orphan*/  DhcpDomain; int /*<<< orphan*/  DhcpPendingLeaseList; TYPE_9__ PushRoute; int /*<<< orphan*/  DhcpDns2; int /*<<< orphan*/  DhcpDns; int /*<<< orphan*/  DhcpLeaseList; scalar_t__ DhcpId; TYPE_5__* NativeNat; } ;
typedef  TYPE_7__ VH ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_49__ {TYPE_3__* UDPHeader; } ;
struct TYPE_47__ {TYPE_1__* IPv4Header; } ;
struct TYPE_51__ {TYPE_13__* DHCPv4Header; } ;
struct TYPE_53__ {int PacketSize; TYPE_4__ L4; TYPE_2__ L3; int /*<<< orphan*/ * MacAddressSrc; scalar_t__ MacHeader; TYPE_6__ L7; } ;
struct TYPE_50__ {int* CurrentMacAddress; } ;
struct TYPE_48__ {int /*<<< orphan*/  SrcPort; } ;
struct TYPE_46__ {scalar_t__ SrcIP; } ;
struct TYPE_45__ {int TransactionId; int OpCode; int /*<<< orphan*/  HardwareAddressSize; int /*<<< orphan*/  HardwareType; int /*<<< orphan*/  ClientMacAddress; } ;
struct TYPE_44__ {int Exists; int /*<<< orphan*/  SubnetMaskLen; TYPE_9__ SubnetMask; TYPE_9__ Network; TYPE_9__ Gateway; } ;
struct TYPE_43__ {scalar_t__ Id; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  MacAddress; } ;
struct TYPE_42__ {scalar_t__ Opcode; scalar_t__ RequestedIp; int ServerAddress; int LeaseTime; int SubnetMask; scalar_t__ Gateway; int /*<<< orphan*/  DomainName; int /*<<< orphan*/  Hostname; TYPE_9__ ClasslessRoute; int /*<<< orphan*/  DnsServer2; int /*<<< orphan*/  DnsServer; } ;
typedef  TYPE_8__ PKT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_9__ IP ;
typedef  TYPE_10__ DHCP_OPTION_LIST ;
typedef  TYPE_11__ DHCP_LEASE ;
typedef  int /*<<< orphan*/  DHCP_CLASSLESS_ROUTE_TABLE ;
typedef  TYPE_12__ DHCP_CLASSLESS_ROUTE ;
typedef  TYPE_13__ DHCPV4_HEADER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BuildDhcpOption (TYPE_10__*) ; 
 int /*<<< orphan*/ * BuildDhcpOptionsBuf (int /*<<< orphan*/ *) ; 
 scalar_t__ Cmp (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  Copy (TYPE_9__*,TYPE_9__*,int) ; 
 scalar_t__ DHCP_ACK ; 
 scalar_t__ DHCP_DISCOVER ; 
 scalar_t__ DHCP_INFORM ; 
 int DHCP_MAGIC_COOKIE ; 
 scalar_t__ DHCP_NACK ; 
 scalar_t__ DHCP_OFFER ; 
 scalar_t__ DHCP_REQUEST ; 
 int /*<<< orphan*/  Debug (char*,char*,char*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  Endian16 (int /*<<< orphan*/ ) ; 
 void* Endian32 (int) ; 
 int /*<<< orphan*/  Free (TYPE_10__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeDhcpLease (TYPE_11__*) ; 
 int /*<<< orphan*/  FreeDhcpOptions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GSF_DISABLE_PUSH_ROUTE ; 
 int /*<<< orphan*/ * GetBestClasslessRoute (TYPE_9__*,TYPE_9__*) ; 
 scalar_t__ GetGlobalServerFlag (int /*<<< orphan*/ ) ; 
 int INFINITE ; 
 int /*<<< orphan*/  IPAnd4 (TYPE_9__*,TYPE_9__*,TYPE_9__*) ; 
 int /*<<< orphan*/  IPToStr (char*,int,TYPE_9__*) ; 
 int /*<<< orphan*/  IPToStr32 (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ IsIpcMacAddress (int /*<<< orphan*/ *) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 size_t MAX_DHCP_CLASSLESS_ROUTE_ENTRIES ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MacToStr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLog (TYPE_7__*,char*,scalar_t__,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NN_HOSTNAME_STARTWITH ; 
 int /*<<< orphan*/  NN_HOSTNAME_STARTWITH2 ; 
 TYPE_11__* NewDhcpLease (int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 TYPE_10__* ParseDhcpOptionList (int /*<<< orphan*/ *,int) ; 
 TYPE_11__* SearchDhcpLeaseByIp (TYPE_7__*,int) ; 
 TYPE_11__* SearchDhcpPendingLeaseByIp (TYPE_7__*,int) ; 
 int ServeDhcpDiscover (TYPE_7__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int ServeDhcpRequest (TYPE_7__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ StartWith (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SubnetMaskToInt (TYPE_9__*) ; 
 int /*<<< orphan*/  UINTToIP (TYPE_9__*,int) ; 
 int /*<<< orphan*/  VirtualDhcpSend (TYPE_7__*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_10__*,int) ; 

void VirtualDhcpServer(VH *v, PKT *p)
{
	DHCPV4_HEADER *dhcp;
	UCHAR *data;
	UINT size;
	UINT dhcp_header_size;
	UINT dhcp_data_offset;
	UINT tran_id;
	UINT magic_cookie = Endian32(DHCP_MAGIC_COOKIE);
	bool ok;
	DHCP_OPTION_LIST *opt;
	// Validate arguments
	if (v == NULL || p == NULL)
	{
		return;
	}

	if (v->NativeNat != NULL)
	{
		if (Cmp(p->MacAddressSrc, v->NativeNat->CurrentMacAddress, 6) == 0)
		{
			// DHCP server is kept from responding for the native NAT interface
			// ** Not be needed to return yet **
			//return;
		}
	}

	dhcp = p->L7.DHCPv4Header;

	tran_id = Endian32(dhcp->TransactionId);

	// Get the DHCP data and size
	dhcp_header_size = sizeof(DHCPV4_HEADER);
	dhcp_data_offset = (UINT)(((UCHAR *)p->L7.DHCPv4Header) - ((UCHAR *)p->MacHeader) + dhcp_header_size);
	data = ((UCHAR *)dhcp) + dhcp_header_size;
	size = p->PacketSize - dhcp_data_offset;
	if (dhcp_header_size < 5)
	{
		// Data size is invalid
		return;
	}

	// Search for Magic Cookie
	ok = false;
	while (size >= 5)
	{
		if (Cmp(data, &magic_cookie, sizeof(magic_cookie)) == 0)
		{
			// Found
			data += 4;
			size -= 4;
			ok = true;
			break;
		}
		data++;
		size--;
	}

	if (ok == false)
	{
		// The packet is invalid
		return;
	}

	// Parse DHCP options list
	opt = ParseDhcpOptionList(data, size);
	if (opt == NULL)
	{
		// The packet is invalid
		return;
	}

	if (StartWith(opt->Hostname, NN_HOSTNAME_STARTWITH) || StartWith(opt->Hostname, NN_HOSTNAME_STARTWITH2))
	{
		Free(opt);
		return;
	}

	if (dhcp->OpCode == 1 && (opt->Opcode == DHCP_DISCOVER || opt->Opcode == DHCP_REQUEST || opt->Opcode == DHCP_INFORM))
	{
		// Operate as the server
		UINT ip = 0;

		if (opt->RequestedIp == 0)
		{
			opt->RequestedIp = p->L3.IPv4Header->SrcIP;
		}
		if (opt->Opcode == DHCP_DISCOVER)
		{
			// Return an IP address that can be used
			ip = ServeDhcpDiscover(v, p->MacAddressSrc, opt->RequestedIp);
		}
		else if (opt->Opcode == DHCP_REQUEST)
		{
			// Determine the IP address
			ip = ServeDhcpRequest(v, p->MacAddressSrc, opt->RequestedIp);
		}

		if (ip != 0 || opt->Opcode == DHCP_INFORM)
		{
			// Respond if there is providable IP address

			if (opt->Opcode == DHCP_REQUEST)
			{
				DHCP_LEASE *d;
				char client_mac[MAX_SIZE];
				char client_ip[MAX_SIZE];

				// Remove old records with the same IP address
				d = SearchDhcpLeaseByIp(v, ip);
				if (d != NULL)
				{
					FreeDhcpLease(d);
					Delete(v->DhcpLeaseList, d);
				}

				d = SearchDhcpPendingLeaseByIp(v, ip);
				if (d != NULL)
				{
					FreeDhcpLease(d);
					Delete(v->DhcpPendingLeaseList, d);
				}

				// Create a new entry
				d = NewDhcpLease(v->DhcpExpire, p->MacAddressSrc, ip, v->DhcpMask, opt->Hostname);
				d->Id = ++v->DhcpId;
				Add(v->DhcpLeaseList, d);

				MacToStr(client_mac, sizeof(client_mac), d->MacAddress);
				IPToStr32(client_ip, sizeof(client_ip), d->IpAddress);

				NLog(v, "LH_NAT_DHCP_CREATED", d->Id, client_mac, client_ip, d->Hostname, v->DhcpExpire / 1000);
			}

			// Respond
			if (true)
			{
				DHCP_OPTION_LIST ret;
				LIST *o;
				Zero(&ret, sizeof(ret));

				ret.Opcode = (opt->Opcode == DHCP_DISCOVER ? DHCP_OFFER : DHCP_ACK);
				ret.ServerAddress = v->HostIP;
				if (v->DhcpExpire == INFINITE)
				{
					ret.LeaseTime = INFINITE;
				}
				else
				{
					ret.LeaseTime = Endian32(v->DhcpExpire / 1000);
				}

				if (opt->Opcode == DHCP_INFORM)
				{
					ret.LeaseTime = 0;
				}

				StrCpy(ret.DomainName, sizeof(ret.DomainName), v->DhcpDomain);
				ret.SubnetMask = v->DhcpMask;
				ret.DnsServer = v->DhcpDns;
				ret.DnsServer2 = v->DhcpDns2;
				ret.Gateway = v->DhcpGateway;

				if (GetGlobalServerFlag(GSF_DISABLE_PUSH_ROUTE) == 0)
				{
					Copy(&ret.ClasslessRoute, &v->PushRoute, sizeof(DHCP_CLASSLESS_ROUTE_TABLE));

					if (IsIpcMacAddress(p->MacAddressSrc))
					{
						if (ret.Gateway == 0)
						{
							// If the default gateway is not specified, add the static routing table
							// entry for the local IP subnet
							// (for PPP clients)
							IP dhcp_ip;
							IP dhcp_mask;
							IP dhcp_network;

							UINTToIP(&dhcp_ip, ip);

							if (ip == 0)
							{
								UINTToIP(&dhcp_ip, p->L3.IPv4Header->SrcIP);
							}

							UINTToIP(&dhcp_mask, v->DhcpMask);

							IPAnd4(&dhcp_network, &dhcp_ip, &dhcp_mask);

							if (GetBestClasslessRoute(&ret.ClasslessRoute, &dhcp_ip) == NULL)
							{
								if (ret.ClasslessRoute.NumExistingRoutes < MAX_DHCP_CLASSLESS_ROUTE_ENTRIES)
								{
									DHCP_CLASSLESS_ROUTE *cr = &ret.ClasslessRoute.Entries[ret.ClasslessRoute.NumExistingRoutes];

									cr->Exists = true;

									UINTToIP(&cr->Gateway, v->HostIP);

									if (v->UseNat == false && ret.ClasslessRoute.NumExistingRoutes >= 1)
									{
										Copy(&cr->Gateway, &ret.ClasslessRoute.Entries[0].Gateway, sizeof(IP));
									}

									Copy(&cr->Network, &dhcp_network, sizeof(IP));
									Copy(&cr->SubnetMask, &dhcp_mask, sizeof(IP));
									cr->SubnetMaskLen = SubnetMaskToInt(&dhcp_mask);

									ret.ClasslessRoute.NumExistingRoutes++;
								}
							}
						}
					}
				}

				if (opt->Opcode != DHCP_INFORM)
				{
					char client_mac[MAX_SIZE];
					char client_ip[64];
					IP ips;

					BinToStr(client_mac, sizeof(client_mac), p->MacAddressSrc, 6);
					UINTToIP(&ips, ip);
					IPToStr(client_ip, sizeof(client_ip), &ips);

					if (ret.Opcode == DHCP_OFFER)
					{
						// DHCP_OFFER
						DHCP_LEASE *d = NewDhcpLease(5000, p->MacAddressSrc, ip, v->DhcpMask, opt->Hostname);
						d->Id = LIST_NUM(v->DhcpPendingLeaseList);
						Add(v->DhcpPendingLeaseList, d);

						Debug("VirtualDhcpServer(): %s has been marked as pending for %s\n", client_ip, client_mac);
					}
					else
					{
						// DHCP_ACK
						Debug("VirtualDhcpServer(): %s has been assigned to %s\n", client_ip, client_mac);
					}
				}

				// Build a DHCP option
				o = BuildDhcpOption(&ret);
				if (o != NULL)
				{
					BUF *b = BuildDhcpOptionsBuf(o);
					if (b != NULL)
					{
						UINT dest_ip = p->L3.IPv4Header->SrcIP;
						if (dest_ip == 0)
						{
							dest_ip = 0xffffffff;
						}
						// Transmission
						VirtualDhcpSend(v, tran_id, dest_ip, Endian16(p->L4.UDPHeader->SrcPort),
							ip, dhcp->ClientMacAddress, b, dhcp->HardwareType, dhcp->HardwareAddressSize);

						// Release the memory
						FreeBuf(b);
					}
					FreeDhcpOptions(o);
				}
			}
		}
		else
		{
			// There is no IP address that can be provided
			DHCP_OPTION_LIST ret;
			LIST *o;
			Zero(&ret, sizeof(ret));

			ret.Opcode = DHCP_NACK;
			ret.ServerAddress = v->HostIP;
			StrCpy(ret.DomainName, sizeof(ret.DomainName), v->DhcpDomain);
			ret.SubnetMask = v->DhcpMask;

			// Build the DHCP option
			o = BuildDhcpOption(&ret);
			if (o != NULL)
			{
				BUF *b = BuildDhcpOptionsBuf(o);
				if (b != NULL)
				{
					UINT dest_ip = p->L3.IPv4Header->SrcIP;
					if (dest_ip == 0)
					{
						dest_ip = 0xffffffff;
					}
					// Transmission
					VirtualDhcpSend(v, tran_id, dest_ip, Endian16(p->L4.UDPHeader->SrcPort),
						ip, dhcp->ClientMacAddress, b, dhcp->HardwareType, dhcp->HardwareAddressSize);

					// Release the memory
					FreeBuf(b);
				}
				FreeDhcpOptions(o);
			}
		}
	}

	// Release the memory
	Free(opt);
}