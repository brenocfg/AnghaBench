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
struct TYPE_3__ {int /*<<< orphan*/  RadiusRetryInterval; int /*<<< orphan*/  RadiusSecret; int /*<<< orphan*/  HubName; int /*<<< orphan*/  RadiusPort; int /*<<< orphan*/  RadiusServerName; } ;
typedef  TYPE_1__ RPC_RADIUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcRadius(PACK *p, RPC_RADIUS *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "RadiusServerName", t->RadiusServerName);
	PackAddInt(p, "RadiusPort", t->RadiusPort);
	PackAddStr(p, "HubName", t->HubName);
	PackAddStr(p, "RadiusSecret", t->RadiusSecret);
	PackAddInt(p, "RadiusRetryInterval", t->RadiusRetryInterval);
}