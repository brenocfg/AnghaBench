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
struct TYPE_4__ {void* SystemExpires; void* SystemId; int /*<<< orphan*/  Valid; } ;
typedef  TYPE_1__ RPC_EL_LICENSE_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetBool (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcElLicenseStatus(RPC_EL_LICENSE_STATUS *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_EL_LICENSE_STATUS));

	t->Valid = PackGetBool(p, "Valid");
	t->SystemId = PackGetInt64(p, "SystemId");
	t->SystemExpires = PackGetInt64(p, "SystemExpires");
}