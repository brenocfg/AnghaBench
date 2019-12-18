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
struct TYPE_3__ {int /*<<< orphan*/  ClientBuild; int /*<<< orphan*/  ClientVer; int /*<<< orphan*/  ClientStr; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void PackAddClientVersion(PACK *p, CONNECTION *c)
{
	// Validate arguments
	if (p == NULL || c == NULL)
	{
		return;
	}

	PackAddStr(p, "client_str", c->ClientStr);
	PackAddInt(p, "client_ver", c->ClientVer);
	PackAddInt(p, "client_build", c->ClientBuild);
}