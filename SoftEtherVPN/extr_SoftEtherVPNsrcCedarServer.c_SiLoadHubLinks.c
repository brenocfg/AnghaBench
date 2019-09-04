#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_4__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  HUB ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 TYPE_1__* CfgEnumFolderToTokenList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  SiLoadHubLinkCfg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void SiLoadHubLinks(HUB *h, FOLDER *f)
{
	TOKEN_LIST *t;
	UINT i;
	// Validate arguments
	if (h == NULL || f == NULL)
	{
		return;
	}

	t = CfgEnumFolderToTokenList(f);

	for (i = 0;i < t->NumTokens;i++)
	{
		char *name = t->Token[i];
		SiLoadHubLinkCfg(CfgGetFolder(f, name), h);
	}

	FreeToken(t);
}