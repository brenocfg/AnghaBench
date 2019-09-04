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
struct TYPE_4__ {struct TYPE_4__* ServerName; struct TYPE_4__* CmdLine; struct TYPE_4__* AdminHub; struct TYPE_4__* HubName; } ;
typedef  TYPE_1__ PS ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 

void FreePs(PS *ps)
{
	// Validate arguments
	if (ps == NULL)
	{
		return;
	}

	Free(ps->HubName);
	Free(ps->AdminHub);
	Free(ps->CmdLine);
	Free(ps->ServerName);

	Free(ps);
}