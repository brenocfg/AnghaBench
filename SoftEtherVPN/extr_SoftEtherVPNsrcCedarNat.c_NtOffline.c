#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int Online; int /*<<< orphan*/  lock; int /*<<< orphan*/ * Virtual; } ;
typedef  int /*<<< orphan*/  RPC_DUMMY ;
typedef  TYPE_1__ NAT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ERR_OFFLINE ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NiWriteConfig (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseVirtual (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopVirtualHost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

UINT NtOffline(NAT *n, RPC_DUMMY *t)
{
	UINT ret = ERR_NO_ERROR;

	Lock(n->lock);
	{
		if (n->Online == false)
		{
			// It is offline
			ret = ERR_OFFLINE;
		}
		else
		{
			// Offline
			StopVirtualHost(n->Virtual);
			ReleaseVirtual(n->Virtual);
			n->Virtual = NULL;

			n->Online = false;
		}
	}
	Unlock(n->lock);

	NiWriteConfig(n);

	return ret;
}