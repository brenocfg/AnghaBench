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
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * UniCopyStr (int /*<<< orphan*/ *) ; 
 int UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void SetHubMsg(HUB *h, wchar_t *msg)
{
	// Validate arguments
	if (h == NULL)
	{
		return;
	}

	Lock(h->lock);
	{
		if (h->Msg != NULL)
		{
			Free(h->Msg);
			h->Msg = NULL;
		}

		if (UniIsEmptyStr(msg) == false)
		{
			h->Msg = UniCopyStr(msg);
		}
	}
	Unlock(h->lock);
}