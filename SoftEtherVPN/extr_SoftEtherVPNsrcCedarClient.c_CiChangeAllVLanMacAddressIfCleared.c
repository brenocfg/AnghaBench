#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */

void CiChangeAllVLanMacAddressIfCleared(CLIENT *c)
{
#ifdef	OS_WIN32
	RPC_CLIENT_ENUM_VLAN t;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	if (MsIsInfCatalogRequired() == false)
	{
		// Not required for other than Windows 8
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

			if (StrToMac(mac, e->MacAddress))
			{
				if (mac[0] == 0x00 &&
					mac[1] == 0x00 &&
					mac[2] == 0x01 &&
					mac[3] == 0x00 &&
					mac[4] == 0x00 &&
					mac[5] == 0x01)
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
		}

		CiFreeClientEnumVLan(&t);
	}
#endif	// OS_WIN32
}