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
typedef  size_t UINT ;
struct TYPE_3__ {size_t NumEntry; int /*<<< orphan*/ * Entry; } ;
typedef  TYPE_1__ ROUTE_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  DebugPrintRoute (int /*<<< orphan*/ ) ; 
 int IsDebug () ; 

void DebugPrintRouteTable(ROUTE_TABLE *r)
{
	UINT i;
	// Validate arguments
	if (r == NULL)
	{
		return;
	}

	if (IsDebug() == false)
	{
		return;
	}

	Debug("---- Routing Table (%u Entries) ----\n", r->NumEntry);

	for (i = 0;i < r->NumEntry;i++)
	{
		Debug("   ");

		DebugPrintRoute(r->Entry[i]);
	}

	Debug("------------------------------------\n");
}