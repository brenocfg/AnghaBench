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

bool CtVLansDown(CLIENT *c)
{
#ifndef UNIX_LINUX
	return true;
#else
	int i;
	LIST *tmpVLanList;
	UNIX_VLAN t, *r;
	bool result = true;

	if (c == NULL)
	{
		return false;
	}

	tmpVLanList = CloneList(c->UnixVLanList);
	if (tmpVLanList == NULL)
	{
		return false;
	}

	// Remove from tmpVLanList all VLans corresponding to active sessions
	for (i = 0; i < LIST_NUM(c->AccountList); ++i)
	{
		ACCOUNT *a = LIST_DATA(c->AccountList, i);
		if (a->ClientSession == NULL)
		{
			continue;
		}

		Zero(&t, sizeof(t));
		StrCpy(t.Name, sizeof(t.Name), a->ClientOption->DeviceName);
		r = Search(tmpVLanList, &t);
		Delete(tmpVLanList, r);
	}

	// Set down every VLan in tmpVLanList
	for (i = 0; i < LIST_NUM(tmpVLanList) && result; ++i)
	{
		r = LIST_DATA(tmpVLanList, i);
		result = UnixVLanSetState(r->Name, false);
		// [MP:] Should we report *critical* error on failure?
	}

	ReleaseList(tmpVLanList);
	return result;
#endif
}