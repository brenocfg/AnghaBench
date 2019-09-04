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
struct TYPE_4__ {int /*<<< orphan*/ * ref; } ;
typedef  TYPE_1__ QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  CleanupQueue (TYPE_1__*) ; 
 scalar_t__ Release (int /*<<< orphan*/ *) ; 

void ReleaseQueue(QUEUE *q)
{
	// Validate arguments
	if (q == NULL)
	{
		return;
	}

	if (q->ref == NULL || Release(q->ref) == 0)
	{
		CleanupQueue(q);
	}
}