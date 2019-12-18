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
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  CfgRw; int /*<<< orphan*/ * ClientAuth; int /*<<< orphan*/ * ClientOption; int /*<<< orphan*/  Online; int /*<<< orphan*/  AdminPort; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  AdminK; int /*<<< orphan*/  AdminX; } ;
typedef  TYPE_1__ NAT ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgAddByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgDeleteFolder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * KToBuf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NiWriteClientData (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NiWriteVhOption (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SaveCfgRw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAG_ROOT ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XToBuf (int /*<<< orphan*/ ,int) ; 

void NiWriteConfig(NAT *n)
{
	// Validate arguments
	if (n == NULL)
	{
		return;
	}

	Lock(n->lock);
	{
		FOLDER *root = CfgCreateFolder(NULL, TAG_ROOT);
		BUF *b;

		// Certificate
		b = XToBuf(n->AdminX, false);
		CfgAddBuf(root, "AdminCert", b);
		FreeBuf(b);

		// Secret key
		b = KToBuf(n->AdminK, false, NULL);
		CfgAddBuf(root, "AdminKey", b);
		FreeBuf(b);

		// Password
		CfgAddByte(root, "HashedPassword", n->HashedPassword, sizeof(n->HashedPassword));
		CfgAddInt(root, "AdminPort", n->AdminPort);
		CfgAddBool(root, "Online", n->Online);

		// Virtual host option
		NiWriteVhOption(n, root);

		// Connection options
		if (n->ClientOption != NULL && n->ClientAuth != NULL)
		{
			NiWriteClientData(n, root);
		}

		SaveCfgRw(n->CfgRw, root);
		CfgDeleteFolder(root);
	}
	Unlock(n->lock);
}