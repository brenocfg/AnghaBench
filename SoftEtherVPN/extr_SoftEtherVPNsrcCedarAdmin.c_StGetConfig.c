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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_18__ {TYPE_2__* Server; } ;
struct TYPE_17__ {scalar_t__ Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_16__ {int /*<<< orphan*/  FileData; int /*<<< orphan*/  FileName; } ;
struct TYPE_15__ {TYPE_1__* CfgRw; } ;
struct TYPE_14__ {char* FileName; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_CONFIG ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_4__ BUF ;
typedef  TYPE_5__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_5__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgDeleteFolder (int /*<<< orphan*/ *) ; 
 TYPE_4__* CfgFolderToBuf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeBuf (TYPE_4__*) ; 
 int /*<<< orphan*/  FreeRpcConfig (TYPE_3__*) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/ * SiWriteConfigurationToCfg (TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ZeroMalloc (scalar_t__) ; 

UINT StGetConfig(ADMIN *a, RPC_CONFIG *t)
{
	SERVER *s;

	SERVER_ADMIN_ONLY;

	FreeRpcConfig(t);
	Zero(t, sizeof(RPC_CONFIG));

	s = a->Server;

	ALog(a, NULL, "LA_GET_CONFIG");

	if (s->CfgRw != NULL)
	{
		FOLDER *f = SiWriteConfigurationToCfg(s);
		BUF *b = CfgFolderToBuf(f, true);

		StrCpy(t->FileName, sizeof(t->FileName), s->CfgRw->FileName + (s->CfgRw->FileName[0] == '@' ? 1 : 0));

		t->FileData = ZeroMalloc(b->Size + 1);
		Copy(t->FileData, b->Buf, b->Size);

		CfgDeleteFolder(f);
		FreeBuf(b);

		return ERR_NO_ERROR;
	}
	else
	{
		return ERR_INTERNAL_ERROR;
	}
}