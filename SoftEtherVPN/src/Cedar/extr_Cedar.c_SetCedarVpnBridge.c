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
struct TYPE_3__ {int Bridge; int /*<<< orphan*/  ServerStr; } ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  CEDAR_BRIDGE_STR ; 
 int /*<<< orphan*/  CopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ ) ; 

void SetCedarVpnBridge(CEDAR *c)
{
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	c->Bridge = true;

	Free(c->ServerStr);
	c->ServerStr = CopyStr(CEDAR_BRIDGE_STR);
}