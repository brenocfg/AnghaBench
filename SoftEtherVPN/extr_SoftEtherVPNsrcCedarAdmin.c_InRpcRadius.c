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
struct TYPE_4__ {void* RadiusRetryInterval; int /*<<< orphan*/  RadiusSecret; int /*<<< orphan*/  HubName; void* RadiusPort; int /*<<< orphan*/  RadiusServerName; } ;
typedef  TYPE_1__ RPC_RADIUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcRadius(RPC_RADIUS *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_RADIUS));
	PackGetStr(p, "RadiusServerName", t->RadiusServerName, sizeof(t->RadiusServerName));
	t->RadiusPort = PackGetInt(p, "RadiusPort");
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	PackGetStr(p, "RadiusSecret", t->RadiusSecret, sizeof(t->RadiusSecret));
	t->RadiusRetryInterval = PackGetInt(p, "RadiusRetryInterval");
}