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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * Msg; } ;
typedef  TYPE_1__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/ * CopyUniStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

wchar_t *GetHubMsg(HUB *h)
{
	wchar_t *ret = NULL;
	// Validate arguments
	if (h == NULL)
	{
		return NULL;
	}

	Lock(h->lock);
	{
		if (h->Msg != NULL)
		{
			ret = CopyUniStr(h->Msg);
		}
	}
	Unlock(h->lock);

	return ret;
}