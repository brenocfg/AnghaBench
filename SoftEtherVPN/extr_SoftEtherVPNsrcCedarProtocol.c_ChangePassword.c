#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  Random; int /*<<< orphan*/ * FirstSock; } ;
struct TYPE_5__ {TYPE_3__* Connection; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ SESSION ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DISCONNECTED ; 
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GenerateNtPasswordHash (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetErrorFromPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HashPassword (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * HttpClientRecv (int /*<<< orphan*/ *) ; 
 scalar_t__ HttpClientSend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MD5_SIZE ; 
 int /*<<< orphan*/ * NewPack () ; 
 TYPE_1__* NewRpcSessionEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddClientVersion (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_1__*) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SecurePassword (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

UINT ChangePassword(CEDAR *cedar, CLIENT_OPTION *o, char *hubname, char *username, char *old_pass, char *new_pass)
{
	UINT ret = ERR_NO_ERROR;
	UCHAR old_password[SHA1_SIZE];
	UCHAR secure_old_password[SHA1_SIZE];
	UCHAR new_password[SHA1_SIZE];
	UCHAR new_password_ntlm[MD5_SIZE];
	SOCK *sock;
	SESSION *s;
	// Validate arguments
	if (cedar == NULL || o == NULL || hubname == NULL || username == NULL || old_pass == NULL || new_pass == NULL)
	{
		return ERR_INTERNAL_ERROR;
	}


	// Create a session
	s = NewRpcSessionEx(cedar, o, &ret, NULL);

	if (s != NULL)
	{
		PACK *p = NewPack();

		sock = s->Connection->FirstSock;

		HashPassword(old_password, username, old_pass);
		SecurePassword(secure_old_password, old_password, s->Connection->Random);
		HashPassword(new_password, username, new_pass);
		GenerateNtPasswordHash(new_password_ntlm, new_pass);

		PackAddClientVersion(p, s->Connection);

		PackAddStr(p, "method", "password");
		PackAddStr(p, "hubname", hubname);
		PackAddStr(p, "username", username);
		PackAddData(p, "secure_old_password", secure_old_password, SHA1_SIZE);
		PackAddData(p, "new_password", new_password, SHA1_SIZE);
		PackAddData(p, "new_password_ntlm", new_password_ntlm, MD5_SIZE);

		if (HttpClientSend(sock, p))
		{
			PACK *p = HttpClientRecv(sock);
			if (p == NULL)
			{
				ret = ERR_DISCONNECTED;
			}
			else
			{
				ret = GetErrorFromPack(p);
			}
			FreePack(p);
		}
		else
		{
			ret = ERR_DISCONNECTED;
		}
		FreePack(p);

		ReleaseSession(s);
	}

	return ret;
}