#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int /*<<< orphan*/  Server; } ;
struct TYPE_6__ {scalar_t__ ServerType; int /*<<< orphan*/  ControllerOnly; int /*<<< orphan*/  Weight; int /*<<< orphan*/  MemberPassword; int /*<<< orphan*/  ControllerPort; int /*<<< orphan*/  ControllerName; int /*<<< orphan*/  Ports; int /*<<< orphan*/  NumPort; int /*<<< orphan*/  PublicIp; } ;
typedef  TYPE_1__ RPC_FARM ;
typedef  TYPE_2__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int GetServerCapsInt (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  SiSetServerType (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT StSetFarmSetting(ADMIN *a, RPC_FARM *t)
{
	bool cluster_allowed = false;

	SERVER_ADMIN_ONLY;
	NO_SUPPORT_FOR_BRIDGE;


	cluster_allowed = GetServerCapsInt(a->Server, "b_support_cluster");

	if (t->ServerType != SERVER_TYPE_STANDALONE && cluster_allowed == false)
	{
		// When clustering function is disabled, deny turning into clustering mode
		return ERR_NOT_SUPPORTED;
	}

	ALog(a, NULL, "LA_SET_FARM_SETTING");

	IncrementServerConfigRevision(a->Server);

	SiSetServerType(a->Server, t->ServerType, t->PublicIp, t->NumPort, t->Ports,
		t->ControllerName, t->ControllerPort, t->MemberPassword, t->Weight, t->ControllerOnly);

	return ERR_NO_ERROR;
}