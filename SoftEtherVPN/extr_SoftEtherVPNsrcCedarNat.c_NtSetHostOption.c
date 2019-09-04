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
typedef  int /*<<< orphan*/  VH_OPTION ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Virtual; int /*<<< orphan*/  lock; int /*<<< orphan*/  Option; } ;
typedef  TYPE_1__ NAT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NiWriteConfig (TYPE_1__*) ; 
 int /*<<< orphan*/  SetVirtualHostOption (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

UINT NtSetHostOption(NAT *n, VH_OPTION *t)
{
	UINT ret = ERR_NO_ERROR;

	Lock(n->lock);
	{
		Copy(&n->Option, t, sizeof(VH_OPTION));
	}
	Unlock(n->lock);

	SetVirtualHostOption(n->Virtual, t);

	NiWriteConfig(n);

	return ret;
}