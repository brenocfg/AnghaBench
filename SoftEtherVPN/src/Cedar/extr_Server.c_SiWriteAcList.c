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
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  SubnetMask; scalar_t__ Masked; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  Priority; int /*<<< orphan*/  Deny; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ AC ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,scalar_t__) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

void SiWriteAcList(FOLDER *f, LIST *o)
{
	// Validate arguments
	if (f == NULL || o == NULL)
	{
		return;
	}

	LockList(o);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(o);i++)
		{
			char name[MAX_SIZE];
			AC *ac = LIST_DATA(o, i);
			FOLDER *ff;

			Format(name, sizeof(name), "Acl%u", i + 1);

			ff = CfgCreateFolder(f, name);

			CfgAddBool(ff, "Deny", ac->Deny);
			CfgAddInt(ff, "Priority", ac->Priority);
			CfgAddIp(ff, "IpAddress", &ac->IpAddress);

			if (ac->Masked)
			{
				CfgAddIp(ff, "NetMask", &ac->SubnetMask);
			}
		}
	}
	UnlockList(o);
}