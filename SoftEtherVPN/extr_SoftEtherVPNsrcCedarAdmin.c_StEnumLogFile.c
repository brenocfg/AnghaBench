#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_26__ {int ServerAdmin; char* HubName; int /*<<< orphan*/ * LogFileList; TYPE_1__* Server; } ;
struct TYPE_25__ {int Me; int /*<<< orphan*/  hostname; } ;
struct TYPE_24__ {int /*<<< orphan*/  ServerName; int /*<<< orphan*/  Path; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  FileSize; } ;
struct TYPE_23__ {scalar_t__ NumItem; TYPE_2__* Items; } ;
struct TYPE_22__ {int /*<<< orphan*/  ServerName; int /*<<< orphan*/  FilePath; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  FileSize; } ;
struct TYPE_21__ {scalar_t__ ServerType; int /*<<< orphan*/ * FarmMemberList; int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_ENUM_LOG_FILE_ITEM ;
typedef  TYPE_3__ RPC_ENUM_LOG_FILE ;
typedef  TYPE_4__ LOG_FILE ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  HUB ;
typedef  TYPE_5__ FARM_MEMBER ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_6__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  AdjoinRpcEnumLogFile (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * CmpLogFile ; 
 scalar_t__ ERR_NOT_ENOUGH_RIGHT ; 
 scalar_t__ ERR_NOT_SUPPORTED ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeEnumLogFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumLogFile (TYPE_3__*) ; 
 int /*<<< orphan*/ * GetHub (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ GetHubAdminOption (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,TYPE_4__*) ; 
 void* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 void* NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ SiCallEnumLogFileList (TYPE_1__*,TYPE_5__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  SiEnumLocalLogFileList (TYPE_1__*,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 void* ZeroMalloc (int) ; 

UINT StEnumLogFile(ADMIN *a, RPC_ENUM_LOG_FILE *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT i;
	bool no_access = false;

	HUB *h;

	if (a->ServerAdmin == false)
	{
		h = GetHub(c, a->HubName);

		if (a->ServerAdmin == false && GetHubAdminOption(h, "no_read_log_file") != 0)
		{
			no_access = true;
		}

		ReleaseHub(h);
	}
	else
	{
		if (s->ServerType == SERVER_TYPE_FARM_CONTROLLER)
		{
			// Since Management session will become unstable if log files are
			// enumerated on a cluster controller, it forbids. 
			return ERR_NOT_SUPPORTED;
		}
	}

	if (no_access)
	{
		return ERR_NOT_ENOUGH_RIGHT;
	}

	FreeRpcEnumLogFile(t);
	Zero(t, sizeof(RPC_ENUM_LOG_FILE));

	// Enumerate local log files
	SiEnumLocalLogFileList(s, a->ServerAdmin ? NULL : a->HubName, t);

	if (s->ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		UINT i;
		LIST *tt_list = NewListFast(NULL);

		LockList(s->FarmMemberList);
		{
			for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
			{
				FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);

				if (f->Me == false)
				{
					// Enumerate log files on other cluster members.
					RPC_ENUM_LOG_FILE *tt;
					tt = ZeroMalloc(sizeof(RPC_ENUM_LOG_FILE));

					if (SiCallEnumLogFileList(s, f, tt, a->ServerAdmin ? "" : a->HubName))
					{
						UINT i;
						for (i = 0;i < tt->NumItem;i++)
						{
							RPC_ENUM_LOG_FILE_ITEM *e = &tt->Items[i];

							StrCpy(e->ServerName, sizeof(e->ServerName), f->hostname);
						}

						Add(tt_list, tt);
					}
					else
					{
						Free(tt);
					}
				}
			}
		}
		UnlockList(s->FarmMemberList);

		for (i = 0;i < LIST_NUM(tt_list);i++)
		{
			RPC_ENUM_LOG_FILE *tt = LIST_DATA(tt_list, i);

			AdjoinRpcEnumLogFile(t, tt);
			FreeRpcEnumLogFile(tt);

			Free(tt);
		}

		ReleaseList(tt_list);
	}

	// Cache the last list of log files on RPC session
	if (a->LogFileList != NULL)
	{
		FreeEnumLogFile(a->LogFileList);
	}

	a->LogFileList = NewListFast(CmpLogFile);

	for (i = 0;i < t->NumItem;i++)
	{
		RPC_ENUM_LOG_FILE_ITEM *e = &t->Items[i];
		LOG_FILE *f = ZeroMalloc(sizeof(LOG_FILE));

		f->FileSize = e->FileSize;
		f->UpdatedTime = e->UpdatedTime;
		StrCpy(f->Path, sizeof(f->Path), e->FilePath);
		StrCpy(f->ServerName, sizeof(f->ServerName), e->ServerName);

		Insert(a->LogFileList, f);
	}

	return ERR_NO_ERROR;
}