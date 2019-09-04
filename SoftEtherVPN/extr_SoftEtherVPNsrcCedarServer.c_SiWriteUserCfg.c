#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int NumLogin; int AuthType; int /*<<< orphan*/  lock; int /*<<< orphan*/ * AuthData; int /*<<< orphan*/  Traffic; int /*<<< orphan*/ * Policy; int /*<<< orphan*/  LastLoginTime; int /*<<< orphan*/  ExpireTime; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  GroupName; int /*<<< orphan*/ * Group; int /*<<< orphan*/ * Note; int /*<<< orphan*/ * RealName; } ;
typedef  TYPE_2__ USER ;
struct TYPE_15__ {int /*<<< orphan*/ * NtUsername; } ;
struct TYPE_14__ {int /*<<< orphan*/  NtLmSecureHash; int /*<<< orphan*/  HashedKey; } ;
struct TYPE_13__ {int /*<<< orphan*/ * RadiusUsername; } ;
struct TYPE_12__ {int /*<<< orphan*/ * CommonName; TYPE_1__* Serial; } ;
struct TYPE_11__ {int /*<<< orphan*/  UserX; } ;
struct TYPE_9__ {int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;
typedef  TYPE_3__ AUTHUSERCERT ;
typedef  TYPE_4__ AUTHROOTCERT ;
typedef  TYPE_5__ AUTHRADIUS ;
typedef  TYPE_6__ AUTHPASSWORD ;
typedef  TYPE_7__ AUTHNT ;

/* Variables and functions */
#define  AUTHTYPE_ANONYMOUS 133 
#define  AUTHTYPE_NT 132 
#define  AUTHTYPE_PASSWORD 131 
#define  AUTHTYPE_RADIUS 130 
#define  AUTHTYPE_ROOTCERT 129 
#define  AUTHTYPE_USERCERT 128 
 int /*<<< orphan*/  CfgAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgAddByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  CfgAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int IsZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiWritePolicyCfg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SiWriteTraffic (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XToBuf (int /*<<< orphan*/ ,int) ; 

void SiWriteUserCfg(FOLDER *f, USER *u)
{
	BUF *b;
	AUTHPASSWORD *password;
	AUTHRADIUS *radius;
	AUTHNT *nt;
	AUTHUSERCERT *usercert;
	AUTHROOTCERT *rootcert;
	// Validate arguments
	if (f == NULL || u == NULL)
	{
		return;
	}

	Lock(u->lock);
	{
		CfgAddUniStr(f, "RealName", u->RealName);
		CfgAddUniStr(f, "Note", u->Note);
		if (u->Group != NULL)
		{
			CfgAddStr(f, "GroupName", u->GroupName);
		}
		CfgAddInt64(f, "CreatedTime", u->CreatedTime);
		CfgAddInt64(f, "UpdatedTime", u->UpdatedTime);
		CfgAddInt64(f, "ExpireTime", u->ExpireTime);
		CfgAddInt64(f, "LastLoginTime", u->LastLoginTime);
		CfgAddInt(f, "NumLogin", u->NumLogin);
		if (u->Policy != NULL)
		{
			SiWritePolicyCfg(CfgCreateFolder(f, "Policy"), u->Policy, false);
		}
		SiWriteTraffic(f, "Traffic", u->Traffic);

		CfgAddInt(f, "AuthType", u->AuthType);
		if (u->AuthData != NULL)
		{
			switch (u->AuthType)
			{
			case AUTHTYPE_ANONYMOUS:
				break;

			case AUTHTYPE_PASSWORD:
				password = (AUTHPASSWORD *)u->AuthData;
				CfgAddByte(f, "AuthPassword", password->HashedKey, sizeof(password->HashedKey));

				if (IsZero(password->NtLmSecureHash, sizeof(password->NtLmSecureHash)) == false)
				{
					CfgAddByte(f, "AuthNtLmSecureHash", password->NtLmSecureHash, sizeof(password->NtLmSecureHash));
				}
				break;

			case AUTHTYPE_NT:
				nt = (AUTHNT *)u->AuthData;
				CfgAddUniStr(f, "AuthNtUserName", nt->NtUsername);
				break;

			case AUTHTYPE_RADIUS:
				radius = (AUTHRADIUS *)u->AuthData;
				CfgAddUniStr(f, "AuthRadiusUsername", radius->RadiusUsername);
				break;

			case AUTHTYPE_USERCERT:
				usercert = (AUTHUSERCERT *)u->AuthData;
				b = XToBuf(usercert->UserX, false);
				if (b != NULL)
				{
					CfgAddBuf(f, "AuthUserCert", b);
					FreeBuf(b);
				}
				break;

			case AUTHTYPE_ROOTCERT:
				rootcert = (AUTHROOTCERT *)u->AuthData;
				if (rootcert->Serial != NULL && rootcert->Serial->size >= 1)
				{
					CfgAddByte(f, "AuthSerial", rootcert->Serial->data, rootcert->Serial->size);
				}
				if (rootcert->CommonName != NULL && UniIsEmptyStr(rootcert->CommonName) == false)
				{
					CfgAddUniStr(f, "AuthCommonName", rootcert->CommonName);
				}
				break;
			}
		}
	}
	Unlock(u->lock);
}