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
struct TYPE_3__ {int /*<<< orphan*/  HubType; int /*<<< orphan*/  HubOption; int /*<<< orphan*/  AdminPasswordPlainText; int /*<<< orphan*/  Online; int /*<<< orphan*/  SecurePassword; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_CREATE_HUB ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  OutRpcHubOption (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcCreateHub(PACK *p, RPC_CREATE_HUB *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "HubName", t->HubName);
	PackAddData(p, "HashedPassword", t->HashedPassword, sizeof(t->HashedPassword));
	PackAddData(p, "SecurePassword", t->SecurePassword, sizeof(t->SecurePassword));
	PackAddBool(p, "Online", t->Online);
	PackAddStr(p, "AdminPasswordPlainText", t->AdminPasswordPlainText);
	OutRpcHubOption(p, &t->HubOption);
	PackAddInt(p, "HubType", t->HubType);
}