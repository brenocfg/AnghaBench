#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_15__ {int /*<<< orphan*/  ref; } ;
struct TYPE_14__ {int /*<<< orphan*/  IsRawIpMode; } ;
struct TYPE_13__ {TYPE_2__* Eth; int /*<<< orphan*/  IsIpRawMode; int /*<<< orphan*/  MainThread; int /*<<< orphan*/  Cancel; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  Sock2; int /*<<< orphan*/  Ipc; TYPE_3__* Cedar; int /*<<< orphan*/  Sock1; } ;
typedef  TYPE_1__ NATIVE_STACK ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_2__ ETH ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Debug (char*,char*) ; 
 int /*<<< orphan*/  EthGetCancel (TYPE_2__*) ; 
 int /*<<< orphan*/  GetLocalHostIP4 (int /*<<< orphan*/ *) ; 
 TYPE_3__* NewCedar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewIPCBySock (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewSocketPair (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  NsGenMacAddress (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  NsMainThread ; 
 TYPE_2__* OpenEth (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseCedar (TYPE_3__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

NATIVE_STACK *NewNativeStack(CEDAR *cedar, char *device_name, char *mac_address_seed)
{
	ETH *eth;
	NATIVE_STACK *a;
	IP localhost;
	char tmp[64];
	bool release_cedar = false;
	// Validate arguments
	if (device_name == NULL || mac_address_seed == NULL)
	{
		return NULL;
	}

	GetLocalHostIP4(&localhost);

	// Open the Eth device
	eth = OpenEth(device_name, false, false, NULL);
	if (eth == NULL)
	{
		return NULL;
	}

	if (cedar == NULL)
	{
		cedar = NewCedar(NULL, NULL);
		release_cedar = true;
	}

	a = ZeroMalloc(sizeof(NATIVE_STACK));

	NewSocketPair(&a->Sock1, &a->Sock2, &localhost, 1, &localhost, 1);

	a->Cedar = cedar;
	AddRef(a->Cedar->ref);

	NsGenMacAddress(a->MacAddress, mac_address_seed, device_name);

	BinToStr(tmp, sizeof(tmp), a->MacAddress, sizeof(a->MacAddress));
	Debug("NewNativeStack: MAC Address = %s\n", tmp);

	a->Ipc = NewIPCBySock(cedar, a->Sock2, a->MacAddress);

	StrCpy(a->DeviceName, sizeof(a->DeviceName), device_name);

	a->Eth = eth;
	a->Cancel = EthGetCancel(eth);

	a->MainThread = NewThread(NsMainThread, a);

	if (release_cedar)
	{
		ReleaseCedar(cedar);
	}

	a->IsIpRawMode = a->Eth->IsRawIpMode;

	return a;
}