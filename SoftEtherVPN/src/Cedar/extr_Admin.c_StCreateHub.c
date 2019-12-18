#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  o ;
typedef  scalar_t__ UINT ;
struct TYPE_30__ {TYPE_2__* Server; } ;
struct TYPE_29__ {int /*<<< orphan*/  HubList; } ;
struct TYPE_28__ {scalar_t__ Type; int Offline; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  SecurePassword; int /*<<< orphan*/  HashedPassword; } ;
struct TYPE_27__ {int /*<<< orphan*/  NoEnum; int /*<<< orphan*/  MaxSession; } ;
struct TYPE_24__ {int /*<<< orphan*/  NoEnum; int /*<<< orphan*/  MaxSession; } ;
struct TYPE_26__ {scalar_t__ HubType; scalar_t__ Online; int /*<<< orphan*/  SecurePassword; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  HubName; int /*<<< orphan*/  AdminPasswordPlainText; TYPE_1__ HubOption; } ;
struct TYPE_25__ {scalar_t__ ServerType; TYPE_6__* Cedar; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_CREATE_HUB ;
typedef  TYPE_4__ HUB_OPTION ;
typedef  TYPE_5__ HUB ;
typedef  TYPE_6__ CEDAR ;
typedef  TYPE_7__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ADMINISTRATOR_USERNAME ; 
 int /*<<< orphan*/  ALog (TYPE_7__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddHub (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_HUB_ALREADY_EXISTS ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NOT_FARM_CONTROLLER ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_TOO_MANY_HUBS ; 
 scalar_t__ EndWith (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ GetServerCapsInt (TYPE_2__*,char*) ; 
 scalar_t__ HUB_TYPE_FARM_DYNAMIC ; 
 scalar_t__ HUB_TYPE_FARM_STATIC ; 
 scalar_t__ HUB_TYPE_STANDALONE ; 
 int /*<<< orphan*/  HashPassword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_2__*) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int IsHub (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int IsSafeStr (int /*<<< orphan*/ ) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ ,int) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 TYPE_5__* NewHub (TYPE_6__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_5__*) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  SetHubOffline (TYPE_5__*) ; 
 int /*<<< orphan*/  SetHubOnline (TYPE_5__*) ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SiSetDefaultHubOption (TYPE_4__*) ; 
 scalar_t__ StartWith (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ StrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemTime64 () ; 
 int /*<<< orphan*/  Trim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_4__*,int) ; 

UINT StCreateHub(ADMIN *a, RPC_CREATE_HUB *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	HUB_OPTION o;
	UINT current_hub_num;
	bool b;

	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_FARM_CONTROLLER;
	}



	if (IsEmptyStr(t->HubName) || IsSafeStr(t->HubName) == false)
	{
		return ERR_INVALID_PARAMETER;
	}

	NO_SUPPORT_FOR_BRIDGE;

	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_FARM_CONTROLLER;
	}

	SERVER_ADMIN_ONLY;

	Trim(t->HubName);
	if (StrLen(t->HubName) == 0)
	{
		return ERR_INVALID_PARAMETER;
	}
	if (StartWith(t->HubName, ".") || EndWith(t->HubName, "."))
	{
		return ERR_INVALID_PARAMETER;
	}

	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_FARM_CONTROLLER;
	}

	if (s->ServerType == SERVER_TYPE_STANDALONE)
	{
		if (t->HubType != HUB_TYPE_STANDALONE)
		{
			return ERR_INVALID_PARAMETER;
		}
	}
	else if (t->HubType != HUB_TYPE_FARM_DYNAMIC && t->HubType != HUB_TYPE_FARM_STATIC)
	{
		return ERR_INVALID_PARAMETER;
	}

	// Create a hub object
	Zero(&o, sizeof(o));
	o.MaxSession = t->HubOption.MaxSession;
	o.NoEnum = t->HubOption.NoEnum;

	// Default setting for hub admin options
	SiSetDefaultHubOption(&o);

	LockList(c->HubList);
	{
		current_hub_num = LIST_NUM(c->HubList);
	}
	UnlockList(c->HubList);

	if (current_hub_num > GetServerCapsInt(a->Server, "i_max_hubs"))
	{
		return ERR_TOO_MANY_HUBS;
	}

	LockList(c->HubList);
	{
		b = IsHub(c, t->HubName);
	}
	UnlockList(c->HubList);

	if (b)
	{
		return ERR_HUB_ALREADY_EXISTS;
	}

	ALog(a, NULL, "LA_CREATE_HUB", t->HubName);

	// For JSON-RPC
	if ((IsZero(t->HashedPassword, sizeof(t->HashedPassword)) &&
		IsZero(t->SecurePassword, sizeof(t->SecurePassword))) ||
		StrLen(t->AdminPasswordPlainText) != 0)
	{
		Sha0(t->HashedPassword, t->AdminPasswordPlainText, StrLen(t->AdminPasswordPlainText));
		HashPassword(t->SecurePassword, ADMINISTRATOR_USERNAME, t->AdminPasswordPlainText);
	}

	h = NewHub(c, t->HubName, &o);
	Copy(h->HashedPassword, t->HashedPassword, SHA1_SIZE);
	Copy(h->SecurePassword, t->SecurePassword, SHA1_SIZE);

	h->Type = t->HubType;

	AddHub(c, h);

	if (t->Online)
	{
		h->Offline = true;
		SetHubOnline(h);
	}
	else
	{
		h->Offline = false;
		SetHubOffline(h);
	}

	h->CreatedTime = SystemTime64();

	ReleaseHub(h);

	IncrementServerConfigRevision(s);

	return ERR_NO_ERROR;
}