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
struct TYPE_3__ {int /*<<< orphan*/  SockList; } ;
typedef  TYPE_1__ SOCKLIST ;
typedef  int /*<<< orphan*/  SOCK ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void StopSockList(SOCKLIST *sl)
{
	SOCK **ss;
	UINT num, i;
	// Validate arguments
	if (sl == NULL)
	{
		return;
	}

	LockList(sl->SockList);
	{
		num = LIST_NUM(sl->SockList);
		ss = ToArray(sl->SockList);

		DeleteAll(sl->SockList);
	}
	UnlockList(sl->SockList);

	for (i = 0;i < num;i++)
	{
		SOCK *s = ss[i];

		Disconnect(s);
		ReleaseSock(s);
	}

	Free(ss);
}