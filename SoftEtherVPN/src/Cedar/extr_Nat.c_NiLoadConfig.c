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
struct TYPE_5__ {int /*<<< orphan*/  AdminK; int /*<<< orphan*/  AdminX; int /*<<< orphan*/  Online; int /*<<< orphan*/  AdminPort; int /*<<< orphan*/  HashedPassword; } ;
typedef  TYPE_1__ NAT ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  BufToK (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BufToX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NiLoadClientData (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NiLoadVhOption (TYPE_1__*,int /*<<< orphan*/ *) ; 

bool NiLoadConfig(NAT *n, FOLDER *root)
{
	FOLDER *host;
	BUF *b;
	// Validate arguments
	if (n == NULL || root == NULL)
	{
		return false;
	}

	host = CfgGetFolder(root, "VirtualHost");
	if (host == NULL)
	{
		return false;
	}

	CfgGetByte(root, "HashedPassword", n->HashedPassword, sizeof(n->HashedPassword));
	n->AdminPort = CfgGetInt(root, "AdminPort");
	n->Online = CfgGetBool(root, "Online");

	b = CfgGetBuf(root, "AdminCert");
	if (b != NULL)
	{
		n->AdminX = BufToX(b, false);
		FreeBuf(b);
	}

	b = CfgGetBuf(root, "AdminKey");
	if (b != NULL)
	{
		n->AdminK = BufToK(b, true, false, NULL);
		FreeBuf(b);
	}

	NiLoadVhOption(n, root);

	NiLoadClientData(n, root);

	return true;
}