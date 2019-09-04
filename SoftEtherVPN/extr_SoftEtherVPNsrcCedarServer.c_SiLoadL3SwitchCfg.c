#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tbl ;
typedef  int /*<<< orphan*/  name ;
typedef  size_t UINT ;
struct TYPE_8__ {int /*<<< orphan*/  Metric; void* GatewayAddress; void* SubnetMask; void* NetworkAddress; } ;
struct TYPE_7__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ L3TABLE ;
typedef  int /*<<< orphan*/  L3SW ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 TYPE_1__* CfgEnumFolderToTokenList (int /*<<< orphan*/ *) ; 
 int CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetIp32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  L3AddIf (int /*<<< orphan*/ *,char*,size_t,size_t) ; 
 int /*<<< orphan*/  L3AddTable (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  L3SwStart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

void SiLoadL3SwitchCfg(L3SW *sw, FOLDER *f)
{
	UINT i;
	FOLDER *if_folder, *table_folder;
	TOKEN_LIST *t;
	bool active = false;
	// Validate arguments
	if (sw == NULL || f == NULL)
	{
		return;
	}

	active = CfgGetBool(f, "Active");

	// Interface list
	if_folder = CfgGetFolder(f, "InterfaceList");
	if (if_folder != NULL)
	{
		t = CfgEnumFolderToTokenList(if_folder);
		if (t != NULL)
		{
			for (i = 0;i < t->NumTokens;i++)
			{
				FOLDER *ff = CfgGetFolder(if_folder, t->Token[i]);
				char name[MAX_HUBNAME_LEN + 1];
				UINT ip, subnet;

				CfgGetStr(ff, "HubName", name, sizeof(name));
				ip = CfgGetIp32(ff, "IpAddress");
				subnet = CfgGetIp32(ff, "SubnetMask");

				{
					L3AddIf(sw, name, ip, subnet);
				}
			}
			FreeToken(t);
		}
	}

	// Routing table
	table_folder = CfgGetFolder(f, "RoutingTable");
	if (table_folder != NULL)
	{
		t = CfgEnumFolderToTokenList(table_folder);
		if (t != NULL)
		{
			for (i = 0;i < t->NumTokens;i++)
			{
				FOLDER *ff = CfgGetFolder(table_folder, t->Token[i]);
				L3TABLE tbl;

				Zero(&tbl, sizeof(tbl));
				tbl.NetworkAddress = CfgGetIp32(ff, "NetworkAddress");
				tbl.SubnetMask = CfgGetIp32(ff, "SubnetMask");
				tbl.GatewayAddress = CfgGetIp32(ff, "GatewayAddress");
				tbl.Metric = CfgGetInt(ff, "Metric");

				L3AddTable(sw, &tbl);
			}
			FreeToken(t);
		}
	}

	if (active)
	{
		L3SwStart(sw);
	}
}