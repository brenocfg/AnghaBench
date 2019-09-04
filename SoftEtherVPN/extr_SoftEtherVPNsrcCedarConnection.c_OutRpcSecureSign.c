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
struct TYPE_3__ {int /*<<< orphan*/  BitmapId; int /*<<< orphan*/  UseSecureDeviceId; int /*<<< orphan*/  Signature; int /*<<< orphan*/  Random; int /*<<< orphan*/  ClientCert; int /*<<< orphan*/  SecurePrivateKeyName; int /*<<< orphan*/  SecurePublicCertName; } ;
typedef  TYPE_1__ SECURE_SIGN ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddX (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcSecureSign(PACK *p, SECURE_SIGN *t)
{
	// Validate arguments
	if (p == NULL || t == NULL)
	{
		return;
	}

	PackAddStr(p, "SecurePublicCertName", t->SecurePublicCertName);
	PackAddStr(p, "SecurePrivateKeyName", t->SecurePrivateKeyName);
	PackAddX(p, "ClientCert", t->ClientCert);
	PackAddData(p, "Random", t->Random, sizeof(t->Random));
	PackAddData(p, "Signature", t->Signature, sizeof(t->Signature));
	PackAddInt(p, "UseSecureDeviceId", t->UseSecureDeviceId);
	PackAddInt(p, "BitmapId", t->BitmapId);
}