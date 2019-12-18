#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tt ;
typedef  int /*<<< orphan*/  servername ;
typedef  int /*<<< orphan*/  logfilename ;
typedef  int /*<<< orphan*/  elf ;
typedef  scalar_t__ UINT ;
struct TYPE_26__ {scalar_t__ Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_25__ {int /*<<< orphan*/ * LogFileList; TYPE_1__* Server; } ;
struct TYPE_24__ {int Me; int /*<<< orphan*/  hostname; } ;
struct TYPE_23__ {char* FilePath; char* ServerName; scalar_t__ Offset; TYPE_7__* Buffer; } ;
struct TYPE_22__ {scalar_t__ ServerType; int /*<<< orphan*/  FarmMemberList; int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_READ_LOG_FILE ;
typedef  TYPE_2__ RPC_ENUM_LOG_FILE ;
typedef  TYPE_4__ FARM_MEMBER ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_5__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_5__*,int /*<<< orphan*/ *,char*,char*,char*) ; 
 int CheckLogFileNameFromEnumList (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  FreeRpcEnumLogFile (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeRpcReadLogFile (TYPE_2__*) ; 
 int /*<<< orphan*/  GetMachineName (char*,int) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 TYPE_4__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HOST_NAME_LEN ; 
 int MAX_PATH ; 
 TYPE_7__* NewBuf () ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ SiCallReadLogFile (TYPE_1__*,TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SiReadLocalLogFile (TYPE_1__*,char*,scalar_t__,TYPE_2__*) ; 
 scalar_t__ StEnumLogFile (TYPE_5__*,TYPE_2__*) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

UINT StReadLogFile(ADMIN *a, RPC_READ_LOG_FILE *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	char logfilename[MAX_PATH];
	char servername[MAX_HOST_NAME_LEN + 1];
	UINT offset;
	bool local = true;

	if (IsEmptyStr(t->FilePath))
	{
		return ERR_INVALID_PARAMETER;
	}

	StrCpy(logfilename, sizeof(logfilename), t->FilePath);
	StrCpy(servername, sizeof(servername), t->ServerName);
	offset = t->Offset;

	if (s->ServerType != SERVER_TYPE_FARM_CONTROLLER)
	{
		GetMachineName(servername, sizeof(servername));
	}

	// Check the permission to read the log file
	if (a->LogFileList == NULL)
	{
		// Enum the log files first
		RPC_ENUM_LOG_FILE elf;
		UINT elf_ret;

		Zero(&elf, sizeof(elf));

		elf_ret = StEnumLogFile(a, &elf);

		FreeRpcEnumLogFile(&elf);

		if (elf_ret != ERR_NO_ERROR)
		{
			return elf_ret;
		}
	}
	if (CheckLogFileNameFromEnumList(a->LogFileList, logfilename, servername) == false)
	{
		// There is no such file in the log file list
		return ERR_OBJECT_NOT_FOUND;
	}

	FreeRpcReadLogFile(t);
	Zero(t, sizeof(RPC_READ_LOG_FILE));

	if (s->ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		UINT i;

		// When the host name in request is a cluster member, redirect the request
		LockList(s->FarmMemberList);
		{
			for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
			{
				FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);

				if (f->Me == false)
				{
					if (StrCmpi(f->hostname, servername) == 0)
					{
						RPC_READ_LOG_FILE tt;

						Zero(&tt, sizeof(tt));
						local = false;

						StrCpy(tt.ServerName, sizeof(tt.ServerName), servername);
						StrCpy(tt.FilePath, sizeof(tt.FilePath), logfilename);
						tt.Offset = offset;

						if (SiCallReadLogFile(s, f, &tt))
						{
							if (tt.Buffer != NULL && tt.Buffer->Size > 0)
							{
								t->Buffer = NewBuf();
								WriteBuf(t->Buffer, tt.Buffer->Buf, tt.Buffer->Size);
							}
						}

						FreeRpcReadLogFile(&tt);

						break;
					}
				}
			}
		}
		UnlockList(s->FarmMemberList);
	}

	// Read a local file
	if (local)
	{
		SiReadLocalLogFile(s, logfilename, offset, t);
	}

	if (offset == 0)
	{
		ALog(a, NULL, "LA_READ_LOG_FILE", servername, logfilename);
	}

	StrCpy(t->FilePath, sizeof(t->FilePath), logfilename);
	StrCpy(t->ServerName, sizeof(t->ServerName), servername);
	t->Offset = offset;

	return ERR_NO_ERROR;
}