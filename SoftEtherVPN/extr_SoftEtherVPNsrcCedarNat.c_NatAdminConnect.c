#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  RPC ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * Connect (char*,scalar_t__) ; 
 scalar_t__ ERR_CONNECT_FAILED ; 
 scalar_t__ ERR_DISCONNECTED ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 scalar_t__ GetErrorFromPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HttpClientRecv (int /*<<< orphan*/ *) ; 
 int HttpClientSend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int PackGetData2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SecurePassword (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetTimeout (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * StartRpcClient (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int StartSSL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TIMEOUT_INFINITE ; 

RPC *NatAdminConnect(CEDAR *cedar, char *hostname, UINT port, void *hashed_password, UINT *err)
{
	UCHAR secure_password[SHA1_SIZE];
	UCHAR random[SHA1_SIZE];
	SOCK *sock;
	RPC *rpc;
	PACK *p;
	UINT error;
	// Validate arguments
	if (cedar == NULL || hostname == NULL || port == 0 || hashed_password == NULL || err == NULL)
	{
		if (err != NULL)
		{
			*err = ERR_INTERNAL_ERROR;
		}
		return NULL;
	}

	// Connection
	sock = Connect(hostname, port);
	if (sock == NULL)
	{
		*err = ERR_CONNECT_FAILED;
		return NULL;
	}

	if (StartSSL(sock, NULL, NULL) == false)
	{
		*err = ERR_PROTOCOL_ERROR;
		ReleaseSock(sock);
		return NULL;
	}

	SetTimeout(sock, 5000);

	p = HttpClientRecv(sock);
	if (p == NULL)
	{
		*err = ERR_DISCONNECTED;
		ReleaseSock(sock);
		return NULL;
	}

	if (PackGetData2(p, "auth_random", random, SHA1_SIZE) == false)
	{
		FreePack(p);
		*err = ERR_PROTOCOL_ERROR;
		ReleaseSock(sock);
		return NULL;
	}

	FreePack(p);

	SecurePassword(secure_password, hashed_password, random);

	p = NewPack();
	PackAddData(p, "secure_password", secure_password, SHA1_SIZE);

	if (HttpClientSend(sock, p) == false)
	{
		FreePack(p);
		*err = ERR_DISCONNECTED;
		ReleaseSock(sock);
		return NULL;
	}

	FreePack(p);

	p = HttpClientRecv(sock);
	if (p == NULL)
	{
		*err = ERR_DISCONNECTED;
		ReleaseSock(sock);
		return NULL;
	}

	error = GetErrorFromPack(p);

	FreePack(p);

	if (error != ERR_NO_ERROR)
	{
		*err = error;
		ReleaseSock(sock);
		return NULL;
	}

	SetTimeout(sock, TIMEOUT_INFINITE);

	rpc = StartRpcClient(sock, NULL);
	ReleaseSock(sock);

	return rpc;
}