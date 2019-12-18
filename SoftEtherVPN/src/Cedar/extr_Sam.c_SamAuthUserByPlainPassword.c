#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  suffix_filter_w ;
typedef  int /*<<< orphan*/  suffix_filter ;
typedef  int /*<<< orphan*/  radius_server_addr ;
typedef  int /*<<< orphan*/  radius_secret ;
typedef  int /*<<< orphan*/  nt_username ;
typedef  int /*<<< orphan*/  nt_name ;
typedef  int /*<<< orphan*/  nt_groupname ;
typedef  int /*<<< orphan*/  nt_domainname ;
typedef  int /*<<< orphan*/  name_and_realm ;
struct TYPE_21__ {scalar_t__ AuthType; char* GroupName; int /*<<< orphan*/  lock; TYPE_1__* Policy; scalar_t__ AuthData; } ;
typedef  TYPE_2__ USER ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_26__ {int /*<<< orphan*/ * NtUsername; } ;
struct TYPE_25__ {int /*<<< orphan*/ * RadiusUsername; } ;
struct TYPE_24__ {char* RadiusRealm; int /*<<< orphan*/  lock; int /*<<< orphan*/  Name; int /*<<< orphan*/  ref; } ;
struct TYPE_23__ {int /*<<< orphan*/  MsChapV2_ClientResponse; int /*<<< orphan*/  MsChapV2_PPPUsername; int /*<<< orphan*/  MsChapV2_ServerChallenge; int /*<<< orphan*/  MsChapV2_ClientChallenge; } ;
struct TYPE_22__ {int Out_IsRadiusLogin; } ;
struct TYPE_20__ {int TimeOut; } ;
typedef  TYPE_3__ RADIUS_LOGIN_OPTION ;
typedef  TYPE_4__ IPC_MSCHAP_V2_AUTHINFO ;
typedef  TYPE_5__ HUB ;
typedef  int /*<<< orphan*/  CONNECTION ;
typedef  TYPE_6__ AUTHRADIUS ;
typedef  TYPE_7__ AUTHNT ;

/* Variables and functions */
 scalar_t__ AUTHTYPE_NT ; 
 scalar_t__ AUTHTYPE_RADIUS ; 
 TYPE_2__* AcGetUser (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  AcLock (TYPE_5__*) ; 
 int /*<<< orphan*/  AcUnlock (TYPE_5__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 char* CopyStrToUni (char*) ; 
 char* CopyUniStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  GSF_DISABLE_RADIUS_AUTH ; 
 scalar_t__ GetGlobalServerFlag (int /*<<< orphan*/ ) ; 
 scalar_t__ GetRadiusServerEx2 (TYPE_5__*,char*,int,int*,char*,int,int*,char*,int) ; 
 int /*<<< orphan*/  HLog (TYPE_5__*,char*,char*) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MsChapV2Server_GenerateResponse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsChapV2_GenerateChallenge8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MsCheckLogon (char*,char*) ; 
 int MsPerformMsChapV2AuthByLsa (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ParseAndExtractMsChapV2InfoFromPassword (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  ParseNtUsername (char*,char*,int,char*,int,int) ; 
 int RadiusLogin (int /*<<< orphan*/ *,char*,int,char*,int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseUser (TYPE_2__*) ; 
 int SmbCheckLogon (char*,char*,char*,char*,int) ; 
 int SmbPerformMsChapV2Auth (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  StrToUni (char*,int,char*) ; 
 scalar_t__ UniEndWith (char*,char*) ; 
 scalar_t__ UniIsEmptyStr (char*) ; 
 scalar_t__ UniStrLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToStr (char*,int,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

bool SamAuthUserByPlainPassword(CONNECTION *c, HUB *hub, char *username, char *password, bool ast, UCHAR *mschap_v2_server_response_20, RADIUS_LOGIN_OPTION *opt)
{
	bool b = false;
	wchar_t *name = NULL;
	wchar_t *groupname = NULL;
	UINT timeout = 90;
	bool auth_by_nt = false;
	HUB *h;
	// Validate arguments
	if (hub == NULL || c == NULL || username == NULL)
	{
		return false;
	}

	if (GetGlobalServerFlag(GSF_DISABLE_RADIUS_AUTH) != 0)
	{
		return false;
	}

	h = hub;

	AddRef(h->ref);

	// Get the user name on authentication system
	AcLock(hub);
	{
		USER *u;
		u = AcGetUser(hub, ast == false ? username : "*");
		if (u)
		{
			Lock(u->lock);
			{
				if (u->AuthType == AUTHTYPE_RADIUS)
				{
					// Radius authentication
					AUTHRADIUS *auth = (AUTHRADIUS *)u->AuthData;
					if (ast || auth->RadiusUsername == NULL || UniStrLen(auth->RadiusUsername) == 0)
					{
						if( IsEmptyStr(h->RadiusRealm) == false )
						{	
							char name_and_realm[MAX_SIZE];
							StrCpy(name_and_realm, sizeof(name_and_realm), username);
							StrCat(name_and_realm, sizeof(name_and_realm), "@");
							StrCat(name_and_realm, sizeof(name_and_realm), h->RadiusRealm);
							name = CopyStrToUni(name_and_realm);
						}
						else
						{
							name = CopyStrToUni(username);
						}
					}
					else
					{
						name = CopyUniStr(auth->RadiusUsername);
					}
					auth_by_nt = false;
				}
				else if (u->AuthType == AUTHTYPE_NT)
				{
					// NT authentication
					AUTHNT *auth = (AUTHNT *)u->AuthData;
					if (ast || auth->NtUsername == NULL || UniStrLen(auth->NtUsername) == 0)
					{
						name = CopyStrToUni(username);
					}
					else
					{
						name = CopyUniStr(auth->NtUsername);
					}

					groupname = CopyStrToUni(u->GroupName);
					
					if (u->Policy)
					{
						timeout = u->Policy->TimeOut;
					}

					auth_by_nt = true;
				}
			}
			Unlock(u->lock);
			ReleaseUser(u);
		}
	}
	AcUnlock(hub);

	if (name != NULL)
	{
		if (auth_by_nt == false)
		{
			// Radius authentication
			char radius_server_addr[MAX_SIZE];
			UINT radius_server_port;
			char radius_secret[MAX_SIZE];
			char suffix_filter[MAX_SIZE];
			wchar_t suffix_filter_w[MAX_SIZE];
			UINT interval;

			Zero(suffix_filter, sizeof(suffix_filter));
			Zero(suffix_filter_w, sizeof(suffix_filter_w));

			// Get the Radius server information
			if (GetRadiusServerEx2(hub, radius_server_addr, sizeof(radius_server_addr), &radius_server_port, radius_secret, sizeof(radius_secret), &interval, suffix_filter, sizeof(suffix_filter)))
			{
				Unlock(hub->lock);

				StrToUni(suffix_filter_w, sizeof(suffix_filter_w), suffix_filter);

				if (UniIsEmptyStr(suffix_filter_w) || UniEndWith(name, suffix_filter_w))
				{
					// Attempt to login
					b = RadiusLogin(c, radius_server_addr, radius_server_port,
						radius_secret, StrLen(radius_secret),
						name, password, interval, mschap_v2_server_response_20, opt, hub->Name);

					if (b)
					{
						if (opt != NULL)
						{
							opt->Out_IsRadiusLogin = true;
						}
					}
				}

				Lock(hub->lock);
			}
			else
			{
				HLog(hub, "LH_NO_RADIUS_SETTING", name);
			}
		}
		else
		{
			// NT authentication
#ifdef	OS_WIN32
			IPC_MSCHAP_V2_AUTHINFO mschap;
			Unlock(hub->lock);

			if (ParseAndExtractMsChapV2InfoFromPassword(&mschap, password) == false)
			{
				// Plaintext password authentication
				b = MsCheckLogon(name, password);
			}
			else
			{
				UCHAR challenge8[8];
				UCHAR nt_pw_hash_hash[16];
				char nt_name[MAX_SIZE];

				UniToStr(nt_name, sizeof(nt_name), name);

				// MS-CHAPv2 authentication
				MsChapV2_GenerateChallenge8(challenge8, mschap.MsChapV2_ClientChallenge,
					mschap.MsChapV2_ServerChallenge,
					mschap.MsChapV2_PPPUsername);

				Debug("MsChapV2_PPPUsername = %s, nt_name = %s\n", mschap.MsChapV2_PPPUsername, nt_name);

				b = MsPerformMsChapV2AuthByLsa(nt_name, challenge8, mschap.MsChapV2_ClientResponse, nt_pw_hash_hash);

				if (b)
				{
					if (mschap_v2_server_response_20 != NULL)
					{
						MsChapV2Server_GenerateResponse(mschap_v2_server_response_20, nt_pw_hash_hash,
							mschap.MsChapV2_ClientResponse, challenge8);
					}
				}
			}

			Lock(hub->lock);
#else	// OS_WIN32
			// Unix / Samba Winbind

			IPC_MSCHAP_V2_AUTHINFO mschap;
			Unlock(hub->lock);

			char nt_name[MAX_SIZE];
			char nt_username[MAX_SIZE];
			char nt_groupname[MAX_SIZE];
			char nt_domainname[MAX_SIZE];
			UCHAR challenge8[8];
			UCHAR nt_pw_hash_hash[16];

			nt_groupname[0] = 0;

			UniToStr(nt_name, sizeof(nt_name), name);

			if (groupname != NULL)
				UniToStr(nt_groupname, sizeof(nt_groupname), groupname);

			ParseNtUsername(nt_name, nt_username, sizeof(nt_username), nt_domainname, sizeof(nt_domainname), false);

			if (ParseAndExtractMsChapV2InfoFromPassword(&mschap, password) == false)
			{
				// Plaintext password authentication
				b = SmbCheckLogon(nt_username, password, nt_domainname, nt_groupname, timeout);
			}
			else
			{
				// MS-CHAPv2 authentication
				MsChapV2_GenerateChallenge8(challenge8, mschap.MsChapV2_ClientChallenge,
					mschap.MsChapV2_ServerChallenge,
					mschap.MsChapV2_PPPUsername);

				Debug("MsChapV2_PPPUsername = %s, nt_name = %s\n", mschap.MsChapV2_PPPUsername, nt_name);

				b = SmbPerformMsChapV2Auth(nt_username, nt_domainname, nt_groupname, challenge8, mschap.MsChapV2_ClientResponse, nt_pw_hash_hash, timeout);

				if (b)
				{
					if (mschap_v2_server_response_20 != NULL)
					{
						MsChapV2Server_GenerateResponse(mschap_v2_server_response_20, nt_pw_hash_hash,
							mschap.MsChapV2_ClientResponse, challenge8);
					}
				}
			}

			Lock(hub->lock);
#endif	// OS_WIN32 / OS_LINUX
		}

		// Memory release
		if( groupname != NULL )
			Free(groupname);
		Free(name);
	}

	ReleaseHub(h);

	return b;
}