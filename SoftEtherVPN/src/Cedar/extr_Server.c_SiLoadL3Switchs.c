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
struct TYPE_7__ {int /*<<< orphan*/ * Cedar; } ;
struct TYPE_6__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ SERVER ;
typedef  int /*<<< orphan*/  L3SW ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 TYPE_1__* CfgEnumFolderToTokenList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/ * L3AddSw (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ReleaseL3Sw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadL3SwitchCfg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SiLoadL3Switchs(SERVER *s, FOLDER *f)
{
	UINT i;
	TOKEN_LIST *t;
	CEDAR *c;
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return;
	}
	c = s->Cedar;

	t = CfgEnumFolderToTokenList(f);
	if (t != NULL)
	{
		for (i = 0;i < t->NumTokens;i++)
		{
			char *name = t->Token[i];
			L3SW *sw = L3AddSw(c, name);

			SiLoadL3SwitchCfg(sw, CfgGetFolder(f, name));

			ReleaseL3Sw(sw);
		}
	}
	FreeToken(t);
}