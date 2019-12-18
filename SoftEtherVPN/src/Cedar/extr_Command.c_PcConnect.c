#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  pass ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_14__ {char* (* ReadPassword ) (TYPE_2__*,char*) ;int /*<<< orphan*/  (* Write ) (TYPE_2__*,char*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  LastError; } ;
typedef  int /*<<< orphan*/  REMOTE_CLIENT ;
typedef  TYPE_1__ PC ;
typedef  TYPE_2__ CONSOLE ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * CcConnectRpc (char*,char*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CcDisconnectRpc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERR_CONNECT_FAILED ; 
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreePc (TYPE_1__*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewCedar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* NewPc (TYPE_2__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PcMain (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,char*) ; 
 char* stub3 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,char*) ; 

UINT PcConnect(CONSOLE *c, char *target, wchar_t *cmdline, char *password)
{
	CEDAR *cedar;
	REMOTE_CLIENT *client;
	bool bad_pass;
	bool no_remote;
	char pass[MAX_SIZE];
	UINT ret = 0;
	// Validate arguments
	if (c == NULL || target == NULL)
	{
		return ERR_INTERNAL_ERROR;
	}

	StrCpy(pass, sizeof(pass), password);

	cedar = NewCedar(NULL, NULL);

RETRY:
	client = CcConnectRpc(target, pass, &bad_pass, &no_remote, 0);

	if (client == NULL)
	{
		if (no_remote)
		{
			// Remote connection refusal
			c->Write(c, _UU("CMD_VPNCMD_CLIENT_NO_REMODE"));
			ReleaseCedar(cedar);
			return ERR_INTERNAL_ERROR;
		}
		else if (bad_pass)
		{
			char *tmp;
			// Password is different
			c->Write(c, _UU("CMD_VPNCMD_PASSWORD_1"));
			tmp = c->ReadPassword(c, _UU("CMD_VPNCMD_PASSWORD_2"));
			c->Write(c, L"");

			if (tmp == NULL)
			{
				// Cancel
				ReleaseCedar(cedar);
				return ERR_ACCESS_DENIED;
			}
			else
			{
				StrCpy(pass, sizeof(pass), tmp);
				Free(tmp);
			}

			goto RETRY;
		}
		else
		{
			// Connection failure
			CmdPrintError(c, ERR_CONNECT_FAILED);
			ReleaseCedar(cedar);
			return ERR_CONNECT_FAILED;
		}
	}
	else
	{
		// Connection complete
		PC *pc = NewPc(c, client, target, cmdline);
		PcMain(pc);
		ret = pc->LastError;
		FreePc(pc);
	}

	CcDisconnectRpc(client);

	ReleaseCedar(cedar);

	return ret;
}