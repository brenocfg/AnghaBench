#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */

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