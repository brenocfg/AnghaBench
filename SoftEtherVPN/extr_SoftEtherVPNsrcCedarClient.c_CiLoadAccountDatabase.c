#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_7__ {int /*<<< orphan*/  AccountList; } ;
struct TYPE_6__ {size_t NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_2__ CLIENT ;
typedef  int /*<<< orphan*/  ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* CfgEnumFolderToTokenList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CiLoadClientAccount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  Sort (int /*<<< orphan*/ ) ; 

void CiLoadAccountDatabase(CLIENT *c, FOLDER *f)
{
	TOKEN_LIST *t;
	UINT i;
	// Validate arguments
	if (c == NULL || f == NULL)
	{
		return;
	}

	t = CfgEnumFolderToTokenList(f);
	if (t == NULL)
	{
		return;
	}

	for (i = 0;i < t->NumTokens;i++)
	{
		FOLDER *ff = CfgGetFolder(f, t->Token[i]);

		if (ff != NULL)
		{
			ACCOUNT *a = CiLoadClientAccount(ff);
			if (a != NULL)
			{
				{
					Add(c->AccountList, a);
				}
			}
		}
	}

	Sort(c->AccountList);

	FreeToken(t);
}