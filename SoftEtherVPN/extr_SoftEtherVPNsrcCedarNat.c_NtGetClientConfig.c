#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ClientAuth; int /*<<< orphan*/ * ClientOption; } ;
struct TYPE_7__ {int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  ClientOption; } ;
typedef  TYPE_1__ RPC_CREATE_LINK ;
typedef  TYPE_2__ NAT ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CopyClientAuth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_ACCOUNT_NOT_PRESENT ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcCreateLink (TYPE_1__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ZeroMalloc (int) ; 

UINT NtGetClientConfig(NAT *n, RPC_CREATE_LINK *t)
{
	UINT err = ERR_NO_ERROR;

	Lock(n->lock);
	{
		if (n->ClientOption == NULL || n->ClientAuth == NULL)
		{
			err = ERR_ACCOUNT_NOT_PRESENT;
		}
		else
		{
			FreeRpcCreateLink(t);

			Zero(t, sizeof(RPC_CREATE_LINK));
			t->ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
			Copy(t->ClientOption, n->ClientOption, sizeof(CLIENT_OPTION));
			t->ClientAuth = CopyClientAuth(n->ClientAuth);
		}
	}
	Unlock(n->lock);

	return err;
}