#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  realname ;
typedef  int /*<<< orphan*/  note ;
typedef  int /*<<< orphan*/  md4_password ;
typedef  int /*<<< orphan*/  hashed_password ;
typedef  int /*<<< orphan*/  groupname ;
typedef  int /*<<< orphan*/  common_name ;
typedef  int /*<<< orphan*/  X_SERIAL ;
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  USERGROUP ;
struct TYPE_24__ {int NumLogin; int /*<<< orphan*/  lock; void* LastLoginTime; void* ExpireTime; void* UpdatedTime; void* CreatedTime; } ;
typedef  TYPE_1__ USER ;
typedef  void* UINT64 ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_26__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_25__ {char* Name; } ;
typedef  int /*<<< orphan*/  TRAFFIC ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  int /*<<< orphan*/  HUB ;
typedef  TYPE_2__ FOLDER ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
#define  AUTHTYPE_NT 132 
#define  AUTHTYPE_PASSWORD 131 
#define  AUTHTYPE_RADIUS 130 
#define  AUTHTYPE_ROOTCERT 129 
#define  AUTHTYPE_USERCERT 128 
 int /*<<< orphan*/  AcAddUser (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * AcGetGroup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  AcLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BufToX (TYPE_3__*,int) ; 
 TYPE_3__* CfgGetBuf (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  CfgGetByte (TYPE_2__*,char*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* CfgGetFolder (TYPE_2__*,char*) ; 
 int CfgGetInt (TYPE_2__*,char*) ; 
 void* CfgGetInt64 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  CfgGetStr (TYPE_2__*,char*,char*,int) ; 
 int /*<<< orphan*/  CfgGetUniStr (TYPE_2__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeXSerial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JoinUserToGroup (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int MD5_SIZE ; 
 void* NewNTAuthData (int /*<<< orphan*/ *) ; 
 void* NewPasswordAuthDataRaw (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* NewRadiusAuthData (int /*<<< orphan*/ *) ; 
 void* NewRootCertAuthData (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* NewUser (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void*) ; 
 void* NewUserCertAuthData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewXSerial (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseGroup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseUser (TYPE_1__*) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SetUserPolicy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetUserTraffic (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadPolicyCfg (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SiLoadTraffic (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void SiLoadUserCfg(HUB *h, FOLDER *f)
{
	char *username;
	wchar_t realname[MAX_SIZE];
	wchar_t note[MAX_SIZE];
	char groupname[MAX_SIZE];
	FOLDER *pf;
	UINT64 created_time;
	UINT64 updated_time;
	UINT64 expire_time;
	UINT64 last_login_time;
	UINT num_login;
	POLICY p;
	TRAFFIC t;
	BUF *b;
	UINT authtype;
	void *authdata;
	X_SERIAL *serial = NULL;
	wchar_t common_name[MAX_SIZE];
	UCHAR hashed_password[SHA1_SIZE];
	UCHAR md4_password[MD5_SIZE];
	wchar_t tmp[MAX_SIZE];
	USER *u;
	USERGROUP *g;
	// Validate arguments
	if (h == NULL || f == NULL)
	{
		return;
	}

	username = f->Name;
	CfgGetUniStr(f, "RealName", realname, sizeof(realname));
	CfgGetUniStr(f, "Note", note, sizeof(note));
	CfgGetStr(f, "GroupName", groupname, sizeof(groupname));

	created_time = CfgGetInt64(f, "CreatedTime");
	updated_time = CfgGetInt64(f, "UpdatedTime");
	expire_time = CfgGetInt64(f, "ExpireTime");
	last_login_time = CfgGetInt64(f, "LastLoginTime");
	num_login = CfgGetInt(f, "NumLogin");
	pf = CfgGetFolder(f, "Policy");
	if (pf != NULL)
	{
		SiLoadPolicyCfg(&p, pf);
	}
	SiLoadTraffic(f, "Traffic", &t);

	authtype = CfgGetInt(f, "AuthType");
	authdata = NULL;

	switch (authtype)
	{
	case AUTHTYPE_PASSWORD:
		Zero(hashed_password, sizeof(hashed_password));
		Zero(md4_password, sizeof(md4_password));
		CfgGetByte(f, "AuthPassword", hashed_password, sizeof(hashed_password));
		CfgGetByte(f, "AuthNtLmSecureHash", md4_password, sizeof(md4_password));
		authdata = NewPasswordAuthDataRaw(hashed_password, md4_password);
		break;

	case AUTHTYPE_NT:
		if (CfgGetUniStr(f, "AuthNtUserName", tmp, sizeof(tmp)))
		{
			authdata = NewNTAuthData(tmp);
		}
		else
		{
			authdata = NewNTAuthData(NULL);
		}
		break;

	case AUTHTYPE_RADIUS:
		if (CfgGetUniStr(f, "AuthRadiusUsername", tmp, sizeof(tmp)))
		{
			authdata = NewRadiusAuthData(tmp);
		}
		else
		{
			authdata = NewRadiusAuthData(NULL);
		}
		break;

	case AUTHTYPE_USERCERT:
		b = CfgGetBuf(f, "AuthUserCert");
		if (b != NULL)
		{
			X *x = BufToX(b, false);
			if (x != NULL)
			{
				authdata = NewUserCertAuthData(x);
				FreeX(x);
			}
			FreeBuf(b);
		}
		break;

	case AUTHTYPE_ROOTCERT:
		b = CfgGetBuf(f, "AuthSerial");
		if (b != NULL)
		{
			serial = NewXSerial(b->Buf, b->Size);
			FreeBuf(b);
		}
		CfgGetUniStr(f, "AuthCommonName", common_name, sizeof(common_name));
		authdata = NewRootCertAuthData(serial, common_name);
		break;
	}

	// Add an user
	AcLock(h);
	{
		if (StrLen(groupname) > 0)
		{
			g = AcGetGroup(h, groupname);
		}
		else
		{
			g = NULL;
		}

		u = NewUser(username, realname, note, authtype, authdata);
		if (u != NULL)
		{
			if (g != NULL)
			{
				JoinUserToGroup(u, g);
			}

			SetUserTraffic(u, &t);

			if (pf != NULL)
			{
				SetUserPolicy(u, &p);
			}

			Lock(u->lock);
			{
				u->CreatedTime = created_time;
				u->UpdatedTime = updated_time;
				u->ExpireTime = expire_time;
				u->LastLoginTime = last_login_time;
				u->NumLogin = num_login;
			}
			Unlock(u->lock);

			AcAddUser(h, u);

			ReleaseUser(u);
		}

		if (g != NULL)
		{
			ReleaseGroup(g);
		}
	}
	AcUnlock(h);

	if (serial != NULL)
	{
		FreeXSerial(serial);
	}
}