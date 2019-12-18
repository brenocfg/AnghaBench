#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_10__ {int /*<<< orphan*/  CaList; } ;
struct TYPE_9__ {TYPE_3__* Cedar; } ;
struct TYPE_8__ {size_t NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_2__ CLIENT ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 TYPE_1__* CfgEnumFolderToTokenList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiLoadCACert (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void CiLoadCAList(CLIENT *c, FOLDER *f)
{
	CEDAR *cedar;
	TOKEN_LIST *t;
	// Validate arguments
	if (c == NULL || f == NULL)
	{
		return;
	}

	t = CfgEnumFolderToTokenList(f);

	cedar = c->Cedar;

	LockList(cedar->CaList);
	{
		UINT i;
		for (i = 0;i < t->NumTokens;i++)
		{
			FOLDER *folder = CfgGetFolder(f, t->Token[i]);
			CiLoadCACert(c, folder);
		}
	}
	UnlockList(cedar->CaList);

	FreeToken(t);
}