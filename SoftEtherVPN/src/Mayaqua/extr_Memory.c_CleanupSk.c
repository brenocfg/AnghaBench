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
struct TYPE_4__ {int /*<<< orphan*/  lock; struct TYPE_4__* p; } ;
typedef  TYPE_1__ SK ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  KS_FREESK_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 

void CleanupSk(SK *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	// Memory release
	Free(s->p);
	DeleteLock(s->lock);
	Free(s);

	// KS
	KS_INC(KS_FREESK_COUNT);
}