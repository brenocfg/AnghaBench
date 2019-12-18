#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sl ;
typedef  int /*<<< orphan*/  d ;
typedef  size_t UINT ;
struct TYPE_13__ {int /*<<< orphan*/  Password; int /*<<< orphan*/  UserName; int /*<<< orphan*/  HubName; int /*<<< orphan*/  Id; void* EtherIP_IPsec; void* L2TP_IPsec; void* L2TP_Raw; int /*<<< orphan*/  L2TP_DefaultHub; int /*<<< orphan*/  IPsec_Secret; } ;
struct TYPE_12__ {scalar_t__ ServerType; int /*<<< orphan*/  IPsecServer; } ;
struct TYPE_11__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ IPSEC_SERVICES ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_3__ ETHERIP_ID ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddEtherIPId (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_1__* CfgEnumFolderToTokenList (int /*<<< orphan*/ *) ; 
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 char* DecryptPassword2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  IPsecServerSetServices (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 

void SiLoadIPsec(SERVER *s, FOLDER *f)
{
	IPSEC_SERVICES sl;
	FOLDER *list_folder;
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return;
	}

	Zero(&sl, sizeof(sl));

	CfgGetStr(f, "IPsec_Secret", sl.IPsec_Secret, sizeof(sl.IPsec_Secret));
	CfgGetStr(f, "L2TP_DefaultHub", sl.L2TP_DefaultHub, sizeof(sl.L2TP_DefaultHub));

	if (s->ServerType == SERVER_TYPE_STANDALONE)
	{
		// IPsec feature only be enabled on a standalone server
		sl.L2TP_Raw = CfgGetBool(f, "L2TP_Raw");
		sl.L2TP_IPsec = CfgGetBool(f, "L2TP_IPsec");
		sl.EtherIP_IPsec = CfgGetBool(f, "EtherIP_IPsec");
	}

	IPsecServerSetServices(s->IPsecServer, &sl);

	list_folder = CfgGetFolder(f, "EtherIP_IDSettingsList");

	if (list_folder != NULL)
	{
		TOKEN_LIST *t = CfgEnumFolderToTokenList(list_folder);
		if (t != NULL)
		{
			UINT i;

			for (i = 0;i < t->NumTokens;i++)
			{
				char *name = t->Token[i];
				FOLDER *f = CfgGetFolder(list_folder, name);

				if (f != NULL)
				{
					ETHERIP_ID d;
					BUF *b;

					Zero(&d, sizeof(d));

					StrCpy(d.Id, sizeof(d.Id), name);
					CfgGetStr(f, "HubName", d.HubName, sizeof(d.HubName));
					CfgGetStr(f, "UserName", d.UserName, sizeof(d.UserName));

					b = CfgGetBuf(f, "EncryptedPassword");
					if (b != NULL)
					{
						char *pass = DecryptPassword2(b);

						StrCpy(d.Password, sizeof(d.Password), pass);

						Free(pass);

						AddEtherIPId(s->IPsecServer, &d);

						FreeBuf(b);
					}
				}
			}

			FreeToken(t);
		}
	}
}