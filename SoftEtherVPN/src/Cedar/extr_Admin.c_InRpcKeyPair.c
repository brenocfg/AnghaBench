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
struct TYPE_3__ {int /*<<< orphan*/  Flag1; int /*<<< orphan*/  Key; int /*<<< orphan*/  Cert; } ;
typedef  TYPE_1__ RPC_KEY_PAIR ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetK (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetX (int /*<<< orphan*/ *,char*) ; 

void InRpcKeyPair(RPC_KEY_PAIR *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	t->Cert = PackGetX(p, "Cert");
	t->Key = PackGetK(p, "Key");
	t->Flag1 = PackGetInt(p, "Flag1");
}