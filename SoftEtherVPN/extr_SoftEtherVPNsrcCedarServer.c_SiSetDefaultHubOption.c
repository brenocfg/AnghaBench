#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int NoIPv6DefaultRouterInRAWhenIPv6; int ManageOnlyPrivateIP; int ManageOnlyLocalUnicastIPv6; int NoMacAddressLog; int NoDhcpPacketLogOutsideHub; int RemoveDefGwOnDhcpForLocalhost; int /*<<< orphan*/  FloodingSendQueueBufferQuota; int /*<<< orphan*/  AccessListIncludeFileCacheLifetime; int /*<<< orphan*/  VlanTypeId; scalar_t__ MaxSession; } ;
typedef  TYPE_1__ HUB_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_LIST_INCLUDE_FILE_CACHE_LIFETIME ; 
 int /*<<< orphan*/  DEFAULT_FLOODING_QUEUE_LENGTH ; 
 int /*<<< orphan*/  MAC_PROTO_TAGVLAN ; 

void SiSetDefaultHubOption(HUB_OPTION *o)
{
	// Validate arguments
	if (o == NULL)
	{
		return;
	}

	o->MaxSession = 0;
	o->VlanTypeId = MAC_PROTO_TAGVLAN;
	o->NoIPv6DefaultRouterInRAWhenIPv6 = true;
	o->ManageOnlyPrivateIP = true;
	o->ManageOnlyLocalUnicastIPv6 = true;
	o->NoMacAddressLog = true;
	o->NoDhcpPacketLogOutsideHub = true;
	o->AccessListIncludeFileCacheLifetime = ACCESS_LIST_INCLUDE_FILE_CACHE_LIFETIME;
	o->RemoveDefGwOnDhcpForLocalhost = true;
	o->FloodingSendQueueBufferQuota = DEFAULT_FLOODING_QUEUE_LENGTH;
}