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
struct TYPE_3__ {int /*<<< orphan*/  DeviceId; } ;
typedef  TYPE_1__ RPC_USE_SECURE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcUseSecure(PACK *p, RPC_USE_SECURE *u)
{
	// Validate arguments
	if (u == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "DeviceId", u->DeviceId);
}