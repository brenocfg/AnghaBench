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
struct TYPE_4__ {int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ RPC_CLIENT_CONNECT ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcClientConnect(RPC_CLIENT_CONNECT *c, PACK *p)
{
	// Validate arguments
	if (c == NULL || p == NULL)
	{
		return;
	}

	Zero(c, sizeof(RPC_CLIENT_CONNECT));

	PackGetUniStr(p, "AccountName", c->AccountName, sizeof(c->AccountName));
}