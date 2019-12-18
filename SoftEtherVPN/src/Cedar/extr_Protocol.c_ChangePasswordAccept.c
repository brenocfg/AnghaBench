#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  username ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  secure_old_password ;
typedef  int /*<<< orphan*/  new_password_ntlm ;
typedef  int /*<<< orphan*/  new_password ;
typedef  int /*<<< orphan*/  hubname ;
struct TYPE_15__ {scalar_t__ AuthType; int /*<<< orphan*/  lock; scalar_t__ AuthData; TYPE_4__* Group; TYPE_2__* Policy; } ;
typedef  TYPE_5__ USER ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_17__ {int /*<<< orphan*/ * NtLmSecureHash; int /*<<< orphan*/ * HashedKey; } ;
struct TYPE_16__ {int /*<<< orphan*/  Name; TYPE_1__* FirstSock; int /*<<< orphan*/ * Cedar; int /*<<< orphan*/ * Random; } ;
struct TYPE_14__ {TYPE_3__* Policy; } ;
struct TYPE_13__ {int FixPassword; } ;
struct TYPE_12__ {int FixPassword; } ;
struct TYPE_11__ {int /*<<< orphan*/  RemoteIP; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  HUB ;
typedef  TYPE_6__ CONNECTION ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_7__ AUTHPASSWORD ;

/* Variables and functions */
 scalar_t__ AUTHTYPE_PASSWORD ; 
 TYPE_5__* AcGetUser (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  AcLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcUnlock (int /*<<< orphan*/ *) ; 
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_NOT_ENOUGH_RIGHT ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ERR_OLD_PASSWORD_WRONG ; 
 int /*<<< orphan*/  ERR_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  ERR_USER_AUTHTYPE_NOT_PASSWORD ; 
 int /*<<< orphan*/ * GetHub (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ GetHubAdminOption (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  HLog (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MAX_USERNAME_LEN ; 
 int MD5_SIZE ; 
 int PackGetData2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseUser (TYPE_5__*) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SecurePassword (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

UINT ChangePasswordAccept(CONNECTION *c, PACK *p)
{
	CEDAR *cedar;
	UCHAR random[SHA1_SIZE];
	char hubname[MAX_HUBNAME_LEN + 1];
	char username[MAX_USERNAME_LEN + 1];
	UCHAR secure_old_password[SHA1_SIZE];
	UCHAR new_password[SHA1_SIZE];
	UCHAR new_password_ntlm[SHA1_SIZE];
	UCHAR check_secure_old_password[SHA1_SIZE];
	UINT ret = ERR_NO_ERROR;
	HUB *hub;
	// Validate arguments
	if (c == NULL || p == NULL)
	{
		return ERR_INTERNAL_ERROR;
	}

	Copy(random, c->Random, SHA1_SIZE);
	if (PackGetStr(p, "hubname", hubname, sizeof(hubname)) == false ||
		PackGetStr(p, "username", username, sizeof(username)) == false ||
		PackGetData2(p, "secure_old_password", secure_old_password, sizeof(secure_old_password)) == false ||
		PackGetData2(p, "new_password", new_password, sizeof(new_password)) == false)
	{
		return ERR_PROTOCOL_ERROR;
	}

	if (PackGetData2(p, "new_password_ntlm", new_password_ntlm, MD5_SIZE) == false)
	{
		Zero(new_password_ntlm, sizeof(new_password_ntlm));
	}

	cedar = c->Cedar;

	LockHubList(cedar);
	{
		hub = GetHub(cedar, hubname);
	}
	UnlockHubList(cedar);

	if (hub == NULL)
	{
		ret = ERR_HUB_NOT_FOUND;
	}
	else
	{
		char tmp[MAX_SIZE];

		if (GetHubAdminOption(hub, "deny_change_user_password") != 0)
		{
			ReleaseHub(hub);
			return ERR_NOT_ENOUGH_RIGHT;
		}

		IPToStr(tmp, sizeof(tmp), &c->FirstSock->RemoteIP);
		HLog(hub, "LH_CHANGE_PASSWORD_1", c->Name, tmp);

		AcLock(hub);
		{
			USER *u = AcGetUser(hub, username);
			if (u == NULL)
			{
				HLog(hub, "LH_CHANGE_PASSWORD_2", c->Name, username);
				ret = ERR_OLD_PASSWORD_WRONG;
			}
			else
			{
				Lock(u->lock);
				{
					if (u->AuthType	!= AUTHTYPE_PASSWORD)
					{
						// Not a password authentication
						HLog(hub, "LH_CHANGE_PASSWORD_3", c->Name, username);
						ret = ERR_USER_AUTHTYPE_NOT_PASSWORD;
					}
					else
					{
						bool fix_password = false;
						if (u->Policy != NULL)
						{
							fix_password = u->Policy->FixPassword;
						}
						else
						{
							if (u->Group != NULL)
							{
								if (u->Group->Policy != NULL)
								{
									fix_password = u->Group->Policy->FixPassword;
								}
							}
						}
						if (fix_password == false)
						{
							// Confirmation of the old password
							AUTHPASSWORD *pw = (AUTHPASSWORD *)u->AuthData;

							SecurePassword(check_secure_old_password, pw->HashedKey, random);
							if (Cmp(check_secure_old_password, secure_old_password, SHA1_SIZE) != 0)
							{
								// Old password is incorrect
								ret = ERR_OLD_PASSWORD_WRONG;
								HLog(hub, "LH_CHANGE_PASSWORD_4", c->Name, username);
							}
							else
							{
								// Write a new password
								if (Cmp(pw->HashedKey, new_password, SHA1_SIZE) != 0 || IsZero(pw->NtLmSecureHash, MD5_SIZE))
								{
									Copy(pw->HashedKey, new_password, SHA1_SIZE);
									Copy(pw->NtLmSecureHash, new_password_ntlm, MD5_SIZE);
								}
								HLog(hub, "LH_CHANGE_PASSWORD_5", c->Name, username);
							}
						}
						else
						{
							// Password change is prohibited
							ret = ERR_NOT_ENOUGH_RIGHT;
						}
					}
				}
				Unlock(u->lock);

				ReleaseUser(u);
			}
		}
		AcUnlock(hub);
		ReleaseHub(hub);
	}

	return ret;
}