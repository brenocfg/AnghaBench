#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ac ;
typedef  size_t UINT ;
struct TYPE_8__ {int Masked; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  Priority; int /*<<< orphan*/  Deny; } ;
struct TYPE_7__ {size_t NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_2__ AC ;

/* Variables and functions */
 int /*<<< orphan*/  AddAc (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* CfgEnumFolderToTokenList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ CfgGetIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

void SiLoadAcList(LIST *o, FOLDER *f)
{
	// Validate arguments
	if (o == NULL || f == NULL)
	{
		return;
	}

	LockList(o);
	{
		TOKEN_LIST *t = CfgEnumFolderToTokenList(f);

		if (t != NULL)
		{
			UINT i;

			for (i = 0;i < t->NumTokens;i++)
			{
				FOLDER *ff = CfgGetFolder(f, t->Token[i]);

				if (ff != NULL)
				{
					AC ac;

					Zero(&ac, sizeof(ac));
					ac.Deny = CfgGetBool(ff, "Deny");
					ac.Priority = CfgGetInt(ff, "Priority");
					CfgGetIp(ff, "IpAddress", &ac.IpAddress);

					if (CfgGetIp(ff, "NetMask", &ac.SubnetMask))
					{
						ac.Masked = true;
					}

					AddAc(o, &ac);
				}
			}

			FreeToken(t);
		}
	}
	UnlockList(o);
}