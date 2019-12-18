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
struct TYPE_4__ {int /*<<< orphan*/  Session; int /*<<< orphan*/ * ParentLocalBridge; } ;
typedef  TYPE_1__ BRIDGE ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseSession (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopSession (int /*<<< orphan*/ ) ; 

void BrFreeBridge(BRIDGE *b)
{
	// Validate arguments
	if (b == NULL)
	{
		return;
	}

	if (b->ParentLocalBridge != NULL)
	{
		b->ParentLocalBridge = NULL;
	}

	// Stop session thread
	StopSession(b->Session);
	ReleaseSession(b->Session);

	Free(b);
}