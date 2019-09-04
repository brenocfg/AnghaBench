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
struct TYPE_3__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  Ip; } ;
typedef  TYPE_1__ QUERYIPTHREAD ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool GetQueryIpThreadResult(QUERYIPTHREAD *t, IP *ip)
{
	bool ret = false;
	Zero(ip, sizeof(IP));
	// Validate arguments
	if (t == NULL || ip == NULL)
	{
		return false;
	}

	Lock(t->Lock);

	if (IsZero(&t->Ip, sizeof(IP)))
	{
		ret = false;
	}
	else
	{
		Copy(ip, &t->Ip, sizeof(IP));
	}

	Unlock(t->Lock);

	return ret;
}