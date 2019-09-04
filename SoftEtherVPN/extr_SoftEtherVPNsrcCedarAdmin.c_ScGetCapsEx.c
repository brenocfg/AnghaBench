#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  b ;
typedef  int UINT ;
struct TYPE_14__ {int Value; } ;
struct TYPE_13__ {int ServerBuildInt; scalar_t__ ServerType; int IsBridgeSupportedOs; int IsWinPcapNeeded; int /*<<< orphan*/  ServerProductName; } ;
struct TYPE_12__ {int NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ RPC_SERVER_INFO ;
typedef  TYPE_2__ RPC_BRIDGE_SUPPORT ;
typedef  int /*<<< orphan*/  RPC ;
typedef  int /*<<< orphan*/  CAPSLIST ;
typedef  TYPE_4__ CAPS ;

/* Variables and functions */
 int /*<<< orphan*/  AddCapsBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  AddCapsInt (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcServerInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 TYPE_4__* GetCaps (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* GetTableNameStartWith (char*) ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/ * NewCapsList () ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 scalar_t__ ScGetBridgeSupport (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ ScGetCaps (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScGetServerInfo (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ SearchStrEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

CAPSLIST *ScGetCapsEx(RPC *rpc)
{
	RPC_SERVER_INFO info;
	CAPSLIST *t;
	bool is_bridge = false;
	// Validate arguments
	if (rpc == NULL)
	{
		return NULL;
	}

	Zero(&info, sizeof(info));
	ScGetServerInfo(rpc, &info);

	t = ZeroMalloc(sizeof(CAPSLIST));

	// Try to get Caps by RPC
	if (ScGetCaps(rpc, t) != ERR_NO_ERROR)
	{
		UINT build;

		Free(t);
		t = NewCapsList();

		// Since acquisition of Caps went wrong, get build number
		build = info.ServerBuildInt;

		is_bridge = (SearchStrEx(info.ServerProductName, "bridge", 0, false) == INFINITE) ? false : true;

		AddCapsInt(t, "i_max_packet_size", 1514);

		if (is_bridge == false)
		{
			AddCapsInt(t, "i_max_hubs", 4096);
			AddCapsInt(t, "i_max_sessions", 4096);

			if (info.ServerType != SERVER_TYPE_FARM_MEMBER)
			{
				AddCapsInt(t, "i_max_users_per_hub", 10000);
				AddCapsInt(t, "i_max_groups_per_hub", 10000);
				AddCapsInt(t, "i_max_access_lists", 4096);
			}
			else
			{
				AddCapsInt(t, "i_max_users_per_hub", 0);
				AddCapsInt(t, "i_max_groups_per_hub", 0);
				AddCapsInt(t, "i_max_access_lists", 0);
			}
		}
		else
		{
			AddCapsInt(t, "i_max_hubs", 0);
			AddCapsInt(t, "i_max_sessions", 0);
			AddCapsInt(t, "i_max_users_per_hub", 0);
			AddCapsInt(t, "i_max_groups_per_hub", 0);
			AddCapsInt(t, "i_max_access_lists", 0);
		}

		AddCapsInt(t, "i_max_mac_tables", 10000);
		AddCapsInt(t, "i_max_ip_tables", 10000);

		if (info.ServerType == SERVER_TYPE_STANDALONE)
		{
			AddCapsBool(t, "b_support_securenat", (build >= 3600) ? true : false);
			AddCapsInt(t, "i_max_secnat_tables", 4096);
		}
		else
		{
			AddCapsBool(t, "b_support_securenat", false);
			AddCapsInt(t, "i_max_secnat_tables", 0);
		}

		if (is_bridge)
		{
			AddCapsBool(t, "b_bridge", true);
		}
		else if (info.ServerType == SERVER_TYPE_STANDALONE)
		{
			AddCapsBool(t, "b_standalone", true);
		}
		else if (info.ServerType == SERVER_TYPE_FARM_CONTROLLER)
		{
			AddCapsBool(t, "b_cluster_controller", true);
		}
		else
		{
			AddCapsBool(t, "b_cluster_member", true);
		}

		AddCapsBool(t, "b_support_config_hub", info.ServerType != SERVER_TYPE_FARM_MEMBER &&
			is_bridge == false);

		AddCapsBool(t, "b_vpn_client_connect", is_bridge == false ? true : false);

		AddCapsBool(t, "b_support_radius", info.ServerType != SERVER_TYPE_FARM_MEMBER &&
			is_bridge == false);

		if (build >= 3600)
		{
			RPC_BRIDGE_SUPPORT b;
			Zero(&b, sizeof(b));
			if (ScGetBridgeSupport(rpc, &b) == ERR_NO_ERROR)
			{
				AddCapsBool(t, "b_local_bridge", b.IsBridgeSupportedOs);
				AddCapsBool(t, "b_must_install_pcap", b.IsWinPcapNeeded);
			}
			else
			{
				AddCapsBool(t, "b_local_bridge", false);
				AddCapsBool(t, "b_must_install_pcap", false);
			}
		}
		else
		{
			AddCapsBool(t, "b_local_bridge", false);
			AddCapsBool(t, "b_must_install_pcap", false);
		}

		AddCapsBool(t, "b_tap_supported", false);

		if (info.ServerType == SERVER_TYPE_STANDALONE)
		{
			AddCapsBool(t, "b_support_cascade", true);
		}
		else
		{
			AddCapsBool(t, "b_support_cascade", false);
		}

		AddCapsBool(t, "b_support_cascade_cert", false);
		AddCapsBool(t, "b_support_config_log", info.ServerType != SERVER_TYPE_FARM_MEMBER);
		AddCapsBool(t, "b_support_autodelete", false);
	}
	else
	{
		// Success getting Caps
		if (info.ServerBuildInt <= 4350)
		{
			if (is_bridge == false)
			{
				// b_support_cluster should be true for build 4300 or earlier
				CAPS *caps = GetCaps(t, "b_support_cluster");
				if (caps == NULL)
				{
					AddCapsBool(t, "b_support_cluster", true);
				}
				else
				{
					caps->Value = 1;
				}
			}
		}
	}

	if (true)
	{
		TOKEN_LIST *names;

		// Fill items that doesn't exist in server-side as false
		names = GetTableNameStartWith("CT_b_");
		if (names != NULL)
		{
			UINT i;
			for (i = 0;i < names->NumTokens;i++)
			{
				char *name = names->Token[i] + 3;

				if (GetCaps(t, name) == NULL)
				{
					AddCapsBool(t, name, false);
				}
			}

			FreeToken(names);
		}
	}

	FreeRpcServerInfo(&info);

	return t;
}