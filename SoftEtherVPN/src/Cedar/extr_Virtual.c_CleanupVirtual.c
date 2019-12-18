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
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  Counter; int /*<<< orphan*/ * Session; } ;
typedef  TYPE_1__ VH ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCounter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseSession (int /*<<< orphan*/ *) ; 

void CleanupVirtual(VH *v)
{
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	if (v->Session != NULL)
	{
		ReleaseSession(v->Session);
	}

	DeleteCounter(v->Counter);
	DeleteLock(v->lock);

	Free(v);
}