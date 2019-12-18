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
typedef  size_t UINT ;
struct TYPE_3__ {int /*<<< orphan*/  SessionList; } ;
typedef  int /*<<< orphan*/  SESSION ;
typedef  TYPE_1__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSession (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopSession (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void StopAllSession(HUB *h)
{
	SESSION **s;
	UINT i, num;
	// Validate arguments
	if (h == NULL)
	{
		return;
	}

	LockList(h->SessionList);
	{
		num = LIST_NUM(h->SessionList);
		s = ToArray(h->SessionList);
		DeleteAll(h->SessionList);
	}
	UnlockList(h->SessionList);

	for (i = 0;i < num;i++)
	{
		StopSession(s[i]);
		ReleaseSession(s[i]);
	}

	Free(s);
}