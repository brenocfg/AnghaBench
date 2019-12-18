#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secure_password ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  Random; int /*<<< orphan*/ * FirstSock; } ;
struct TYPE_6__ {TYPE_3__* Connection; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ SESSION ;
typedef  int /*<<< orphan*/  RPC_WINVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 scalar_t__ ERR_DISCONNECTED ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 scalar_t__ GetErrorFromPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetWinVer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HttpClientRecv (int /*<<< orphan*/ *) ; 
 int HttpClientSend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 TYPE_1__* NewRpcSessionEx2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,char*,void*) ; 
 int /*<<< orphan*/  OutRpcWinVer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackAddClientVersion (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_1__*) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SecurePassword (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

SESSION *AdminConnectMain(CEDAR *cedar, CLIENT_OPTION *o, char *hubname, void *hashed_password, UINT *err, char *client_name, void *hWnd, bool *empty_password)
{
	UCHAR secure_password[SHA1_SIZE];
	SESSION *s;
	SOCK *sock;
	PACK *p;
	RPC_WINVER ver;
	// connect
	s = NewRpcSessionEx2(cedar, o, err, client_name, hWnd);
	if (s == NULL)
	{
		return NULL;
	}

	// Get socket
	sock = s->Connection->FirstSock;

	// Generate connect method
	p = NewPack();

	PackAddClientVersion(p, s->Connection);

	PackAddStr(p, "method", "admin");
	PackAddBool(p, "accept_empty_password", true);

	// Windows version on client
	GetWinVer(&ver);
	OutRpcWinVer(p, &ver);

	// Secure Password
	SecurePassword(secure_password, hashed_password, s->Connection->Random);

	PackAddData(p, "secure_password", secure_password, sizeof(secure_password));

	// HUB name
	if (hubname != NULL)
	{
		PackAddStr(p, "hubname", hubname);
	}

	if (HttpClientSend(sock, p) == false)
	{
		// disconnect
		FreePack(p);
		ReleaseSession(s);
		*err = ERR_DISCONNECTED;
		return NULL;
	}

	FreePack(p);

	p = HttpClientRecv(sock);
	if (p == NULL)
	{
		// disconnect
		ReleaseSession(s);
		*err = ERR_DISCONNECTED;
		return NULL;
	}

	if (GetErrorFromPack(p) != 0)
	{
		// error
		ReleaseSession(s);
		*err = GetErrorFromPack(p);
		FreePack(p);
		return NULL;
	}

	if (empty_password != NULL)
	{
		*empty_password = PackGetBool(p, "empty_password");
	}

	FreePack(p);

	return s;
}