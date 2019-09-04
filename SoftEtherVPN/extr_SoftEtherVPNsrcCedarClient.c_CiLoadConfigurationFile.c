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
typedef  int /*<<< orphan*/  path ;
struct TYPE_4__ {void* CfgRw; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 char* CLIENT_CONFIG_FILE_NAME ; 
 int /*<<< orphan*/  CfgDeleteFolder (int /*<<< orphan*/ *) ; 
 scalar_t__ CiLoadConfigFilePathFromIni (char*,int) ; 
 int CiReadSettingFromCfg (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 void* NewCfgRw (int /*<<< orphan*/ **,char*) ; 

bool CiLoadConfigurationFile(CLIENT *c)
{
	bool ret;
	FOLDER *root;
	char path[MAX_SIZE];
	// Validate arguments
	if (c == NULL)
	{
		return false;
	}

	// Read the configuration file
	if (CiLoadConfigFilePathFromIni(path, sizeof(path)))
	{
		c->CfgRw = NewCfgRw(&root, path);
	}
	else
	{
		c->CfgRw = NewCfgRw(&root, CLIENT_CONFIG_FILE_NAME);
	}

	if (root == NULL)
	{
		return false;
	}

	ret = CiReadSettingFromCfg(c, root);

	CfgDeleteFolder(root);

	return ret;
}