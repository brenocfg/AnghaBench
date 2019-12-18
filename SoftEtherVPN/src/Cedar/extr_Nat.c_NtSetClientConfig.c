#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {scalar_t__ Online; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ClientAuth; int /*<<< orphan*/ * ClientOption; } ;
struct TYPE_8__ {int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  ClientOption; } ;
typedef  TYPE_1__ RPC_CREATE_LINK ;
typedef  TYPE_2__ NAT ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  CiFreeClientAuth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CopyClientAuth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NiWriteConfig (TYPE_2__*) ; 
 int /*<<< orphan*/  NtOffline (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtOnline (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

UINT NtSetClientConfig(NAT *n, RPC_CREATE_LINK *t)
{
	Lock(n->lock);
	{
		if (n->ClientOption != NULL || n->ClientAuth != NULL)
		{
			Free(n->ClientOption);
			CiFreeClientAuth(n->ClientAuth);
		}

		n->ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
		Copy(n->ClientOption, t->ClientOption, sizeof(CLIENT_OPTION));
		n->ClientAuth = CopyClientAuth(t->ClientAuth);
	}
	Unlock(n->lock);

	NiWriteConfig(n);

	if (n->Online)
	{
		NtOffline(n, NULL);
		NtOnline(n, NULL);
	}

	return ERR_NO_ERROR;
}