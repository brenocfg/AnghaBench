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
struct TYPE_4__ {int /*<<< orphan*/  HubType; int /*<<< orphan*/  HubOption; int /*<<< orphan*/  Online; int /*<<< orphan*/  AdminPasswordPlainText; int /*<<< orphan*/  SecurePassword; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_CREATE_HUB ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  InRpcHubOption (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetData2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcCreateHub(RPC_CREATE_HUB *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_CREATE_HUB));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	PackGetData2(p, "HashedPassword", t->HashedPassword, sizeof(t->HashedPassword));
	PackGetData2(p, "SecurePassword", t->SecurePassword, sizeof(t->SecurePassword));
	PackGetStr(p, "AdminPasswordPlainText", t->AdminPasswordPlainText, sizeof(t->AdminPasswordPlainText));
	t->Online = PackGetBool(p, "Online");
	InRpcHubOption(&t->HubOption, p);
	t->HubType = PackGetInt(p, "HubType");
}