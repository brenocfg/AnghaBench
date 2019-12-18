#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  ref; } ;
struct TYPE_7__ {int /*<<< orphan*/  ref; TYPE_2__* release_event; } ;
typedef  TYPE_1__ THREAD ;
typedef  TYPE_2__ EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CleanupThread (TYPE_1__*) ; 
 scalar_t__ Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (TYPE_2__*) ; 
 int /*<<< orphan*/  Set (TYPE_2__*) ; 

void ReleaseThread(THREAD *t)
{
	UINT ret;
	EVENT *e;
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	e = t->release_event;
	if (e != NULL)
	{
		AddRef(e->ref);
	}

	ret = Release(t->ref);
	Set(e);

	ReleaseEvent(e);

	if (ret == 0)
	{
		CleanupThread(t);
	}
}