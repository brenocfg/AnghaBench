#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ ExpireDate; TYPE_5__* Admin; } ;
typedef  TYPE_2__ WU_CONTEXT ;
struct TYPE_10__ {TYPE_1__* Cedar; } ;
typedef  TYPE_3__ WEBUI ;
struct TYPE_12__ {int ServerAdmin; int /*<<< orphan*/ * LogFileList; TYPE_4__* Rpc; int /*<<< orphan*/  Server; int /*<<< orphan*/ * HubName; } ;
struct TYPE_11__ {int ServerAdminMode; int ServerMode; int IsVpnServer; int /*<<< orphan*/  Lock; TYPE_5__* Param; int /*<<< orphan*/  Name; } ;
struct TYPE_8__ {int /*<<< orphan*/  Server; } ;
typedef  TYPE_4__ RPC ;
typedef  TYPE_5__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/ * CopyStr (char*) ; 
 scalar_t__ Malloc (int) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ StrLen (char*) ; 
 scalar_t__ Tick64 () ; 
 scalar_t__ WU_CONTEXT_EXPIRE ; 
 scalar_t__ ZeroMalloc (int) ; 

__attribute__((used)) static WU_CONTEXT *WuNewContext(WEBUI *wu, char *hubname)
{
	WU_CONTEXT *context = (WU_CONTEXT*)Malloc(sizeof(WU_CONTEXT));

	if(StrLen(hubname) == 0)
	{
		hubname=NULL;
	}
	context->Admin = (ADMIN*)ZeroMalloc(sizeof(ADMIN));
	context->Admin->HubName = hubname != NULL ? CopyStr(hubname) : NULL;
	context->Admin->Server = wu->Cedar->Server;
	context->Admin->ServerAdmin = hubname == NULL ? true: false;
	context->Admin->Rpc = (RPC*)ZeroMalloc(sizeof(RPC));
	StrCpy(context->Admin->Rpc->Name, sizeof(context->Admin->Rpc->Name), "WEBUI");
	context->Admin->Rpc->Param = context->Admin;
	context->Admin->Rpc->ServerAdminMode = context->Admin->ServerAdmin;
	context->Admin->Rpc->ServerMode = true;
	context->Admin->Rpc->IsVpnServer = true;
	context->Admin->Rpc->Lock = NewLock();
	context->Admin->LogFileList = NULL;

	context->ExpireDate = Tick64() + WU_CONTEXT_EXPIRE;

	return context;
}