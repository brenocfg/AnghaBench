#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  ROUTE_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,char*) ; 
 int IsDebug () ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  RouteToStr (char*,int,int /*<<< orphan*/ *) ; 

void DebugPrintRoute(ROUTE_ENTRY *e)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (e == NULL)
	{
		return;
	}

	if (IsDebug() == false)
	{
		return;
	}

	RouteToStr(tmp, sizeof(tmp), e);

	Debug("%s\n", tmp);
}