#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ UNIX_VLAN ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  UnixVLanList; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiWriteVLan (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void CiWriteVLanList(CLIENT *c, FOLDER *f)
{
	// Validate arguments
	if (c == NULL || f == NULL)
	{
		return;
	}

	LockList(c->UnixVLanList);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(c->UnixVLanList);i++)
		{
			UNIX_VLAN *v = LIST_DATA(c->UnixVLanList, i);
			CiWriteVLan(c, CfgCreateFolder(f, v->Name), v);
		}
	}
	UnlockList(c->UnixVLanList);
}