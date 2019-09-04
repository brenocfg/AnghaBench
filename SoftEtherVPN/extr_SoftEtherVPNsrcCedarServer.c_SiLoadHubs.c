#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_11__ {TYPE_1__* Cedar; } ;
struct TYPE_10__ {size_t NumTokens; char** Token; } ;
struct TYPE_9__ {scalar_t__ Bridge; } ;
typedef  TYPE_2__ TOKEN_LIST ;
typedef  TYPE_3__ SERVER ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 TYPE_2__* CfgEnumFolderToTokenList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_2__*) ; 
 int /*<<< orphan*/  SERVER_DEFAULT_BRIDGE_NAME ; 
 int /*<<< orphan*/  SiInitDefaultHubList (TYPE_3__*) ; 
 int /*<<< orphan*/  SiLoadHubCfg (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ StrCmpi (char*,int /*<<< orphan*/ ) ; 

void SiLoadHubs(SERVER *s, FOLDER *f)
{
	UINT i;
	FOLDER *hub_folder;
	TOKEN_LIST *t;
	bool b = false;
	// Validate arguments
	if (f == NULL || s == NULL)
	{
		return;
	}

	t = CfgEnumFolderToTokenList(f);
	for (i = 0;i < t->NumTokens;i++)
	{
		char *name = t->Token[i];


		if (s->Cedar->Bridge)
		{
			if (StrCmpi(name, SERVER_DEFAULT_BRIDGE_NAME) == 0)
			{
				// Read only the setting of Virtual HUB named "BRIDGE"
				// in the case of the Bridge
				b = true;
			}
			else
			{
				continue;
			}
		}
		hub_folder = CfgGetFolder(f, name);
		if (hub_folder != NULL)
		{
			SiLoadHubCfg(s, hub_folder, name);
		}
	}
	FreeToken(t);

	if (s->Cedar->Bridge && b == false)
	{
		// If there isn't "BRIDGE" virtual HUB setting, create it newly
		SiInitDefaultHubList(s);
	}
}