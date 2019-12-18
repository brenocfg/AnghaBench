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
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ COUNTER ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  KS_CURRENT_COUNT ; 
 int /*<<< orphan*/  KS_DELETE_COUNTER_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_SUB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void DeleteCounter(COUNTER *c)
{
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	// KS
	KS_INC(KS_DELETE_COUNTER_COUNT);
	KS_SUB(KS_CURRENT_COUNT, c->c);

	DeleteLock(c->lock);
	Free(c);
}