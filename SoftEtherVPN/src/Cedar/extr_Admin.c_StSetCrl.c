#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hubname ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_18__ {int ServerAdmin; TYPE_2__* Server; } ;
struct TYPE_17__ {TYPE_1__* HubDb; } ;
struct TYPE_16__ {int /*<<< orphan*/  Crl; int /*<<< orphan*/  Key; int /*<<< orphan*/  HubName; } ;
struct TYPE_15__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_14__ {int /*<<< orphan*/  CrlList; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_CRL ;
typedef  TYPE_4__ HUB ;
typedef  int /*<<< orphan*/  CRL ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_5__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_5__*,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/ * CopyCrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_NOT_ENOUGH_RIGHT ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ERR_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  FreeCrl (int /*<<< orphan*/ *) ; 
 TYPE_4__* GetHub (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ GetHubAdminOption (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_2__*) ; 
 int /*<<< orphan*/ * ListKeyToPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_4__*) ; 
 scalar_t__ ReplaceListPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

UINT StSetCrl(ADMIN *a, RPC_CRL *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	UINT ret = ERR_NO_ERROR;
	UINT key;
	char hubname[MAX_HUBNAME_LEN + 1];

	CHECK_RIGHT;
	NO_SUPPORT_FOR_BRIDGE;
	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_SUPPORTED;
	}

	StrCpy(hubname, sizeof(hubname), t->HubName);
	key = t->Key;

	h = GetHub(c, hubname);

	if (h == NULL)
	{
		ret = ERR_HUB_NOT_FOUND;
	}
	else
	{
		if (a->ServerAdmin == false && GetHubAdminOption(h, "no_change_crl_list") != 0)
		{
			ret = ERR_NOT_ENOUGH_RIGHT;
		}
		else
		{
			if (h->HubDb == NULL)
			{
				ret = ERR_NOT_SUPPORTED;
			}
			else
			{
				LockList(h->HubDb->CrlList);
				{
					CRL *crl = ListKeyToPointer(h->HubDb->CrlList, t->Key);

					if (crl == NULL)
					{
						ret = ERR_OBJECT_NOT_FOUND;
					}
					else
					{
						CRL *new_crl = CopyCrl(t->Crl);
						if (ReplaceListPointer(h->HubDb->CrlList, crl, new_crl))
						{
							ALog(a, h, "LA_ADD_CRL");
							FreeCrl(crl);

							IncrementServerConfigRevision(s);
						}
					}
				}
				UnlockList(h->HubDb->CrlList);
			}
		}

		ReleaseHub(h);
	}

	return ret;
}