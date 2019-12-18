#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  Traffic; int /*<<< orphan*/ * Policy; int /*<<< orphan*/  Note; int /*<<< orphan*/  RealName; } ;
typedef  TYPE_1__ USERGROUP ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiWritePolicyCfg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SiWriteTraffic (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void SiWriteGroupCfg(FOLDER *f, USERGROUP *g)
{
	// Validate arguments
	if (f == NULL || g == NULL)
	{
		return;
	}

	Lock(g->lock);
	{
		CfgAddUniStr(f, "RealName", g->RealName);
		CfgAddUniStr(f, "Note", g->Note);
		if (g->Policy != NULL)
		{
			SiWritePolicyCfg(CfgCreateFolder(f, "Policy"), g->Policy, false);
		}
		SiWriteTraffic(f, "Traffic", g->Traffic);
	}
	Unlock(g->lock);
}