#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winver_msg_server ;
typedef  int /*<<< orphan*/  winver_msg_client ;
struct TYPE_29__ {struct TYPE_29__* Msg; } ;
typedef  TYPE_1__ wchar_t ;
typedef  scalar_t__ UINT ;
struct TYPE_34__ {int /*<<< orphan*/  ClientWinVer; TYPE_3__* Server; } ;
struct TYPE_33__ {int Bridge; } ;
struct TYPE_32__ {int /*<<< orphan*/  Title; } ;
struct TYPE_31__ {TYPE_6__* Cedar; } ;
struct TYPE_30__ {int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  TYPE_3__ SERVER ;
typedef  TYPE_4__ RPC_WINVER ;
typedef  TYPE_1__ RPC_MSG ;
typedef  TYPE_6__ CEDAR ;
typedef  TYPE_7__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcMsg (TYPE_1__*) ; 
 int /*<<< orphan*/  GSF_SHOW_OSS_MSG ; 
 scalar_t__ GetGlobalServerFlag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWinVer (TYPE_4__*) ; 
 int IsSupportedWinVer (TYPE_4__*) ; 
 int /*<<< orphan*/  LocalTime (TYPE_2__*) ; 
 int /*<<< orphan*/  SUPPORTED_WINDOWS_LIST ; 
 int /*<<< orphan*/  UniFormat (TYPE_1__*,int,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCat (TYPE_1__*,scalar_t__,TYPE_1__*) ; 
 scalar_t__ UniStrSize (TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 TYPE_1__* ZeroMalloc (scalar_t__) ; 
 TYPE_1__* _UU (char*) ; 

UINT StGetAdminMsg(ADMIN *a, RPC_MSG *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT ret = ERR_NO_ERROR;
	RPC_WINVER server_ver;
	RPC_WINVER client_ver;
	wchar_t winver_msg_client[3800];
	wchar_t winver_msg_server[3800];
	UINT tmpsize;
	wchar_t *tmp;

	FreeRpcMsg(t);
	Zero(t, sizeof(RPC_MSG));

	// Check for Windows version
	GetWinVer(&server_ver);
	Copy(&client_ver, &a->ClientWinVer, sizeof(RPC_WINVER));

	Zero(winver_msg_client, sizeof(winver_msg_client));
	Zero(winver_msg_server, sizeof(winver_msg_server));

	if (IsSupportedWinVer(&client_ver) == false)
	{
		SYSTEMTIME st;

		LocalTime(&st);

		UniFormat(winver_msg_client, sizeof(winver_msg_client), _UU("WINVER_ERROR_FORMAT"),
			_UU("WINVER_ERROR_PC_LOCAL"),
			client_ver.Title,
			_UU("WINVER_ERROR_VPNSERVER"),
			SUPPORTED_WINDOWS_LIST,
			_UU("WINVER_ERROR_PC_LOCAL"),
			_UU("WINVER_ERROR_VPNSERVER"),
			_UU("WINVER_ERROR_VPNSERVER"),
			_UU("WINVER_ERROR_VPNSERVER"),
			st.wYear, st.wMonth);
	}

	if (IsSupportedWinVer(&server_ver) == false)
	{
		SYSTEMTIME st;

		LocalTime(&st);

		UniFormat(winver_msg_server, sizeof(winver_msg_server), _UU("WINVER_ERROR_FORMAT"),
			_UU("WINVER_ERROR_PC_REMOTE"),
			server_ver.Title,
			_UU("WINVER_ERROR_VPNSERVER"),
			SUPPORTED_WINDOWS_LIST,
			_UU("WINVER_ERROR_PC_REMOTE"),
			_UU("WINVER_ERROR_VPNSERVER"),
			_UU("WINVER_ERROR_VPNSERVER"),
			_UU("WINVER_ERROR_VPNSERVER"),
			st.wYear, st.wMonth);
	}

	tmpsize = UniStrSize(winver_msg_client) + UniStrSize(winver_msg_server) + 10000;

	tmp = ZeroMalloc(tmpsize);

	if (
		c->Bridge == false)
	{
		if (GetGlobalServerFlag(GSF_SHOW_OSS_MSG) != 0)
		{
			UniStrCat(tmp, tmpsize, _UU("OSS_MSG"));
		}
	}

	UniStrCat(tmp, tmpsize, winver_msg_client);
	UniStrCat(tmp, tmpsize, winver_msg_server);

	t->Msg = tmp;

	return ERR_NO_ERROR;
}