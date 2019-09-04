#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  o ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_17__ {int /*<<< orphan*/  ProxyType; scalar_t__ Port; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  AccountName; } ;
struct TYPE_16__ {int ProgrammingMode; char* (* ReadPassword ) (TYPE_2__*,char*) ;int /*<<< orphan*/  (* Write ) (TYPE_2__*,char*) ;} ;
struct TYPE_15__ {scalar_t__ LastError; } ;
typedef  int /*<<< orphan*/  RPC ;
typedef  TYPE_1__ PS ;
typedef  TYPE_2__ CONSOLE ;
typedef  TYPE_3__ CLIENT_OPTION ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * AdminConnectEx (int /*<<< orphan*/ *,TYPE_3__*,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AdminDisconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CEDAR_CUI_STR ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_2__*,scalar_t__) ; 
 scalar_t__ ERR_ACCESS_DENIED ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreePs (TYPE_1__*) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/ * NewCedar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* NewPs (TYPE_2__*,int /*<<< orphan*/ *,char*,scalar_t__,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROXY_DIRECT ; 
 int /*<<< orphan*/  PsMain (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ *) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*) ; 
 char* stub2 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,char*) ; 

UINT PsConnect(CONSOLE *c, char *host, UINT port, char *hub, char *adminhub, wchar_t *cmdline, char *password)
{
	UINT retcode = 0;
	RPC *rpc = NULL;
	CEDAR *cedar;
	CLIENT_OPTION o;
	UCHAR hashed_password[SHA1_SIZE];
	bool b = false;
	// Validate arguments
	if (c == NULL || host == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}
	if (port == 0)
	{
		port = 443;
	}
	if (hub != NULL)
	{
		adminhub = NULL;
	}

	cedar = NewCedar(NULL, NULL);

	Zero(&o, sizeof(o));
	UniStrCpy(o.AccountName, sizeof(o.AccountName), L"VPNCMD");
	StrCpy(o.Hostname, sizeof(o.Hostname), host);
	o.Port = port;
	o.ProxyType = PROXY_DIRECT;

	Sha0(hashed_password, password, StrLen(password));

	if (IsEmptyStr(password) == false)
	{
		b = true;
	}

	// Connect
	while (true)
	{
		UINT err;

		rpc = AdminConnectEx(cedar, &o, hub, hashed_password, &err, CEDAR_CUI_STR);
		if (rpc == NULL)
		{
			// Failure
			retcode = err;

			if (err == ERR_ACCESS_DENIED && c->ProgrammingMode == false)
			{
				char *pass;
				// Password is incorrect
				if (b)
				{
					// Input the password
					c->Write(c, _UU("CMD_VPNCMD_PASSWORD_1"));
				}

				b = true;

				pass = c->ReadPassword(c, _UU("CMD_VPNCMD_PASSWORD_2"));
				c->Write(c, L"");

				if (pass != NULL)
				{
					Sha0(hashed_password, pass, StrLen(pass));
					Free(pass);
				}
				else
				{
					break;
				}
			}
			else
			{
				// Other errors
				CmdPrintError(c, err);
				break;
			}
		}
		else
		{
			PS *ps;

			// Success
			ps = NewPs(c, rpc, host, port, hub, adminhub, cmdline);
			PsMain(ps);
			retcode = ps->LastError;
			FreePs(ps);
			AdminDisconnect(rpc);
			break;
		}
	}

	ReleaseCedar(cedar);

	return retcode;
}