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
struct TYPE_4__ {int IsPasswordPresented; int PasswordRemoteOnly; } ;
typedef  TYPE_1__ RPC_CLIENT_PASSWORD_SETTING ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 scalar_t__ PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcClientPasswordSetting(RPC_CLIENT_PASSWORD_SETTING *a, PACK *p)
{
	// Validate arguments
	if (a == NULL || p == NULL)
	{
		return;
	}

	Zero(a, sizeof(RPC_CLIENT_PASSWORD_SETTING));

	a->IsPasswordPresented = PackGetInt(p, "IsPasswordPresented") == 0 ? false : true;
	a->PasswordRemoteOnly = PackGetInt(p, "PasswordRemoteOnly") == 0 ? false : true;
}