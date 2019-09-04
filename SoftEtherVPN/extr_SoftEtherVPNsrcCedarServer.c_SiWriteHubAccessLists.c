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
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  Id; } ;
struct TYPE_6__ {int /*<<< orphan*/  AccessList; } ;
typedef  TYPE_1__ HUB ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_2__ ACCESS ;

/* Variables and functions */
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  SiWriteHubAccessCfg (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ToStr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void SiWriteHubAccessLists(FOLDER *f, HUB *h)
{
	// Validate arguments
	if (f == NULL || h == NULL)
	{
		return;
	}

	LockList(h->AccessList);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(h->AccessList);i++)
		{
			ACCESS *a = LIST_DATA(h->AccessList, i);
			char name[MAX_SIZE];
			ToStr(name, a->Id);
			SiWriteHubAccessCfg(CfgCreateFolder(f, name), a);
		}
	}
	UnlockList(h->AccessList);
}