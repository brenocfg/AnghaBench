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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  SaveCfgLock; int /*<<< orphan*/  ConfigRevision; scalar_t__ BackupConfigOnlyWhenModified; int /*<<< orphan*/ * CfgRw; scalar_t__ NoMoreSave; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgDeleteFolder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SaveCfgRwEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SiWriteConfigurationToCfg (TYPE_1__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

UINT SiWriteConfigurationFile(SERVER *s)
{
	UINT ret;
	// Validate arguments
	if (s == NULL)
	{
		return 0;
	}

	if (s->CfgRw == NULL)
	{
		return 0;
	}

	if (s->NoMoreSave)
	{
		return 0;
	}

	Lock(s->SaveCfgLock);
	{
		FOLDER *f;

		Debug("save: SiWriteConfigurationToCfg() start.\n");
		f = SiWriteConfigurationToCfg(s);
		Debug("save: SiWriteConfigurationToCfg() finished.\n");

		Debug("save: SaveCfgRw() start.\n");
		ret = SaveCfgRwEx(s->CfgRw, f, s->BackupConfigOnlyWhenModified ? s->ConfigRevision : INFINITE);
		Debug("save: SaveCfgRw() finished.\n");

		Debug("save: CfgDeleteFolder() start.\n");
		CfgDeleteFolder(f);
		Debug("save: CfgDeleteFolder() finished.\n");
	}
	Unlock(s->SaveCfgLock);

	return ret;
}