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
struct TYPE_4__ {void* BitmapId; void* UseSecureDeviceId; int /*<<< orphan*/  Signature; int /*<<< orphan*/  Random; int /*<<< orphan*/  ClientCert; int /*<<< orphan*/  SecurePrivateKeyName; int /*<<< orphan*/  SecurePublicCertName; } ;
typedef  TYPE_1__ SECURE_SIGN ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetData2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetX (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcSecureSign(SECURE_SIGN *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(SECURE_SIGN));
	PackGetStr(p, "SecurePublicCertName", t->SecurePublicCertName, sizeof(t->SecurePublicCertName));
	PackGetStr(p, "SecurePrivateKeyName", t->SecurePrivateKeyName, sizeof(t->SecurePrivateKeyName));
	t->ClientCert = PackGetX(p, "ClientCert");
	PackGetData2(p, "Random", t->Random, sizeof(t->Random));
	PackGetData2(p, "Signature", t->Signature, sizeof(t->Signature));
	t->UseSecureDeviceId = PackGetInt(p, "UseSecureDeviceId");
	t->BitmapId = PackGetInt(p, "BitmapId");
}