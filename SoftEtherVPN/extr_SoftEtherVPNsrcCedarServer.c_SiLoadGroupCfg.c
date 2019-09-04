#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  realname ;
typedef  int /*<<< orphan*/  note ;
typedef  int /*<<< orphan*/  USERGROUP ;
struct TYPE_8__ {char* Name; } ;
typedef  int /*<<< orphan*/  TRAFFIC ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  int /*<<< orphan*/  HUB ;
typedef  TYPE_1__ FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  AcAddGroup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcUnlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* CfgGetFolder (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  CfgGetUniStr (TYPE_1__*,char*,int /*<<< orphan*/ *,int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewGroup (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseGroup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetGroupPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetGroupTraffic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadPolicyCfg (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SiLoadTraffic (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 

void SiLoadGroupCfg(HUB *h, FOLDER *f)
{
	wchar_t realname[MAX_SIZE];
	wchar_t note[MAX_SIZE];
	char *name;
	FOLDER *pf;
	POLICY p;
	TRAFFIC t;
	USERGROUP *g;
	// Validate arguments
	if (h == NULL || f == NULL)
	{
		return;
	}

	name = f->Name;

	CfgGetUniStr(f, "RealName", realname, sizeof(realname));
	CfgGetUniStr(f, "Note", note, sizeof(note));

	pf = CfgGetFolder(f, "Policy");
	if (pf != NULL)
	{
		SiLoadPolicyCfg(&p, pf);
	}

	SiLoadTraffic(f, "Traffic", &t);

	g = NewGroup(name, realname, note);
	if (g == NULL)
	{
		return;
	}

	if (pf != NULL)
	{
		SetGroupPolicy(g, &p);
	}

	SetGroupTraffic(g, &t);

	AcLock(h);
	{
		AcAddGroup(h, g);
	}
	AcUnlock(h);

	ReleaseGroup(g);
}