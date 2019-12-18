#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ UNIX_VLAN ;
struct TYPE_6__ {int /*<<< orphan*/  UnixVLanList; } ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnixVLanSetState (int /*<<< orphan*/ ,int) ; 

bool CtVLansUp(CLIENT *c)
{
#ifndef UNIX_LINUX
	return true;
#else
	int i;
	UNIX_VLAN *r;

	if (c == NULL)
	{
		return false;
	}

	for (i = 0; i < LIST_NUM(c->UnixVLanList); ++i)
	{
		r = LIST_DATA(c->UnixVLanList, i);
		UnixVLanSetState(r->Name, true);
	}

	return true;
#endif
}