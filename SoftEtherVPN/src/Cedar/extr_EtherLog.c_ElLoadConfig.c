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
struct TYPE_4__ {int /*<<< orphan*/  AutoDeleteCheckDiskFreeSpaceMin; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  CfgRw; int /*<<< orphan*/  Port; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  CfgDeleteFolder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DISK_FREE_SPACE_DEFAULT ; 
 int /*<<< orphan*/  EL_ADMIN_PORT ; 
 int /*<<< orphan*/  EL_CONFIG_FILENAME ; 
 int /*<<< orphan*/  ElLoadConfigFromFolder (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewCfgRw (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 

bool ElLoadConfig(EL *e)
{
	FOLDER *root;
	bool ret = false;
	// Validate arguments
	if (e == NULL)
	{
		return false;
	}

	e->Port = EL_ADMIN_PORT;

	e->CfgRw = NewCfgRw(&root, EL_CONFIG_FILENAME);

	if (root != NULL)
	{
		ElLoadConfigFromFolder(e, root);

		CfgDeleteFolder(root);
	}
	else
	{
		char *pass = "";
		Sha0(e->HashedPassword, pass, StrLen(pass));
		e->AutoDeleteCheckDiskFreeSpaceMin = DISK_FREE_SPACE_DEFAULT;
	}

	return ret;
}