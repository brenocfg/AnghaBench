#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mschap ;
typedef  int /*<<< orphan*/  client_response ;
typedef  int /*<<< orphan*/  challenge8 ;
struct TYPE_25__ {scalar_t__ AuthType; int /*<<< orphan*/  lock; scalar_t__ AuthData; } ;
typedef  TYPE_1__ USER ;
typedef  scalar_t__ UINT ;
struct TYPE_26__ {void* MsChapV2_ClientResponse; int /*<<< orphan*/  MsChapV2_PPPUsername; int /*<<< orphan*/  MsChapV2_ServerChallenge; int /*<<< orphan*/  MsChapV2_ClientChallenge; } ;
typedef  TYPE_2__ UCHAR ;
struct TYPE_28__ {int /*<<< orphan*/  NtLmSecureHash; int /*<<< orphan*/  HashedKey; } ;
struct TYPE_27__ {int /*<<< orphan*/  SecurePassword; } ;
typedef  TYPE_2__ IPC_MSCHAP_V2_AUTHINFO ;
typedef  TYPE_4__ HUB ;
typedef  TYPE_5__ AUTHPASSWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ADMINISTRATOR_USERNAME ; 
 scalar_t__ AUTHTYPE_PASSWORD ; 
 TYPE_1__* AcGetUser (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  AcLock (TYPE_4__*) ; 
 int /*<<< orphan*/  AcUnlock (TYPE_4__*) ; 
 scalar_t__ Cmp (TYPE_2__*,void*,int) ; 
 scalar_t__ ERR_MSCHAP2_PASSWORD_NEED_RESET ; 
 int /*<<< orphan*/  GenerateNtPasswordHashHash (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MD5_SIZE ; 
 int /*<<< orphan*/  MsChapV2Client_GenerateResponse (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsChapV2Server_GenerateResponse (TYPE_2__*,TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  MsChapV2_GenerateChallenge8 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ParseAndExtractMsChapV2InfoFromPassword (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ReleaseUser (TYPE_1__*) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SecurePassword (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ StrCmpi (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool SamAuthUserByPassword(HUB *h, char *username, void *random, void *secure_password, char *mschap_v2_password, UCHAR *mschap_v2_server_response_20, UINT *err)
{
	bool b = false;
	UCHAR secure_password_check[SHA1_SIZE];
	bool is_mschap = false;
	IPC_MSCHAP_V2_AUTHINFO mschap;
	UINT dummy = 0;
	// Validate arguments
	if (h == NULL || username == NULL || secure_password == NULL)
	{
		return false;
	}
	if (err == NULL)
	{
		err = &dummy;
	}

	*err = 0;

	Zero(&mschap, sizeof(mschap));

	is_mschap = ParseAndExtractMsChapV2InfoFromPassword(&mschap, mschap_v2_password);

	if (StrCmpi(username, ADMINISTRATOR_USERNAME) == 0)
	{
		// Administrator mode
		SecurePassword(secure_password_check, h->SecurePassword, random);
		if (Cmp(secure_password_check, secure_password, SHA1_SIZE) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	AcLock(h);
	{
		USER *u;
		u = AcGetUser(h, username);
		if (u)
		{
			Lock(u->lock);
			{
				if (u->AuthType == AUTHTYPE_PASSWORD)
				{
					AUTHPASSWORD *auth = (AUTHPASSWORD *)u->AuthData;

					if (is_mschap == false)
					{
						// Normal password authentication
						SecurePassword(secure_password_check, auth->HashedKey, random);
						if (Cmp(secure_password_check, secure_password, SHA1_SIZE) == 0)
						{
							b = true;
						}
					}
					else
					{
						// MS-CHAP v2 authentication via PPP
						UCHAR challenge8[8];
						UCHAR client_response[24];

						if (IsZero(auth->NtLmSecureHash, MD5_SIZE))
						{
							// NTLM hash is not registered in the user account
							*err = ERR_MSCHAP2_PASSWORD_NEED_RESET;
						}
						else
						{
							UCHAR nt_pw_hash_hash[16];
							Zero(challenge8, sizeof(challenge8));
							Zero(client_response, sizeof(client_response));

							MsChapV2_GenerateChallenge8(challenge8, mschap.MsChapV2_ClientChallenge, mschap.MsChapV2_ServerChallenge,
								mschap.MsChapV2_PPPUsername);

							MsChapV2Client_GenerateResponse(client_response, challenge8, auth->NtLmSecureHash);

							if (Cmp(client_response, mschap.MsChapV2_ClientResponse, 24) == 0)
							{
								// Hash matched
								b = true;

								// Calculate the response
								GenerateNtPasswordHashHash(nt_pw_hash_hash, auth->NtLmSecureHash);
								MsChapV2Server_GenerateResponse(mschap_v2_server_response_20, nt_pw_hash_hash,
									client_response, challenge8);
							}
						}
					}
				}
			}
			Unlock(u->lock);
			ReleaseUser(u);
		}
	}
	AcUnlock(h);

	return b;
}