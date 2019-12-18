#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int Online; int /*<<< orphan*/  lock; int /*<<< orphan*/  Option; int /*<<< orphan*/ * ClientAuth; int /*<<< orphan*/ * ClientOption; int /*<<< orphan*/  Cedar; int /*<<< orphan*/  Virtual; } ;
typedef  int /*<<< orphan*/  RPC_DUMMY ;
typedef  TYPE_1__ NAT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_ACCOUNT_NOT_PRESENT ; 
 int /*<<< orphan*/  ERR_ALREADY_ONLINE ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewVirtualHostEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  NiWriteConfig (TYPE_1__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

UINT NtOnline(NAT *n, RPC_DUMMY *t)
{
	UINT ret = ERR_NO_ERROR;

	Lock(n->lock);
	{
		if (n->Online)
		{
			// It is already online
			ret = ERR_ALREADY_ONLINE;
		}
		else
		{
			if (n->ClientOption == NULL || n->ClientAuth == NULL)
			{
				// Setting is not yet done
				ret = ERR_ACCOUNT_NOT_PRESENT;
			}
			else
			{
				// OK
				n->Online = true;

				// Start connection
				n->Virtual = NewVirtualHostEx(n->Cedar, n->ClientOption, n->ClientAuth,
					&n->Option, n);
			}
		}
	}
	Unlock(n->lock);

	NiWriteConfig(n);

	return ret;
}