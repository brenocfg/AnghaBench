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
typedef  size_t UINT ;
struct TYPE_13__ {size_t Value; int /*<<< orphan*/  Name; } ;
struct TYPE_12__ {int /*<<< orphan*/  AdminOptionList; } ;
struct TYPE_11__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ HUB ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_3__ ADMIN_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  AddHubAdminOptionsDefaults (TYPE_2__*,int) ; 
 TYPE_1__* CfgEnumItemToTokenList (int /*<<< orphan*/ *) ; 
 size_t CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  DeleteAllHubAdminOption (TYPE_2__*,int) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_3__* ZeroMalloc (int) ; 

void SiLoadHubAdminOptions(HUB *h, FOLDER *f)
{
	TOKEN_LIST *t;
	// Validate arguments
	if (h == NULL || f == NULL)
	{
		return;
	}

	t = CfgEnumItemToTokenList(f);
	if (t != NULL)
	{
		UINT i;

		LockList(h->AdminOptionList);
		{
			DeleteAllHubAdminOption(h, false);

			for (i = 0;i < t->NumTokens;i++)
			{
				char *name = t->Token[i];
				ADMIN_OPTION *a;
				UINT value = CfgGetInt(f, name);;

				Trim(name);

				a = ZeroMalloc(sizeof(ADMIN_OPTION));
				StrCpy(a->Name, sizeof(a->Name), name);
				a->Value = value;

				Insert(h->AdminOptionList, a);
			}

			AddHubAdminOptionsDefaults(h, false);
		}
		UnlockList(h->AdminOptionList);

		FreeToken(t);
	}
}