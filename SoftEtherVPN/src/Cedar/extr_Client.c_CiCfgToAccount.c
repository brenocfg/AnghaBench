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
struct TYPE_8__ {int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  ClientOption; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  ClientOption; } ;
typedef  TYPE_1__ RPC_CLIENT_CREATE_ACCOUNT ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;
typedef  TYPE_2__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgBufTextToFolder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgDeleteFolder (int /*<<< orphan*/ *) ; 
 TYPE_2__* CiLoadClientAccount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

RPC_CLIENT_CREATE_ACCOUNT *CiCfgToAccount(BUF *b)
{
	RPC_CLIENT_CREATE_ACCOUNT *t;
	FOLDER *f;
	ACCOUNT *a;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	f = CfgBufTextToFolder(b);
	if (f == NULL)
	{
		return NULL;
	}

	a = CiLoadClientAccount(f);

	CfgDeleteFolder(f);

	if (a == NULL)
	{
		return NULL;
	}

	DeleteLock(a->lock);

	t = ZeroMalloc(sizeof(RPC_CLIENT_CREATE_ACCOUNT));
	t->ClientOption = a->ClientOption;
	t->ClientAuth = a->ClientAuth;
	t->StartupAccount = a->StartupAccount;
	t->CheckServerCert = a->CheckServerCert;
	t->RetryOnServerCert = a->RetryOnServerCert;
	t->ServerCert = a->ServerCert;
	Free(a);

	return t;
}