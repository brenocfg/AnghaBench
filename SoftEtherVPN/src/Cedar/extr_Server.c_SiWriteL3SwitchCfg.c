#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  HubName; } ;
struct TYPE_6__ {int /*<<< orphan*/  TableList; int /*<<< orphan*/  IfList; int /*<<< orphan*/  Active; } ;
struct TYPE_5__ {int /*<<< orphan*/  Metric; int /*<<< orphan*/  GatewayAddress; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  NetworkAddress; } ;
typedef  TYPE_1__ L3TABLE ;
typedef  TYPE_2__ L3SW ;
typedef  TYPE_3__ L3IF ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddIp32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,scalar_t__) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 

void SiWriteL3SwitchCfg(FOLDER *f, L3SW *sw)
{
	UINT i;
	FOLDER *if_folder, *table_folder;
	char tmp[MAX_SIZE];
	// Validate arguments
	if (f == NULL || sw == NULL)
	{
		return;
	}

	// Active flag
	CfgAddBool(f, "Active", sw->Active);

	// Interface list
	if_folder = CfgCreateFolder(f, "InterfaceList");
	for (i = 0;i < LIST_NUM(sw->IfList);i++)
	{
		L3IF *e = LIST_DATA(sw->IfList, i);
		FOLDER *ff;

		Format(tmp, sizeof(tmp), "Interface%u", i);
		ff = CfgCreateFolder(if_folder, tmp);

		CfgAddStr(ff, "HubName", e->HubName);
		CfgAddIp32(ff, "IpAddress", e->IpAddress);
		CfgAddIp32(ff, "SubnetMask", e->SubnetMask);
	}

	// Routing table
	table_folder = CfgCreateFolder(f, "RoutingTable");
	for (i = 0;i < LIST_NUM(sw->TableList);i++)
	{
		L3TABLE *e = LIST_DATA(sw->TableList, i);
		FOLDER *ff;

		Format(tmp, sizeof(tmp), "Entry%u", i);
		ff = CfgCreateFolder(table_folder, tmp);

		CfgAddIp32(ff, "NetworkAddress", e->NetworkAddress);
		CfgAddIp32(ff, "SubnetMask", e->SubnetMask);
		CfgAddIp32(ff, "GatewayAddress", e->GatewayAddress);
		CfgAddInt(ff, "Metric", e->Metric);
	}
}