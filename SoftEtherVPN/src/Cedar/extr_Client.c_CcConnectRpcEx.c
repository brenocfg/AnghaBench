#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_12__ {int /*<<< orphan*/  ClientId; int /*<<< orphan*/  ShowVgcLink; int /*<<< orphan*/  IsVgcSupported; int /*<<< orphan*/  OsType; int /*<<< orphan*/  Win9x; int /*<<< orphan*/  Unix; TYPE_2__* Rpc; } ;
struct TYPE_11__ {TYPE_3__* Param; } ;
struct TYPE_10__ {int /*<<< orphan*/  ClientId; int /*<<< orphan*/  ShowVgcLink; int /*<<< orphan*/  IsVgcSupported; int /*<<< orphan*/  OsType; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ RPC_CLIENT_VERSION ;
typedef  TYPE_2__ RPC ;
typedef  TYPE_3__ REMOTE_CLIENT ;

/* Variables and functions */
 scalar_t__ CLIENT_CONFIG_PORT ; 
 scalar_t__ CLIENT_RPC_MODE_MANAGEMENT ; 
 scalar_t__ CLIENT_RPC_MODE_SHORTCUT ; 
 scalar_t__ CLIENT_RPC_MODE_SHORTCUT_DISCONNECT ; 
 int /*<<< orphan*/  CLIENT_WIN32_REGKEYNAME ; 
 int /*<<< orphan*/  CLIENT_WIN32_REGVALUE_PID ; 
 int /*<<< orphan*/  CLIENT_WIN32_REGVALUE_PORT ; 
 int /*<<< orphan*/  CcGetClientVersion (TYPE_3__*,TYPE_1__*) ; 
 scalar_t__ CheckTCPPort (char*,scalar_t__) ; 
 int /*<<< orphan*/ * Connect (char*,scalar_t__) ; 
 scalar_t__ ERR_CONNECT_FAILED ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ Endian32 (scalar_t__) ; 
 int /*<<< orphan*/  GC_SVC_NAME_VPNCLIENT ; 
 int INFINITE ; 
 int MsIsServiceRunning (int /*<<< orphan*/ ) ; 
 scalar_t__ MsRegReadIntEx2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OS_IS_UNIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_IS_WINDOWS_9X (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_LOCAL_MACHINE ; 
 int RecvAll (int /*<<< orphan*/ *,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SendAdd (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  SendAll (int /*<<< orphan*/ *,scalar_t__*,int,int) ; 
 int SendNow (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetTimeout (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Sha0 (scalar_t__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* StartRpcClient (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 TYPE_3__* ZeroMalloc (int) ; 

REMOTE_CLIENT *CcConnectRpcEx(char *server_name, char *password, bool *bad_pass, bool *no_remote, UCHAR *key, UINT *key_error_code, bool shortcut_disconnect, UINT wait_retry)
{
	SOCK *s = NULL;
	UINT i;
	UINT retcode;
	UINT rpc_mode = CLIENT_RPC_MODE_MANAGEMENT;
	RPC *rpc;
	REMOTE_CLIENT *ret;
	UCHAR hash_password[SHA1_SIZE];
	UINT port_start;
	UINT64 try_started = 0;
	bool ok;
	UINT reg_port = 0;
	UINT reg_pid = 0;
	// Validate arguments
	if (server_name == NULL)
	{
		return NULL;
	}
	if (password == NULL)
	{
		password = "";
	}

	if (key_error_code != NULL)
	{
		*key_error_code = ERR_NO_ERROR;
	}

	if (bad_pass != NULL)
	{
		*bad_pass = false;
	}

	if (no_remote != NULL)
	{
		*no_remote = false;
	}

#ifdef	OS_WIN32
	// read the current port number from the registry of the localhost
	if (StrCmpi(server_name, "localhost") == 0)
	{
		reg_port = MsRegReadIntEx2(REG_LOCAL_MACHINE, CLIENT_WIN32_REGKEYNAME, CLIENT_WIN32_REGVALUE_PORT, false, true);
		reg_pid = MsRegReadIntEx2(REG_LOCAL_MACHINE, CLIENT_WIN32_REGKEYNAME, CLIENT_WIN32_REGVALUE_PID, false, true);

		if (reg_pid != 0)
		{
			if (MsIsServiceRunning(GC_SVC_NAME_VPNCLIENT) == false)
			{
				reg_port = 0;
			}
		}
		else
		{
			reg_port = 0;
		}
	}

	if (reg_port != 0)
	{
		s = Connect(server_name, reg_port);

		if (s != NULL)
		{
			goto L_TRY;
		}
	}

#endif	// OS_WIN32

	port_start = CLIENT_CONFIG_PORT - 1;

RETRY:
	port_start++;

	if (port_start >= (CLIENT_CONFIG_PORT + 5))
	{
		return NULL;
	}

	ok = false;

	while (true)
	{
		for (i = port_start;i < (CLIENT_CONFIG_PORT + 5);i++)
		{
			if (CheckTCPPort(server_name, i))
			{
				ok = true;
				break;
			}
		}

		if (ok)
		{
			break;
		}

		if (wait_retry == 0)
		{
			break;
		}

		if (try_started == 0)
		{
			try_started = Tick64();
		}

		if ((try_started + (UINT64)wait_retry) <= Tick64())
		{
			break;
		}
	}

	if (ok == false)
	{
		if (key_error_code)
		{
			*key_error_code = ERR_CONNECT_FAILED;
		}
		return NULL;
	}

	port_start = i;

	s = Connect(server_name, i);
	if (s == NULL)
	{
		if (key_error_code)
		{
			*key_error_code = ERR_CONNECT_FAILED;
		}
		goto RETRY;
	}
L_TRY:

	SetTimeout(s, 10000);

	Sha0(hash_password, password, StrLen(password));

	if (key != NULL)
	{
		if (shortcut_disconnect == false)
		{
			rpc_mode = CLIENT_RPC_MODE_SHORTCUT;
		}
		else
		{
			rpc_mode = CLIENT_RPC_MODE_SHORTCUT_DISCONNECT;
		}
	}

	rpc_mode = Endian32(rpc_mode);
	SendAdd(s, &rpc_mode, sizeof(UINT));

	if (key != NULL)
	{
		SendAdd(s, key, SHA1_SIZE);
	}
	else
	{
		SendAdd(s, hash_password, SHA1_SIZE);
	}

	if (SendNow(s, false) == false)
	{
		ReleaseSock(s);
		goto RETRY;
	}

	if (RecvAll(s, &retcode, sizeof(UINT), false) == false)
	{
		ReleaseSock(s);
		goto RETRY;
	}

	retcode = Endian32(retcode);

	if (retcode >= 1024)
	{
		ReleaseSock(s);
		goto RETRY;
	}

	if (key != NULL)
	{
		if (key_error_code)
		{
			*key_error_code = retcode;
		}
		SendAll(s, &retcode, sizeof(UINT), false);
		ReleaseSock(s);
		return NULL;
	}

	switch (retcode)
	{
	case 1:
		if (bad_pass != NULL)
		{
			*bad_pass = true;
		}
		break;
	case 2:
		if (no_remote != NULL)
		{
			*no_remote = true;
		}
		break;
	}

	if (retcode != 0)
	{
		ReleaseSock(s);
		return NULL;
	}

	SetTimeout(s, INFINITE);

	rpc = StartRpcClient(s, NULL);

	ReleaseSock(s);

	ret = ZeroMalloc(sizeof(REMOTE_CLIENT));
	rpc->Param = ret;

	if (ret != NULL)
	{
		RPC_CLIENT_VERSION t;

		ret->Rpc = rpc;
		Zero(&t, sizeof(t));
		CcGetClientVersion(ret, &t);
		ret->OsType = t.OsType;
		ret->Unix = OS_IS_UNIX(ret->OsType);
		ret->Win9x = OS_IS_WINDOWS_9X(ret->OsType);
		ret->IsVgcSupported = t.IsVgcSupported;
		ret->ShowVgcLink = t.ShowVgcLink;
		StrCpy(ret->ClientId, sizeof(ret->ClientId), t.ClientId);
	}

	return ret;
}