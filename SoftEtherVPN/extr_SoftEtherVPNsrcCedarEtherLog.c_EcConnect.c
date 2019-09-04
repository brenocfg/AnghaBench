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
typedef  int /*<<< orphan*/  retcode ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  rand ;
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  RPC ;

/* Variables and functions */
 int /*<<< orphan*/ * Connect (char*,scalar_t__) ; 
 scalar_t__ EL_ADMIN_PORT ; 
 scalar_t__ ERR_AUTH_FAILED ; 
 scalar_t__ ERR_CONNECT_FAILED ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_PROTOCOL_ERROR ; 
 int Endian32 (int) ; 
 int INFINITE ; 
 int RecvAll (int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SecurePassword (int*,int*,int*) ; 
 int /*<<< orphan*/  SendAll (int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  SetTimeout (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Sha0 (int*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * StartRpcClient (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  Zero (int*,int) ; 

UINT EcConnect(char *host, UINT port, char *password, RPC **rpc)
{
	SOCK *s;
	UCHAR password_hash[SHA1_SIZE];
	UCHAR rand[SHA1_SIZE];
	UCHAR response[SHA1_SIZE];
	bool retcode;
	// Validate arguments
	if (host == NULL)
	{
		host = "localhost";
	}
	if (port == 0)
	{
		port = EL_ADMIN_PORT;
	}
	if (password == NULL)
	{
		password = "";
	}
	if (rpc == NULL)
	{
		return ERR_INTERNAL_ERROR;
	}

	// Connect to the server
	s = Connect(host, port);
	if (s == NULL)
	{
		// Connection failure
		return ERR_CONNECT_FAILED;
	}

	SetTimeout(s, 5000);

	// Hash the password
	Sha0(password_hash, password, StrLen(password));

	// Receive the random number
	Zero(rand, sizeof(rand));
	(void)RecvAll(s, rand, sizeof(rand), false);
	SecurePassword(response, password_hash, rand);

	// Send a response
	SendAll(s, response, sizeof(response), false);

	// Receive results
	retcode = false;
	if (RecvAll(s, &retcode, sizeof(retcode), false) == false)
	{
		// Disconnect
		ReleaseSock(s);
		return ERR_PROTOCOL_ERROR;
	}
	retcode = Endian32(retcode);

	if (retcode == false)
	{
		// Password incorrect
		ReleaseSock(s);
		return ERR_AUTH_FAILED;
	}

	// Successful connection
	SetTimeout(s, INFINITE);

	*rpc = StartRpcClient(s, NULL);

	ReleaseSock(s);

	return ERR_NO_ERROR;
}