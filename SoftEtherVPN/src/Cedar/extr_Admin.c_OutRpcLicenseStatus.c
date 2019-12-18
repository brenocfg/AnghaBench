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
struct TYPE_3__ {int /*<<< orphan*/  ReleaseDate; int /*<<< orphan*/  NumUserCreationLicense; int /*<<< orphan*/  IsSubscriptionExpired; int /*<<< orphan*/  SubscriptionExpires; int /*<<< orphan*/  AllowEnterpriseFunction; int /*<<< orphan*/  NeedSubscription; int /*<<< orphan*/  NumBridgeConnectLicense; int /*<<< orphan*/  NumClientConnectLicense; int /*<<< orphan*/  SystemExpires; int /*<<< orphan*/  SystemId; int /*<<< orphan*/  EditionStr; int /*<<< orphan*/  EditionId; } ;
typedef  TYPE_1__ RPC_LICENSE_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddTime64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcLicenseStatus(PACK *p, RPC_LICENSE_STATUS *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "EditionId", t->EditionId);
	PackAddStr(p, "EditionStr", t->EditionStr);
	PackAddInt64(p, "SystemId", t->SystemId);
	PackAddTime64(p, "SystemExpires", t->SystemExpires);
	PackAddInt(p, "NumClientConnectLicense", t->NumClientConnectLicense);
	PackAddInt(p, "NumBridgeConnectLicense", t->NumBridgeConnectLicense);

	// v3.0
	PackAddBool(p, "NeedSubscription", t->NeedSubscription);
	PackAddBool(p, "AllowEnterpriseFunction", t->AllowEnterpriseFunction);
	PackAddTime64(p, "SubscriptionExpires", t->SubscriptionExpires);
	PackAddBool(p, "IsSubscriptionExpired", t->IsSubscriptionExpired);
	PackAddInt(p, "NumUserCreationLicense", t->NumUserCreationLicense);
	PackAddTime64(p, "ReleaseDate", t->ReleaseDate);
}