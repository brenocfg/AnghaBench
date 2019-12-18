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
typedef  size_t UINT ;
struct TYPE_8__ {int /*<<< orphan*/  UnixVLanList; } ;
struct TYPE_7__ {size_t NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 TYPE_1__* CfgEnumFolderToTokenList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiLoadVLan (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void CiLoadVLanList(CLIENT *c, FOLDER *f)
{
	TOKEN_LIST *t;
	// Validate arguments
	if (c == NULL || f == NULL)
	{
		return;
	}

	t = CfgEnumFolderToTokenList(f);

	LockList(c->UnixVLanList);
	{
		UINT i;
		for (i = 0;i < t->NumTokens;i++)
		{
			FOLDER *folder = CfgGetFolder(f, t->Token[i]);
			CiLoadVLan(c, folder);
		}
	}
	UnlockList(c->UnixVLanList);

	FreeToken(t);
}