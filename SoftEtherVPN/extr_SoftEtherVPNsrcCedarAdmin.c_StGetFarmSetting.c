#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {TYPE_1__* Server; } ;
struct TYPE_9__ {scalar_t__ ServerType; int NumPort; void* Ports; int /*<<< orphan*/  ControllerPort; int /*<<< orphan*/  ControllerName; int /*<<< orphan*/  PublicIp; int /*<<< orphan*/  Weight; int /*<<< orphan*/  ControllerOnly; } ;
struct TYPE_8__ {scalar_t__ ServerType; int NumPublicPort; int /*<<< orphan*/  ControllerPort; int /*<<< orphan*/  ControllerName; int /*<<< orphan*/  PublicIp; int /*<<< orphan*/  PublicPorts; int /*<<< orphan*/  Weight; int /*<<< orphan*/  ControllerOnly; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_FARM ;
typedef  TYPE_3__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcFarm (TYPE_2__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 void* ZeroMalloc (int) ; 

UINT StGetFarmSetting(ADMIN *a, RPC_FARM *t)
{
	SERVER *s;
	FreeRpcFarm(t);
	Zero(t, sizeof(RPC_FARM));

	s = a->Server;
	t->ServerType = s->ServerType;
	t->ControllerOnly = s->ControllerOnly;
	t->Weight = s->Weight;

	if (t->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		t->NumPort = s->NumPublicPort;
		t->Ports = ZeroMalloc(sizeof(UINT) * t->NumPort);
		Copy(t->Ports, s->PublicPorts, sizeof(UINT) * t->NumPort);
		t->PublicIp = s->PublicIp;
		StrCpy(t->ControllerName, sizeof(t->ControllerName), s->ControllerName);
		t->ControllerPort = s->ControllerPort;
	}
	else
	{
		t->NumPort = 0;
		t->Ports = ZeroMalloc(0);
	}

	return ERR_NO_ERROR;
}