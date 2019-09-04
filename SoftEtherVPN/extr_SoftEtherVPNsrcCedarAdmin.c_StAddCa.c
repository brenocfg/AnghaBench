#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_17__ {int ServerAdmin; TYPE_1__* Server; } ;
struct TYPE_16__ {scalar_t__ Bridge; } ;
struct TYPE_15__ {TYPE_11__* Cert; int /*<<< orphan*/  HubName; } ;
struct TYPE_14__ {scalar_t__ ServerType; TYPE_3__* Cedar; } ;
struct TYPE_13__ {int is_compatible_bit; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_HUB_ADD_CA ;
typedef  int /*<<< orphan*/  HUB ;
typedef  TYPE_3__ CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_4__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  AddRootCert (int /*<<< orphan*/ *,TYPE_11__*) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NOT_ENOUGH_RIGHT ; 
 int /*<<< orphan*/  ERR_NOT_FARM_CONTROLLER ; 
 int /*<<< orphan*/  ERR_NOT_RSA_1024 ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/ * GetHub (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GetHubAdminOption (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 int /*<<< orphan*/  LockHubList (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  UnlockHubList (TYPE_3__*) ; 

UINT StAddCa(ADMIN *a, RPC_HUB_ADD_CA *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;

	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_FARM_CONTROLLER;
	}

	if (c->Bridge)
	{
		return ERR_NOT_SUPPORTED;
	}

	if (t->Cert == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	if (t->Cert->is_compatible_bit == false)
	{
		return ERR_NOT_RSA_1024;
	}

	CHECK_RIGHT;

	LockHubList(c);
	{
		h = GetHub(c, t->HubName);
	}
	UnlockHubList(c);

	if (h == NULL)
	{
		return ERR_HUB_NOT_FOUND;
	}

	if (a->ServerAdmin == false && GetHubAdminOption(h, "no_change_cert_list") != 0)
	{
		ReleaseHub(h);
		return ERR_NOT_ENOUGH_RIGHT;
	}

	IncrementServerConfigRevision(s);

	ALog(a, h, "LA_ADD_CA");

	AddRootCert(h, t->Cert);

	ReleaseHub(h);

	return ERR_NO_ERROR;
}