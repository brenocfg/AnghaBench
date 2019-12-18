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
struct TYPE_4__ {int /*<<< orphan*/  CfgRw; scalar_t__ NoSaveConfig; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgDeleteFolder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiWriteSettingToCfg (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SaveCfgRw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAG_ROOT ; 

void CiSaveConfigurationFile(CLIENT *c)
{
	FOLDER *root;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}
	
	// Do not save the configuration file
	if(c->NoSaveConfig)
	{
		return;
	}

	root = CfgCreateFolder(NULL, TAG_ROOT);
	CiWriteSettingToCfg(c, root);

	SaveCfgRw(c->CfgRw, root);

	CfgDeleteFolder(root);
}