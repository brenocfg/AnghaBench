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
struct TYPE_3__ {int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  ClientOption; } ;
typedef  TYPE_1__ NAT ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CiLoadClientAuth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiLoadClientOption (int /*<<< orphan*/ *) ; 

void NiLoadClientData(NAT *n, FOLDER *root)
{
	FOLDER *co, *ca;
	// Validate arguments
	if (n == NULL || root == NULL)
	{
		return;
	}

	co = CfgGetFolder(root, "VpnClientOption");
	ca = CfgGetFolder(root, "VpnClientAuth");
	if (co == NULL || ca == NULL)
	{
		return;
	}

	n->ClientOption = CiLoadClientOption(co);
	n->ClientAuth = CiLoadClientAuth(ca);
}