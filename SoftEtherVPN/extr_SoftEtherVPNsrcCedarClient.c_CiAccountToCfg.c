#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  a ;
struct TYPE_7__ {int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  ClientOption; } ;
struct TYPE_6__ {int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  ClientOption; } ;
typedef  TYPE_1__ RPC_CLIENT_CREATE_ACCOUNT ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;
typedef  TYPE_2__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgDeleteFolder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CfgFolderToBufEx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  CiWriteAccountData (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  TAG_ROOT ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

BUF *CiAccountToCfg(RPC_CLIENT_CREATE_ACCOUNT *t)
{
	BUF *b;
	FOLDER *root;
	ACCOUNT a;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	root = CfgCreateFolder(NULL, TAG_ROOT);
	Zero(&a, sizeof(a));
	a.ClientOption = t->ClientOption;
	a.ClientAuth = t->ClientAuth;
	a.CheckServerCert = t->CheckServerCert;
	a.RetryOnServerCert = t->RetryOnServerCert;
	a.ServerCert = t->ServerCert;
	a.StartupAccount = t->StartupAccount;

	CiWriteAccountData(root, &a);

	b = CfgFolderToBufEx(root, true, true);
	CfgDeleteFolder(root);

	return b;
}