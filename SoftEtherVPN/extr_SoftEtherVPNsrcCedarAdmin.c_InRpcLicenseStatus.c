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
struct TYPE_4__ {void* ReleaseDate; void* NumUserCreationLicense; void* IsSubscriptionExpired; void* SubscriptionExpires; void* AllowEnterpriseFunction; void* NeedSubscription; void* NumBridgeConnectLicense; void* NumClientConnectLicense; void* SystemExpires; void* SystemId; int /*<<< orphan*/  EditionStr; void* EditionId; } ;
typedef  TYPE_1__ RPC_LICENSE_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcLicenseStatus(RPC_LICENSE_STATUS *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_LICENSE_STATUS));

	t->EditionId = PackGetInt(p, "EditionId");
	PackGetStr(p, "EditionStr", t->EditionStr, sizeof(t->EditionStr) );
	t->SystemId = PackGetInt64(p, "SystemId");
	t->SystemExpires = PackGetInt64(p, "SystemExpires");
	t->NumClientConnectLicense = PackGetInt(p, "NumClientConnectLicense");
	t->NumBridgeConnectLicense = PackGetInt(p, "NumBridgeConnectLicense");

	// v3.0
	t->NeedSubscription = PackGetBool(p, "NeedSubscription");
	t->AllowEnterpriseFunction = PackGetBool(p, "AllowEnterpriseFunction");
	t->SubscriptionExpires = PackGetInt64(p, "SubscriptionExpires");
	t->IsSubscriptionExpired = PackGetBool(p, "IsSubscriptionExpired");
	t->NumUserCreationLicense = PackGetInt(p, "NumUserCreationLicense");
	t->ReleaseDate = PackGetInt64(p, "ReleaseDate");
}