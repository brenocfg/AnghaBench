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
struct TYPE_4__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  AdapterName; } ;
typedef  TYPE_1__ SL_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  SlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  SlFreeLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlFreeUnicode (int /*<<< orphan*/ ) ; 

void SlFreeAdapter(SL_ADAPTER *a)
{
	// Validate arguments
	if (a == NULL)
	{
		return;
	}

	SlFreeUnicode(a->AdapterName);

	SlFreeLock(a->Lock);

	SlFree(a);
}