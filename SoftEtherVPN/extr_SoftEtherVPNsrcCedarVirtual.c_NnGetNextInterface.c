#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  gateway_ip ;
typedef  int /*<<< orphan*/  dhcp_ip ;
typedef  int /*<<< orphan*/  client_mask ;
typedef  int /*<<< orphan*/  client_ip ;
typedef  scalar_t__ UINT ;
struct TYPE_26__ {int /*<<< orphan*/  Gateway; int /*<<< orphan*/  DnsServer2; int /*<<< orphan*/  DnsServer; int /*<<< orphan*/  ClasslessRoute; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  ClientAddress; int /*<<< orphan*/  ServerAddress; } ;
struct TYPE_25__ {int NextWaitTimeForRetry; scalar_t__ LastInterfaceDeviceHash; scalar_t__ LastHostAddressHash; scalar_t__ LastInterfaceIndex; TYPE_6__* CurrentMacAddress; scalar_t__ FailedCount; int /*<<< orphan*/  HaltTube2; TYPE_2__* v; } ;
struct TYPE_24__ {int /*<<< orphan*/  DnsServerIP2; int /*<<< orphan*/  DnsServerIP; TYPE_12__* Ipc; TYPE_6__ CurrentDhcpOptionList; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  MacAddress; } ;
struct TYPE_23__ {scalar_t__ NumTokens; char** Token; } ;
struct TYPE_22__ {int /*<<< orphan*/  MacAddress; TYPE_1__* HubOption; } ;
struct TYPE_21__ {scalar_t__ DisableIpRawModeSecureNAT; scalar_t__ DisableKernelModeSecureNAT; } ;
struct TYPE_20__ {int /*<<< orphan*/  ClientHostname; TYPE_6__* MacAddress; } ;
typedef  TYPE_3__ TOKEN_LIST ;
typedef  TYPE_4__ NATIVE_STACK ;
typedef  TYPE_5__ NATIVE_NAT ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_6__ DHCP_OPTION_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Copy (TYPE_6__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  Format (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FreeNativeStack (TYPE_4__*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_3__*) ; 
 scalar_t__ GetEthDeviceHash () ; 
 TYPE_3__* GetEthListEx (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ GetHostIPAddressHash32 () ; 
 scalar_t__ INFINITE ; 
 scalar_t__ IPCDhcpAllocateIP (TYPE_12__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPCSetIPv4Parameters (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToStr32 (char*,int,int /*<<< orphan*/ ) ; 
 int IsInLinesFile (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ IsZeroIP (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NN_HOSTNAME_FORMAT ; 
 int NN_NEXT_WAIT_TIME_FOR_DEVICE_ENUM ; 
 int /*<<< orphan*/  NN_NEXT_WAIT_TIME_MAX_FAIL_COUNT ; 
 int /*<<< orphan*/  NN_NO_NATIVE_NAT_FILENAME ; 
 TYPE_4__* NewNativeStack (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ NnTestConnectivity (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetIP (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  StrLower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_6__*,int) ; 

NATIVE_STACK *NnGetNextInterface(NATIVE_NAT *t)
{
	NATIVE_STACK *ret = NULL;
	UINT current_hash;
	TOKEN_LIST *device_list;
	UINT i;
	char tmp[MAX_SIZE];
	char *dev_name;
	UINT current_ip_hash;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	t->NextWaitTimeForRetry = NN_NEXT_WAIT_TIME_FOR_DEVICE_ENUM * MIN((t->FailedCount + 1), NN_NEXT_WAIT_TIME_MAX_FAIL_COUNT);

	// Get the device list
	device_list = GetEthListEx(NULL,
		!(t->v->HubOption != NULL && t->v->HubOption->DisableKernelModeSecureNAT),
		!(t->v->HubOption != NULL && t->v->HubOption->DisableIpRawModeSecureNAT));

	if (device_list == NULL || device_list->NumTokens == 0)
	{
		// Device list acquisition failure (Or no device acquired as a result)
		FreeToken(device_list);
		t->FailedCount++;
		return NULL;
	}

	current_hash = GetEthDeviceHash();
	current_ip_hash = GetHostIPAddressHash32();

	if (t->LastInterfaceDeviceHash != current_hash || t->LastHostAddressHash != current_ip_hash)
	{
		// Device list is altered from the previous search
		t->LastInterfaceIndex = INFINITE;
		t->FailedCount = 0;
	}

	t->LastInterfaceDeviceHash = current_hash;
	t->LastHostAddressHash = current_ip_hash;

	if (t->LastInterfaceIndex == INFINITE)
	{
		i = 0;
	}
	else
	{
		i = t->LastInterfaceIndex + 1;
		if (i >= device_list->NumTokens)
		{
			i = 0;
		}
	}

	if ((i + 1) == device_list->NumTokens)
	{
		// Searched to the end
		t->LastInterfaceIndex = INFINITE;

		// Increase the number of search failures by one
		t->FailedCount++;
	}
	else
	{
		// It is not the end yet
		t->LastInterfaceIndex = i;
		t->NextWaitTimeForRetry = 0;
	}

	dev_name = device_list->Token[i];

	if (IsInLinesFile(NN_NO_NATIVE_NAT_FILENAME, dev_name, true) == false)
	{
		// Try to open the device
		BinToStr(tmp, sizeof(tmp), t->v->MacAddress, 6);
		ret = NewNativeStack(NULL, dev_name, tmp);

		if (ret != NULL)
		{
			// Test whether an IP address can be obtained from a DHCP server
			DHCP_OPTION_LIST opt;

			Copy(t->CurrentMacAddress, ret->Ipc->MacAddress, 6);

			Zero(&opt, sizeof(opt));

			BinToStr(tmp, sizeof(tmp), ret->MacAddress, 6);
			Format(ret->Ipc->ClientHostname, sizeof(ret->Ipc->ClientHostname), NN_HOSTNAME_FORMAT, tmp);
			StrLower(ret->Ipc->ClientHostname);

			Debug("IPCDhcpAllocateIP for %s\n", ret->DeviceName);
			if (IPCDhcpAllocateIP(ret->Ipc, &opt, t->HaltTube2))
			{
				char client_ip[64];
				char dhcp_ip[64];
				char client_mask[64];
				char gateway_ip[64];

				IP ip;
				IP subnet;
				IP gw;

				IPToStr32(client_ip, sizeof(client_ip), opt.ClientAddress);
				IPToStr32(client_mask, sizeof(client_mask), opt.SubnetMask);
				IPToStr32(dhcp_ip, sizeof(dhcp_ip), opt.ServerAddress);
				IPToStr32(gateway_ip, sizeof(gateway_ip), opt.Gateway);

				Debug("DHCP: client_ip=%s, client_mask=%s, dhcp_ip=%s, gateway_ip=%s\n",
					client_ip, client_mask, dhcp_ip, gateway_ip);

				Copy(&ret->CurrentDhcpOptionList, &opt, sizeof(DHCP_OPTION_LIST));

				// IP parameter settings
				UINTToIP(&ip, opt.ClientAddress);
				UINTToIP(&subnet, opt.SubnetMask);
				UINTToIP(&gw, opt.Gateway);

				IPCSetIPv4Parameters(ret->Ipc, &ip, &subnet, &gw, &opt.ClasslessRoute);

				// Determine the DNS server to use
				UINTToIP(&ret->DnsServerIP, opt.DnsServer);
				UINTToIP(&ret->DnsServerIP2, opt.DnsServer2);
				if (IsZeroIP(&ret->DnsServerIP))
				{
					// Use 8.8.8.8 instead If the DNS is not assigned from the DHCP server
					SetIP(&ret->DnsServerIP, 8, 8, 8, 8);
				}
				if (IsZeroIP(&ret->DnsServerIP2))
				{
					// Use 8.8.4.4 instead If the DNS is not assigned from the DHCP server
					SetIP(&ret->DnsServerIP2, 8, 8, 4, 4);
				}

				// Connectivity test
				// (always fail if the default gateway is not set)
				if (opt.Gateway != 0 &&
					NnTestConnectivity(ret, t->HaltTube2))
				{
					// Reset the number of search failures
					t->FailedCount = 0;
					Debug("Connectivity OK.\n");
				}
				else
				{
					Debug("Connectivity Failed.\n");
					FreeNativeStack(ret);
					ret = NULL;
				}
			}
			else
			{
				Debug("DHCP Failed.\n");
				FreeNativeStack(ret);
				ret = NULL;

				Zero(t->CurrentMacAddress, sizeof(t->CurrentMacAddress));
			}
		}
	}

	FreeToken(device_list);

	return ret;
}