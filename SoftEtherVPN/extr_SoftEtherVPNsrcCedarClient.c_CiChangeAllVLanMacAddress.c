#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  s ;
typedef  size_t UINT ;
typedef  int UCHAR ;
struct TYPE_9__ {char* DeviceName; int /*<<< orphan*/  MacAddress; } ;
struct TYPE_8__ {size_t NumItem; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  DeviceName; TYPE_2__** Items; } ;
typedef  TYPE_1__ RPC_CLIENT_SET_VLAN ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_VLAN_ITEM ;
typedef  TYPE_1__ RPC_CLIENT_ENUM_VLAN ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CiFreeClientEnumVLan (TYPE_1__*) ; 
 scalar_t__ CtEnumVLan (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CtSetVLan (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  GenMacAddress (int*) ; 
 int /*<<< orphan*/  MacToStr (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ StrToMac (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void CiChangeAllVLanMacAddress(CLIENT *c)
{
	RPC_CLIENT_ENUM_VLAN t;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	Zero(&t, sizeof(t));
	if (CtEnumVLan(c, &t))
	{
		UINT i;

		for (i = 0;i < t.NumItem;i++)
		{
			RPC_CLIENT_ENUM_VLAN_ITEM *e = t.Items[i];
			UCHAR mac[6];

			if (StrToMac(mac, e->MacAddress) && ((mac[0] == 0x00 && mac[1] == 0xAC) || (mac[0] == 0x5E)))
			{
				char *name = e->DeviceName;
				RPC_CLIENT_SET_VLAN s;
				UCHAR mac[6];

				GenMacAddress(mac);

				Zero(&s, sizeof(s));
				StrCpy(s.DeviceName, sizeof(s.DeviceName), name);

				MacToStr(s.MacAddress, sizeof(s.MacAddress), mac);

				CtSetVLan(c, &s);
			}
		}

		CiFreeClientEnumVLan(&t);
	}
}